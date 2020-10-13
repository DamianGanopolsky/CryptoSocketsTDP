#include <stdio.h>

#include "common_socket.h"

int main(int argc, char const *argv[]){

	socket_t socket;
	socket_t socket_peer;

	socket_init(&socket);
	socket_init(&socket_peer);

	int val=1;

	setsockopt(socket.fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

	socket_bind_and_listen(&socket,NULL,argv[1]);

	socket_accept(&socket, &socket_peer);

	//char buffer[20];

	char client_message[256];

	recv(socket_peer.fd,&client_message,sizeof(client_message),0);

	printf("The client sent the data: %s \n",client_message);
	/*
	char buf[16];
	int bytes=0;

	while(bytes==0){
		bytes = recv(socket_peer.fd, buf,12, 0);
		buf[12] = 0;
		printf("Recibido %d bytes: %s\n", bytes, buf);
	}
*/
	//int bytes = recv(socket_peer.fd, buf,12, 0);


	//recv(socket.fd,buffer,20,0);

	//printf("el mensaje es %s \n",buffer);

	socket_uninit(&socket);

	return 0;
}
