#ifndef SHARED_HPP
#define SHARED_HPP

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>

#define VERSION   "2021.11.07"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"

#define PORT 5510

namespace cstm {
/*    int socket(int domain, int type, int protocol);
    int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int listen(int sockfd, int backlog);
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);*/
    ssize_t sendStr(int sockfd, const std::string *str, int flags = 0);
    ssize_t recvStr(int sockfd, std::string *str, int flags = 0);
}

#endif//SHARED_HPP
