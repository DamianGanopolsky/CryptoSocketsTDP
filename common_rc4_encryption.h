#ifndef COMMON_RC4_ENCRYPTION_H_
#define COMMON_RC4_ENCRYPTION_H_

#include <stdio.h>
#include <string.h>

void swap(unsigned char *s, unsigned int i, unsigned int j);

void inicializar_rc4(unsigned char *key,unsigned int key_length,unsigned char* S);

void rc4_cifrar(unsigned char* S,unsigned char* buffer,unsigned char* buffer_procesado);

void rc4_descifrar(unsigned char* S,unsigned char* buffer_procesado,unsigned char* buffer_normalizado);

#endif /* COMMON_VIGENERE_ENCRYPTION_H_ */
