#include "client_client.h"
#include "common_socket.h"
#define LARGO_VECTOR_CLAVE 300
#define EXITO 0
#define ERROR -1


int main(int argc, char const *argv[]) {
    archivo_t archivo;
    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, argv[1], argv[2]);
    if (abrir_y_validar_archivo(argc,argv,&archivo,&socket)==ERROR){
    	return ERROR;
    }
    char clave[LARGO_VECTOR_CLAVE];
    //Me quedo solo con la clave sacando el --key del argumento
    int tamanio_clave= strlen(argv[4])-6;
    memcpy(clave,&argv[4][6],tamanio_clave);
    clave[tamanio_clave] = '\0';
    enviar_datos(argv[3],clave,&archivo,&socket);
    cerrar_archivo(&archivo);
    socket_uninit(&socket);
	return EXITO;
}
