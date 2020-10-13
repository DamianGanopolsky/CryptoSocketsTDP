
#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#ifndef SOCKET_H
#define SOCKET_H
#define _POSIX_C_SOURCE 200112L
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct {
	int fd;
} socket_t;

void socket_init(socket_t *self);
void socket_uninit(socket_t *self);

void socket_bind_and_listen(socket_t *self,
	                        const char *host,
	                        const char *service);
void socket_accept(socket_t *listener, socket_t *peer);

void socket_connect(socket_t *self, const char *host, const char *service);

ssize_t socket_send(socket_t *self, unsigned char *buffer, size_t length);
ssize_t socket_receive(socket_t *self, char *buffer, size_t length);

#endif

#endif /* COMMON_SOCKET_H_ */
