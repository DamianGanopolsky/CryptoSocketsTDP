#include <stdio.h>

#include "common_socket.h"
#include "common_cesar_encryption.h"

int main(int argc, char const *argv[]){

	socket_t socket;
	socket_t socket_peer;

	socket_init(&socket);
	socket_init(&socket_peer);

	int val=1;

    int tamanio_clave= strlen(argv[3])-6;
    char subbuff[tamanio_clave+1];
    memcpy( subbuff, &argv[3][6], tamanio_clave );
    subbuff[tamanio_clave] = '\0';

	setsockopt(socket.fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

	socket_bind_and_listen(&socket,NULL,argv[1]);

	socket_accept(&socket, &socket_peer);

	unsigned char client_message[64];
	ssize_t recibidos=0;
	//unsigned char* client_message_final;

	recibidos=socket_receive(&socket_peer,client_message, sizeof(client_message));

	unsigned char message_final[recibidos+1];
	memset(message_final,0,sizeof(message_final));
	memcpy(message_final,client_message,recibidos+1);


	printf("Recibidos es %li \n",recibidos);

	printf("The client sent the data: %s \n",client_message);

	printf("El tamaño del buffer final es %li \n",sizeof(message_final));

	printf("The client sent the data: %s \n",message_final);

/*	recibidos=recv(socket_peer.fd,&client_message,sizeof(client_message),0);

	printf("La cantidad de bytes recibidos es %li \n",recibidos);

	printf("The client sent the data: %s \n",client_message);
*/
    if(atoi(subbuff)!=0){
    	int clave_numerica=atoi(subbuff);
    	unsigned char buffer_normalizado[sizeof(client_message)];
    	memset(buffer_normalizado,0,sizeof(buffer_normalizado));
    	descifrado_cesar(client_message,buffer_normalizado,clave_numerica,sizeof(client_message));
    	printf("El mensaje es %s \n",buffer_normalizado);
    }
/*
    if(strcmp(argv[2],"--method=vigenere")==0){
    	file_reader_iterate_vigenere(&file_reader,subbuff);
    }

    if(strcmp(argv[2],"--method=rc4")==0){
    	file_reader_iterate_rc4(&file_reader,subbuff);
    }
*/
	socket_uninit(&socket);

	return 0;
}
