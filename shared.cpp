#include "shared.hpp"

int Socket(int domain, int type, int protocol) {
    int info = socket(domain, type, protocol);
    if (info == -1) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}
