#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_
#include <stdio.h>
#include <string.h>

int slice(const char* argumento,char* clave);

void limpiar_buffers(unsigned char* buffer1,\
		size_t size1,unsigned char* buffer2,size_t size2);



#endif /* COMMON_UTIL_H_ */
