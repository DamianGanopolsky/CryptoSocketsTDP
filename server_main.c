#include <string.h>
#include "common_socket.h"
#include "server_server.h"
#define EXITO 0
#define ERROR -1
#define LARGO_VECTOR_CLAVE 300

int main(int argc, char const *argv[]){
	socket_t socket;
	socket_t socket_peer;
	char clave[LARGO_VECTOR_CLAVE];
    //Me quedo solo con la clave sacando el --key del argumento
    int tamanio_clave= strlen(argv[3])-6;
    memcpy(clave,&argv[3][6],tamanio_clave);
    clave[tamanio_clave] = '\0';
	socket_init(&socket);
	socket_init(&socket_peer);
	socket_bind_and_listen(&socket,NULL,argv[1]);
	socket_accept(&socket, &socket_peer);
	recibir_datos(argv[2],clave,&socket_peer);
	socket_uninit(&socket);
	socket_uninit(&socket_peer);
	return 0;
}
