#include "common_util.h"
#define ERROR -1
#define EXITO 0
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

/*
void limpiar_buffers(unsigned char* buffer1,size_t size1,\
		unsigned char* buffer2,size_t size2){
	if(buffer1!=NULL){
		memset(buffer1,0,size1);
	}
	if(buffer2!=NULL){
		memset(buffer2,0,size2);
	}
}
*/
