#ifndef COMMON_VIGENERE_ENCRYPTION_H_
#define COMMON_VIGENERE_ENCRYPTION_H_

#include <stdio.h>
#include <string.h>

typedef struct {
	int posicion_cifrado;
	int longitud_clave;
} vigenere_t;

void inicializar_vigenere(vigenere_t* self,int longitud,int longitud_mensaje);

void cifrado_vigenere(unsigned char* cadena,unsigned char* cadena_procesada,unsigned char* clave,vigenere_t* self);

void descifrado_vigenere(unsigned char* cadena_procesada,unsigned char* cadena_normalizada,unsigned char* clave,vigenere_t* self,int tamanio_buffer);

#endif /* COMMON_VIGENERE_ENCRYPTION_H_ */
