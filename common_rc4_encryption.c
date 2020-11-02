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


void inicializar_rc4(char *key,unsigned int key_length,\
		rc4_t* self){
	int i,j;
    for (i = 0; i < CANT_CARACTERES_ASCII; i++){
    	self->S[i] = i;
    }
    for (i = j = 0; i < CANT_CARACTERES_ASCII; i++) {
        j = (j + key[i % key_length] + self->S[i]) % CANT_CARACTERES_ASCII;
        swap(self->S, i, j);
    }
    self->i=0;
    self->j=0;
}


void rc4_cifrar(unsigned char* buffer,unsigned char*\
		buffer_procesado,rc4_t* self,int tamanio){
	size_t k=0;
	while (k<tamanio){
		int indice;
		self->i=(self->j+1) % CANT_CARACTERES_ASCII;
		self->j = (self->j+self->S[self->i]) % CANT_CARACTERES_ASCII;
		swap(self->S,self->i,self->j);
		indice=(self->S[self->i]+self->S[self->j]) % CANT_CARACTERES_ASCII;
		buffer_procesado[k]=buffer[k]^self->S[indice];
        k++;
    }
}

void rc4_descifrar(unsigned char* buffer_procesado,\
		unsigned char* buffer_normalizado,rc4_t* self,int tamanio) {
	int k=0;
	while (k<tamanio){
		int indice;
		self->i=(self->j+1) % CANT_CARACTERES_ASCII;
		self->j = (self->j+self->S[self->i]) % CANT_CARACTERES_ASCII;
		swap(self->S,self->i,self->j);
		indice=(self->S[self->i]+self->S[self->j]) % CANT_CARACTERES_ASCII;
		buffer_normalizado[k]=buffer_procesado[k]^self->S[indice];
        k++;
    }
}
