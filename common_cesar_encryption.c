#include "common_cesar_encryption.h"
#define BUFFER_SIZE 64

void cifrado_cesar(unsigned char* cadena,unsigned char* cadena_procesada){

	int i=0;
	//int null_desplazado=5;
	char caracter;

	while((i<BUFFER_SIZE)){

		if((*(cadena+i)=='\n')){
		//	cadena_procesada[i]=caracter;
			break;
		}
		caracter=*(cadena+i);
		caracter=caracter+5;
		caracter=caracter%256;

		cadena_procesada[i]=caracter;
		i++;
	}

}

void descifrado_cesar(unsigned char* cadena_procesada,unsigned char* cadena_normalizada){
	int i=0;
	char valor_decimal;

	while((i<BUFFER_SIZE)){



		if((*(cadena_procesada+i)=='\0')) break;

		valor_decimal=*(cadena_procesada+i);
		valor_decimal=valor_decimal-5;

		valor_decimal=valor_decimal%256;
		cadena_normalizada[i]=valor_decimal;
		i++;
	}
}
