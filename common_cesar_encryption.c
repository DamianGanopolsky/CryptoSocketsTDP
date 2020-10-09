#include "common_cesar_encryption.h"
#define BUFFER_SIZE 3

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
	while((i<3)){
		int valor=0;
		if(*(cadena+i)=='\0'){
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
