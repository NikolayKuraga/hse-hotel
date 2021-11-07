#include "server.hpp"

// Shared memory section
std::mutex mutexF;
std::vector<std::thread> vectorThreads; // vector of threads excepting main() function thread

// The end of shared memory section

// Function for communication with client
void DealWithClient(int *p_fdSockClient, sockaddr_in *p_addrClient, socklen_t *p_lenAddrClient) {
    std::string msg;
    std::cout << "A client successfully connected and ready to communicate!" << std::endl;
    for (int i = 0; ; ++i) {
        cstm::recvStr(*p_fdSockClient, &msg);
        std::cout << msg << std::endl;
        msg = "Hello, Client!";
        cstm::sendStr(*p_fdSockClient, &msg);
    }
}

// Function for infinite accessing clients
void AcceptClients(int *p_fdSockServer) {
    // declare pointers to client's file descriptor, address, address length
    int *p_fdSockClient;
    struct sockaddr_in *p_addrClient;
    socklen_t *p_lenAddrClient;

    for(int i = 0;; ++i) {
        // allocate memory for client's file descriptor, address and address length
        p_fdSockClient = new (std::nothrow) int;
        p_addrClient = new (std::nothrow) sockaddr_in;
        p_lenAddrClient = new (std::nothrow) socklen_t;
        if(p_fdSockClient == nullptr || p_addrClient == nullptr || p_lenAddrClient == nullptr) {
            std::cerr << "bad allocation" << std::endl;
            delete p_fdSockClient;
            delete p_addrClient;
            delete p_lenAddrClient;
        }

        // accept client connecting
        *p_fdSockClient = accept(*p_fdSockServer, (struct sockaddr *) p_addrClient, p_lenAddrClient);
        if(*p_fdSockClient == -1) {
            std::cerr << "accept() failed" << std::endl;
            delete p_fdSockClient;
            delete p_addrClient;
            delete p_lenAddrClient;
        }

        // create thread for further communication
        vectorThreads.emplace_back(std::thread(DealWithClient, p_fdSockClient, p_addrClient, p_lenAddrClient));
        vectorThreads.back().detach();
    }
}

int main(int argc, char **argv) {
    int info;

    // set up file descriptor for server's socket
    int fdSockServer = socket(AF_INET, SOCK_STREAM, 0);
    if(fdSockServer == -1) {
        std::cerr << "socket() failed" << std::endl;
        return -1;
    }
    int one = 1;
    info = setsockopt(fdSockServer, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(info == -1) {
        std::cerr << "setsockopt() failed" << std::endl;
        return -1;
    }

    // specify server's port, address and assign them to the socket, make it listen
    struct sockaddr_in addrServer = { 0 };
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
    info = bind(fdSockServer, (struct sockaddr *) &addrServer, sizeof(addrServer));
    if(info == -1) {
        std::cerr << "bind() failed" << std::endl;
    }
    info = listen(fdSockServer, LEN_QUEUE);
    if(info == -1) {
        std::cerr << "listen() failed" << std::endl;
        return -1;
    }

    // start accessing clients thread
    vectorThreads.push_back(std::move(std::thread(AcceptClients, &fdSockServer)));
    vectorThreads.back().detach();

    // monitor console input
    std::cout << COMMAND_LINE_PROMPT;
    for(;;) {
        std::string str;
        std::cin >> str;
        if(str == "print") {
            std::cin >> str;
            if(str == "status") {
                std::cout << "working" << std::endl;
            }
            else if(str == "threads") {
                std::cout << "Active threads: " << std::endl << "\t" << std::this_thread::get_id() << std::endl;
                for(unsigned long i = 0; i < vectorThreads.size(); ++i) {
                    std::cout << "\t" << vectorThreads.at(i).get_id() << std::endl;
                }
            }
            else {
                std::cout << "Wrong command: " << std::endl << "\t\"" + str + "\"" << std::endl;
            }
        }
        else {
            std::cout << "Wrong command: " << std::endl << "\t\"" + str + "\"" << std::endl;
        }
        std::cout << COMMAND_LINE_PROMPT;
    }
    close(fdSockServer);
    return 0;
}
