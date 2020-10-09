#include "common_cesar_encryption.h"
#define BUFFER_SIZE 4

void cifrado(unsigned char* cadena,unsigned char* cadena_procesada){

	int i=0;
	int valor;
	char caracter;
	/*
	valor=(int)*cadena;
	valor=valor+5;
	valor=valor%256;
	*cadena_procesada= (char)valor;
	//printf("cadena es %s",cadena_cesar->cadena);
*/
	while((i<4)){
		int valor=0;
		if(*(cadena+i)=='\n'){
			cadena_procesada[i]='\0';
			break;
		}
		valor=(int)*(cadena+i);
		valor=valor+5;
		printf("cadena es %s \n",cadena);
		valor=valor%256;
		cadena_procesada[i]=(char)valor;
		i++;
	}

}

//void descifrado()
