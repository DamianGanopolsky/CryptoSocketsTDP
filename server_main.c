#include <stdio.h>
#include "common_socket.h"
#include "server_server.h"
#define EXITO 0
#define ERROR -1
#define LARGO_VECTOR_CLAVE 300

int slice(const char* argumento,char* clave){
    int tamanio_clave= strlen(argumento)-6;
    //Establezco un limite en el tamaño de la
    //clave para evitar un buffer overflow
    if (tamanio_clave>LARGO_VECTOR_CLAVE){
    	fprintf(stderr, "Tamaño de clave demasiado grande \n");
    	return ERROR;
    }
    memcpy(clave,&argumento[6],tamanio_clave);
    clave[tamanio_clave] = '\0';
    return EXITO;
}

void recibir_datos(const char* argumento,char* clave,socket_t* socket_peer){
    if (strcmp(argumento,"--method=cesar")==0){
    	int clave_numerica=atoi(clave);
    	recibir_mensaje_cesar(socket_peer,clave_numerica);
    }
    if (strcmp(argumento,"--method=vigenere")==0){
    	recibir_mensaje_vigenere(socket_peer,clave);
    }
    if (strcmp(argumento,"--method=rc4")==0){
    	recibir_mensaje_rc4(socket_peer,clave);
    }
}

int main(int argc, char const *argv[]){
	socket_t socket;
	socket_t socket_peer;
	char clave[LARGO_VECTOR_CLAVE];
    if (slice(argv[3],clave)==ERROR){
    	return ERROR;
    }
	socket_init(&socket);
	socket_init(&socket_peer);
	socket_bind_and_listen(&socket,NULL,argv[1]);
	socket_accept(&socket, &socket_peer);
	recibir_datos(argv[2],clave,&socket_peer);
	socket_uninit(&socket);
	socket_uninit(&socket_peer);
	return 0;
}
