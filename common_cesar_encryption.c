#include "common_cesar_encryption.h"
#define CANT_CARACTERES_ASCII 256


void cifrado_cesar(unsigned char* cadena,unsigned char* cadena_procesada,\
		int clave_numerica,int tamanio){
	int i=0;

	while((i<tamanio)){
		char caracter;
		caracter=*(cadena+i);
		caracter=caracter+clave_numerica;
		caracter=caracter%CANT_CARACTERES_ASCII;
		cadena_procesada[i]=caracter;
		i++;
	}
}

void descifrado_cesar(unsigned char* cadena_procesada,\
		unsigned char* cadena_normalizada,int clave_numerica,int tamanio){
	int i=0;

	while((i<tamanio)){
		char valor_decimal;
		valor_decimal=*(cadena_procesada+i);
		valor_decimal=valor_decimal-clave_numerica;
		valor_decimal=valor_decimal%CANT_CARACTERES_ASCII;
		cadena_normalizada[i]=valor_decimal;
		i++;
	}
}
