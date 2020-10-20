#include "client_procesar_datos.h"
#include "common_socket.h"
#include "common_util.h"
#define LARGO_VECTOR_CLAVE 300
#define EXITO 0
#define ERROR -1


int main(int argc, char const *argv[]) {
    archivo_t archivo;
    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, argv[1], argv[2]);
	if(argc<5){
		fprintf(stderr,"Cantidad de parametros invalidos \n");
	}
    if (argc==5){ //Si son 5 argumentos, asumo que la entrada es por stdin
    	abrir_archivo(&archivo,NULL);
    }else{
    	if(abrir_archivo(&archivo, argv[6])==ERROR){
    		socket_uninit(&socket); //Libero recurso previamente inicializado
    		return ERROR;
    	}
    }
    char clave[LARGO_VECTOR_CLAVE];
    if(slice(argv[4],clave)==ERROR){
    	return ERROR;
    }
    enviar_datos(argv[3],clave,&archivo,&socket);
    cerrar_archivo(&archivo);
    socket_uninit(&socket);
	return EXITO;
}
