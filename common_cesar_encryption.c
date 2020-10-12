#include "common_cesar_encryption.h"

void cifrado_cesar(unsigned char* cadena,unsigned char* cadena_procesada,int clave_numerica,int tamanio){

	int i=0;
	char caracter;

	while((i<tamanio)){

		caracter=*(cadena+i);
		caracter=caracter+clave_numerica;
		caracter=caracter%256;
		cadena_procesada[i]=caracter;
		i++;
	}

}

void descifrado_cesar(unsigned char* cadena_procesada,unsigned char* cadena_normalizada,int clave_numerica,int tamanio){
	int i=0;
	char valor_decimal;

	while((i<tamanio)){

		valor_decimal=*(cadena_procesada+i);
		valor_decimal=valor_decimal-clave_numerica;
		valor_decimal=valor_decimal%256;
		cadena_normalizada[i]=valor_decimal;
		i++;
	}
}
