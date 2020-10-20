#include "client_procesar_datos.h"
#include "common_socket.h"
#define LARGO_VECTOR_CLAVE 300
#define EXITO 0
#define ERROR -1

//Recibe el argumento correspondiente a la clave que
//le llega al main y devuelve la clave sin el --key
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


int abrir_y_validar_archivo(int argc,char const *argv[],archivo_t* archivo,socket_t* socket){
	if(argc<5){
		fprintf(stderr,"Cantidad de parametros invalidos \n");
	}
    if (argc==5){ //Si son 5 argumentos, la entrada es por stdin
    	abrir_archivo(archivo,NULL);
    }else{
    	if(abrir_archivo(archivo, argv[6])==ERROR){
    		socket_uninit(socket); //Libero recurso previamente inicializado
    		return ERROR;
    	}
    }
    return EXITO;
}


int main(int argc, char const *argv[]) {
    archivo_t archivo;
    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, argv[1], argv[2]);
    if(abrir_y_validar_archivo(argc,argv,&archivo,&socket)==ERROR){
    	return ERROR;
    }
    char clave[LARGO_VECTOR_CLAVE];
    if(slice(argv[4],clave)==ERROR){
    	return ERROR;
    }
    if (strcmp(argv[3],"--method=cesar")==0){
    	int clave_numerica=atoi(clave);
    	enviar_datos_cesar(&archivo,clave_numerica,&socket);
    }
    if (strcmp(argv[3],"--method=vigenere")==0){
    	enviar_datos_vigenere(&archivo,clave,&socket);
    }
    if (strcmp(argv[3],"--method=rc4")==0){
    	enviar_datos_rc4(&archivo,clave,&socket);
    }
    cerrar_archivo(&archivo);
    socket_uninit(&socket);
	return 0;
}
