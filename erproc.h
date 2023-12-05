#ifndef ERPROC_H 
#define ERPROC_H

#include <sys/socket.h>
#include <sys/types.h> //работа с константами (аргументами функции сокет)
#define PORT 6379

int Socket(int domain, int type, int protocol);
void Bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr* adr, socklen_t* adrlen);
void Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
void Inet_pton(int af, const char* src, void* dst);
#endif