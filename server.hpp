#include "shared.hpp"

#define LEN_QUEUE_CLIENT 5

int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
