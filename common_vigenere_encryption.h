#ifndef COMMON_VIGENERE_ENCRYPTION_H_
#define COMMON_VIGENERE_ENCRYPTION_H_

#include <stdio.h>

typedef struct {
	int posicion_cifrado;
	int posicion_descifrado;
	int longitud_clave;
	int longitud_mensaje;
} vigenere_t;

void inicializar_vigenere(vigenere_t* self,int longitud,int longitud_mensaje);

void cifrado_vigenere(unsigned char* cadena,unsigned char* cadena_procesada,char* clave,vigenere_t* self);

void descifrado_vigenere(unsigned char* cadena_procesada,unsigned char* cadena_normalizada,char* clave,vigenere_t* self);

#endif /* COMMON_VIGENERE_ENCRYPTION_H_ */
