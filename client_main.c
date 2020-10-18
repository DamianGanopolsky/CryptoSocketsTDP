#include "client_procesar_datos.h"
#include "common_socket.h"
#define LARGO_VECTOR_CLAVE 300


int main(int argc, char const *argv[]) {
    archivo_t archivo;
    socket_t socket;

    socket_init(&socket);

    socket_connect(&socket, argv[1], argv[2]);

    if (argc<6){
    	abrir_archivo(&archivo,NULL);
    }else{
    	abrir_archivo(&archivo, argv[6]); //ACA INICIALIZO MI TDA READER
    }

    int tamanio_clave= strlen(argv[4])-6;
    char subbuff[LARGO_VECTOR_CLAVE];
    memset(subbuff,0,sizeof(subbuff));
    memcpy(subbuff,&argv[4][6],tamanio_clave);
    subbuff[tamanio_clave] = '\0';

    if (atoi(subbuff)!=0){
    	int clave_numerica=atoi(subbuff);
    	enviar_datos_cesar(&archivo,clave_numerica,&socket);
    }
    if (strcmp(argv[3],"--method=vigenere")==0){
    	enviar_datos_vigenere(&archivo,subbuff,&socket);
    }
    if (strcmp(argv[3],"--method=rc4")==0){
    	enviar_datos_rc4(&archivo,subbuff,&socket);
    }
    cerrar_archivo(&archivo); //ACA CIERRO MI TDA READER
    socket_uninit(&socket);
	return 0;
}
