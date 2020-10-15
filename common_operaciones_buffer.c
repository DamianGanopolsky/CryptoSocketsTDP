#include "common_operaciones_buffer.h"

void limpiar_buffers(unsigned char* buffer1,size_t size1,\
		unsigned char* buffer2,size_t size2){
	if(buffer1!=NULL){
		memset(buffer1,0,size1);
	}
	if(buffer2!=NULL){
		memset(buffer2,0,size2);
	}
}
