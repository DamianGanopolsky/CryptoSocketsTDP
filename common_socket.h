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

//Libera los recursos del socket, haciendo un shutdown
//y luego un close.
void socket_uninit(socket_t *self);

//Le asigna una direccion al socket y lo marca como pasivo
void socket_bind_and_listen(socket_t *self,
	                        const char *host,
	                        const char *service);

//Crea el nuevo socket peer, el cual servira para
//establecer la comunicacion cliente-servidor
void socket_accept(socket_t *listener, socket_t *peer);

//Conecta al socket referido a una de las posibles direcciones
//que nos provee getaddrinfo
void socket_connect(socket_t *self, const char *host, const char *service);

//Envia la totalidad del buffer, hace uso de un puntero para ir avanzando
//sobre los caracteres que se pudieron enviar para asi terminar enviando todos
ssize_t socket_send(socket_t *self, unsigned char *buffer, size_t length);

//Recibe la totalidad del buffer, hace uso de un puntero para ir avanzando
//posiciones en el buffer para asi recibir los caracteres que no se recibieron
//antes
ssize_t socket_receive(socket_t *self,unsigned char *buffer, size_t length);

#endif

#endif /* COMMON_SOCKET_H_ */
