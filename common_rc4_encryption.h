#ifndef COMMON_RC4_ENCRYPTION_H_
#define COMMON_RC4_ENCRYPTION_H_

#include <stdio.h>
#include <string.h>

typedef struct {
	int posicion_cifrado;
	int longitud_mensaje;
} rc4_t;

void swap(unsigned char *s, unsigned int i, unsigned int j);

void inicializar_rc4(char *key,unsigned int key_length,\
		unsigned char* S,rc4_t* self,int longitud_mensaje);

void rc4_cifrar(unsigned char* S,unsigned char* buffer,unsigned char*\
		buffer_procesado,rc4_t* self,int* i,int* j,int tamanio);

void rc4_descifrar(unsigned char* S,unsigned char* buffer_procesado,\
		unsigned char* buffer_normalizado,rc4_t* self,int* i,int* j,int tamanio);

#endif /* COMMON_VIGENERE_ENCRYPTION_H_ */
