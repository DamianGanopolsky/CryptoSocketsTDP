#include "common_cesar_encryption.h"

void cifrado(unsigned char* cadena){

	int i=0;
	int valor;
	char caracter;
	while((i<4)&&((*cadena+i)!='\0')){
		int a;
		valor=(int)*cadena+i;
		valor=valor+5;
		valor=valor%256;
		caracter=(char)valor;
	}






}

//void descifrado()
