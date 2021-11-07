#ifndef SERVER_HPP
#define SERVER_HPP

#include "shared.hpp"

#include <thread>
#include <mutex>
#include <vector>

#define COMMAND_LINE_PROMPT " >> "
#define LEN_QUEUE           5

void DealWithClient(int *p_fdSockClient, sockaddr_in *p_addrClient, socklen_t *p_lenAddrClient);
void AcceptClients(int *p_fdSockServer);

#endif//SERVER_HPP
