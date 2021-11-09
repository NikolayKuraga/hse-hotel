#ifndef SHARED_HPP
#define SHARED_HPP

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>

#define VERSION   "2021.11.09"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"

#define PORT 5510

namespace cstm {
    ssize_t sendStr(int sockfd, const std::string *str);
    ssize_t recvStr(int sockfd, std::string *str);
}

#endif//SHARED_HPP
