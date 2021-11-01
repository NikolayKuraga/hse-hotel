#include "shared.hpp"

#include <sqlite3.h>

#define LEN_QUEUE_CLIENT 5

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
