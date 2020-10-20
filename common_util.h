#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_
#include <stdio.h>
#include <string.h>

//Recibe el argumento correspondiente a la clave que
//le llega al main y devuelve la clave sin el --key
int slice(const char* argumento,char* clave);

//Realiza la operacion memset, para "limpiar" los buffers
//Esto lo hace poniendole un \0 a todos los caracteres
//de los buffers
void limpiar_buffers(unsigned char* buffer1,\
		size_t size1,unsigned char* buffer2,size_t size2);

#endif /* COMMON_UTIL_H_ */
