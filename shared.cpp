#include "shared.hpp"
/*
int cstm::socket(int domain, int type, int protocol) {
    int info = ::socket(domain, type, protocol);
    if (info == -1) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int cstm::setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    int info = ::setsockopt(sockfd, level, optname, optval, optlen);
    if (info == -1) {
        perror("setsockopt() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int cstm::bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int info = ::bind(sockfd, addr, addrlen) == -1;
    if (info == -1) {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int cstm::listen(int sockfd, int backlog) {
    int info = ::listen(sockfd, backlog);
    if (info == -1) {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

int cstm::accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int info = ::accept(sockfd, addr, addrlen);
    if (info == -1) {
        perror("accept() failed");
    }
    return info;
}

int cstm::connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int info = ::connect(sockfd, addr, addrlen);
    if (info == -1) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}
*/
ssize_t cstm::sendStr(int sockfd, const std::string *str, int flags) {
    size_t len_tmp = str->length();
    ssize_t info = ::send(sockfd, &len_tmp, sizeof(len_tmp), flags);
    if (info != -1) {
        info = ::send(sockfd, str->c_str(), len_tmp * sizeof(char), flags);
    }
    return info;
}

ssize_t cstm::recvStr(int sockfd, std::string *str, int flags) {
    size_t len_tmp;
    ssize_t info = ::recv(sockfd, &len_tmp, sizeof(len_tmp), flags);
    if (info != -1) {
        str->clear();
        str->resize(len_tmp);
        info = ::recv(sockfd, str->data(), len_tmp * sizeof(char), flags);
    }
    return info;
}
