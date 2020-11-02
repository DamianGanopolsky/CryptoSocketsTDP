#include <stddef.h>
#include "common_rc4_encryption.h"
#define CANT_CARACTERES_ASCII 256

//Hace un swap entre el caracter de la posicion i con
// el caracter de la posicion j, del vector S
static void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void inicializar_rc4(char *key,unsigned int key_length,unsigned char* S) {
	int i,j;
    for (i = 0; i < CANT_CARACTERES_ASCII; i++){
    	S[i] = i;
    }
    for (i = j = 0; i < CANT_CARACTERES_ASCII; i++) {
        j = (j + key[i % key_length] + S[i]) % CANT_CARACTERES_ASCII;
        swap(S, i, j);
    }
}


void rc4_cifrar(unsigned char* S,unsigned char* buffer,unsigned char*\
		buffer_procesado,int* i,int* j,int tamanio){
	size_t k=0;
	while (k<tamanio){
		int indice;
        *i = (*i + 1) % CANT_CARACTERES_ASCII;
        *j = (*j + S[*i]) % CANT_CARACTERES_ASCII;
        swap(S, *i, *j);
        indice=(S[*i] + S[*j]) % CANT_CARACTERES_ASCII;
        buffer_procesado[k]=buffer[k]^S[indice];
        k++;
    }
}

void rc4_descifrar(unsigned char* S,unsigned char* buffer_procesado,\
		unsigned char* buffer_normalizado,int* i,int* j,int tamanio) {
	int k=0;
	while (k<tamanio){
		int indice;
        *i = (*i + 1) % CANT_CARACTERES_ASCII;
        *j = (*j + S[*i]) % CANT_CARACTERES_ASCII;
        swap(S, *i, *j);
        indice=(S[*i] + S[*j]) % CANT_CARACTERES_ASCII;
        buffer_normalizado[k]=buffer_procesado[k]^S[indice];
        k++;
    }
}
