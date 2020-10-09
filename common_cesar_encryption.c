#include "common_cesar_encryption.h"
#define BUFFER_SIZE 4

void cifrado(unsigned char* cadena,unsigned char* cadena_procesada){

	int i=0;
	int valor;
	int null_desplazado=191;
	char caracter;

	while((i<BUFFER_SIZE)){
		int valor=0;
		if(*(cadena+i)=='\0'){
			cadena_procesada[i]=(char)null_desplazado;
			break;
		}
		valor=(int)*(cadena+i);
		valor=valor+191;
		printf("cadena es %s \n",cadena);
		valor=valor%256;
		cadena_procesada[i]=(char)valor;
		i++;
	}

}

void descifrado(unsigned char* cadena_procesada,unsigned char* cadena_normalizada){
	int i=0;
	int valor;
	char caracter;

	while((i<BUFFER_SIZE)){
		int valor=0;
		if((int)*(cadena_procesada+i)==191){
			cadena_normalizada[i]='\0';
			break;
		}
		valor=(int)*(cadena_procesada+i);
		valor=valor-191;
		printf("cadena es %s \n",cadena_normalizada);
		valor=valor%256;
		cadena_normalizada[i]=(char)valor;
		i++;
	}
}

//void descifrado()
