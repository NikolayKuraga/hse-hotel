#include "server.hpp"

int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    int info = setsockopt(sockfd, level, optname, optval, optlen);
    if (info == -1) {
        perror("setsockopt() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int info = bind(sockfd, addr, addrlen) == -1;
    if (info == -1) {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int Listen(int sockfd, int backlog) {
    int info = listen(sockfd, backlog);
    if (info == -1) {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int info = accept(sockfd, addr, addrlen);
    if (info == -1) {
        perror("accept() failed");
    }
    return info;
}

int main(int argc, char *argv[]) {

    int sockServer = Socket(AF_INET, SOCK_STREAM, 0);
    int sockClient = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer = { 0 };
    struct sockaddr_in addrClient = { 0 };

    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    short one = 1;
    Setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
    Bind(sockServer, (struct sockaddr *) &addrServer, sizeof(addrServer));

    Listen(sockServer, LEN_QUEUE_CLIENT);

    socklen_t lenAddrServer = sizeof(addrServer);
    sockClient = Accept(sockServer, (struct sockaddr *) &addrClient, &lenAddrServer);

    std::cout << "A client successfully connected!" << std::endl;

    close(sockClient);
    close(sockServer);
    return 0;
}
