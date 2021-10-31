#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

#define PORT             5510

int Socket(int domain, int type, int protocol);
