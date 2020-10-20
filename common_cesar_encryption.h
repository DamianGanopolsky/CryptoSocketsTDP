#ifndef COMMON_CESAR_ENCRYPTION_H_
#define COMMON_CESAR_ENCRYPTION_H_

#include <stdio.h>

void cifrado_cesar(unsigned char* cadena,\
		unsigned char* cadena_procesada,int clave_numerica,int tamanio);

void descifrado_cesar(unsigned char* cadena_procesada,\
		unsigned char* cadena_normalizada,int clave_numerica,int tamanio);

#endif /* COMMON_CESAR_ENCRYPTION_H_ */
