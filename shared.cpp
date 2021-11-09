#include "shared.hpp"

ssize_t cstm::sendStr(int sockfd, const std::string *str) {
    size_t lenTmp = str->length();
    ssize_t info = ::send(sockfd, &lenTmp, sizeof(lenTmp), MSG_NOSIGNAL);         // On success send() returns
    if(info != -1) {                                                              //the number of bytes sent,
        info = ::send(sockfd, str->c_str(), lenTmp * sizeof(char), MSG_NOSIGNAL); //on error, -1 is returned
    }
    return info;
}

ssize_t cstm::recvStr(int sockfd, std::string *str) {
    size_t lenTmp = 0;
    ssize_t info = ::recv(sockfd, &lenTmp, sizeof(lenTmp), 0); // On success recv() return the number of bytes
    if(info != -1) {                                           //received, on error, -1 is returned. When a
        char *buf = new char[lenTmp];                          //stream socket peer has performed a shutdown,
        info = ::recv(sockfd, buf, lenTmp * sizeof(char), 0);  //the return value will be 0 (i.e. EOF)
        *str = buf;
        delete[] buf;
    }
    return info;
}
