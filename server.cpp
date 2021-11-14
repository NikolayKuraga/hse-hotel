#include "server.hpp"

//// Shared memory section
std::mutex mtx;
std::vector<std::thread> vctrThreads; // vector of threads excepting main() function thread

// command line prompt
const char promptCmd[] = { " >> " };
// notifications bounds
const std::string bndsNtfctnInf[] = { "...\n[i] ", " [Inf]\n" };
const std::string bndsNtfctnMsg[] = { "...\n[@] ", " [Msg]\n" };
const std::string bndsNtfctnWrn[] = { "...\n[!] ", " [Wrn]\n" };
//// The end of shared memory section

// Function for printring message and cmd prompt (P -- printing)
void PrintMes(const std::string PTxt, const std::string PBnds[2], const std::string PPrompt = promptCmd) {
    mtx.lock();
    std::cout << PBnds[0] << PTxt << PBnds[1] << PPrompt;
    std::cout.flush();
    mtx.unlock();
}

// Function for communication with client
void DealWithClient(int *p_fdSockClient, sockaddr_in *p_addrClient, socklen_t *p_lenAddrClient) {
    int info = 0;
    std::string msg;

    PrintMes("Another client has connected", bndsNtfctnInf);

    for(;;) {
        info = cstm::recvStr(*p_fdSockClient, &msg);
        if(info == -1) {
            PrintMes("A client was suddenly disconnected", bndsNtfctnWrn);
            break;
        }
        else if(info != 0) {
            PrintMes(msg, bndsNtfctnMsg);
        }
        msg = "Hello, Client!";
        if(cstm::sendStr(*p_fdSockClient, &msg) == -1) {
            PrintMes("A client was suddenly disconnected", bndsNtfctnWrn);
            break;
        }
    }

    close(*p_fdSockClient);
    delete p_fdSockClient;
    delete p_addrClient;
    delete p_lenAddrClient;
}

// Function for accessing clients
void AcceptClients(int *p_fdSockServer) {
    // declare pointers to client's file descriptor, address, address length
    int *p_fdSockClient;
    struct sockaddr_in *p_addrClient;
    socklen_t *p_lenAddrClient;

    for(;;) {
        // allocate memory for client's file descriptor, address and address length
        p_fdSockClient = new (std::nothrow) int;
        p_addrClient = new (std::nothrow) sockaddr_in;
        p_lenAddrClient = new (std::nothrow) socklen_t;
        if(p_fdSockClient == nullptr || p_addrClient == nullptr || p_lenAddrClient == nullptr) {
            mtx.lock();
            std::cerr << "bad allocation" << std::endl;
            mtx.unlock();
            delete p_fdSockClient;
            delete p_addrClient;
            delete p_lenAddrClient;
        }

        // accept client connecting
        *p_fdSockClient = accept(*p_fdSockServer, (struct sockaddr *) p_addrClient, p_lenAddrClient);
        if(*p_fdSockClient == -1) {
            mtx.lock();
            std::cerr << "accept() failed" << std::endl;
            mtx.unlock();
            delete p_fdSockClient;
            delete p_addrClient;
            delete p_lenAddrClient;
        }

        // create thread for further communication
        mtx.lock();
        vctrThreads.emplace_back(std::thread(DealWithClient, p_fdSockClient, p_addrClient, p_lenAddrClient));
        mtx.unlock();
    }
}

int main(int argc, char **argv) {
    // set up file descriptor for server's socket
    int fdSockServer = socket(AF_INET, SOCK_STREAM, 0);
    if(fdSockServer == -1) {
        std::cerr << "socket() failed" << std::endl;
        return -1;
    }
    int one = 1;
    if(setsockopt(fdSockServer, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) == -1) {
        std::cerr << "setsockopt() failed" << std::endl;
        return -1;
    }

    // specify server's port, address and assign them to the socket, make it listen
    struct sockaddr_in addrServer = { 0 };
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(fdSockServer, (struct sockaddr *) &addrServer, sizeof(addrServer)) == -1) {
        std::cerr << "bind() failed" << std::endl;
    }
    if(listen(fdSockServer, LEN_QUEUE) == -1) {
        std::cerr << "listen() failed" << std::endl;
        return -1;
    }

    // start accessing clients thread
    vctrThreads.push_back(std::move(std::thread(AcceptClients, &fdSockServer))); // thread is non-copyable

    // monitor console input
    for(;;) {
        std::string strInputCmd;
        std::string partStrInputCmd;
        std::vector<std::string> vctrPartsStrInputCmd;
        do {
            vctrPartsStrInputCmd.clear();
            mtx.lock();
            std::cout << promptCmd;
            mtx.unlock();
            std::getline(std::cin, strInputCmd);
        } while(strInputCmd.length() == 0);
        std::stringstream strStreamInputCmd(strInputCmd);
        while(getline(strStreamInputCmd, partStrInputCmd, ' ')) {
            vctrPartsStrInputCmd.push_back(partStrInputCmd);
        }
        mtx.lock();
        if(vctrPartsStrInputCmd.at(0) == "stop") {
            break;
        }
        else if(vctrPartsStrInputCmd.at(0) == "print") {
            if(vctrPartsStrInputCmd.size() > 1) {
                if(vctrPartsStrInputCmd.at(1) == "status") {
                    std::cout << "working" << std::endl;
                }
                else if(vctrPartsStrInputCmd.at(1) == "threads") {
                    std::cout << "active threads:\n   main\n\t" << std::this_thread::get_id() << std::endl;
                    for(unsigned long i = 0; i < vctrThreads.size(); ++i) {
                        switch(i) {
                        case 0:
                            std::cout << "   accepting clients\n";
                            break;
                        case 1:
                            std::cout << "   other threads\n";
                            break;
                        }
                        std::cout << "\t" << vctrThreads.at(i).get_id() << std::endl;
                    }
                }
                else if(vctrPartsStrInputCmd.at(1) == "version") {
                    std::cout << "      version " << VERSION << ", server\n" << std::endl;
                }
                else {
                    std::cout << "  Cannot print this!\n";
                }
            }
            else {
                std::cout << "  Print what?\n";
            }
        }
        else {
            std::cout << "  Wrong command!\n";
        }
        mtx.unlock();
    }

    // stop wait for other threads
    for(unsigned long i = 0; i < vctrThreads.size(); ++i) {
        vctrThreads.at(i).detach();
    }

    // terminate the program
    close(fdSockServer);
    return 0;
}
