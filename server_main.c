#include <stdio.h>

#include "common_socket.h"
#include "common_cesar_encryption.h"
#include "server_server.h"

int main(int argc, char const *argv[]){
	socket_t socket;
	socket_t socket_peer;

	socket_init(&socket);
	socket_init(&socket_peer);

	int val=1;

	setsockopt(socket.fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

	socket_bind_and_listen(&socket,NULL,argv[1]);

	socket_accept(&socket, &socket_peer);

	recibir_mensajes(&socket_peer,argv[2],argv[3]);

	socket_uninit(&socket);
	socket_uninit(&socket_peer);

	return 0;
}
