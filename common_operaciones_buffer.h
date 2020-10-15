#ifndef COMMON_OPERACIONES_BUFFER_H_
#define COMMON_OPERACIONES_BUFFER_H_

#include <stdio.h>
#include <string.h>


void limpiar_buffers(unsigned char* buffer1,\
		size_t size1,unsigned char* buffer2,size_t size2);

unsigned char* crear_buffer_vacio(size_t tamanio_buffer);

#endif
