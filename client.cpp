#include "client.hpp"

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int info = connect(sockfd, addr, addrlen);
    if (info == -1) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int main(int argc, char ** argv) {

    int sockServer = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer = { 0 };

    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    Connect(sockServer, (struct sockaddr *) &addrServer, sizeof(addrServer));

    std::cout << "Successfully connected to the server!" << std::endl;

    close(sockServer);
    return 0;
}
