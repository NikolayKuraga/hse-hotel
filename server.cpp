#include "server.hpp"

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
