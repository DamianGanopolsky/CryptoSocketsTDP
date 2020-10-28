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

void inicializar_rc4(char *key,unsigned int key_length,unsigned char* S\
		,rc4_t* self) {
	int i,j;
    for (i = 0; i < CANT_CARACTERES_ASCII; i++){
    	S[i] = i;
    }
    for (i = j = 0; i < CANT_CARACTERES_ASCII; i++) {
        j = (j + key[i % key_length] + S[i]) % CANT_CARACTERES_ASCII;
        swap(S, i, j);
    }
}
/*
void inicializar_rc4(char *key,unsigned int key_length,\
		unsigned char* S,rc4_t* self){
	int i,j;
	//self->longitud_mensaje=longitud_mensaje;
    for (i = 0; i < 256; i++){
    	self->S[i] = i;
    }
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + self->S[i]) & 255;
        swap(self->S, i, j);
    }
    self->i=0;
    self->j=0;
}
*/

void rc4_cifrar(unsigned char* S,unsigned char* buffer,unsigned char*\
		buffer_procesado,rc4_t* self,int* i,int* j,int tamanio){
	size_t k=0;
	while (k<tamanio){
		int indice;
		//if ((buffer[k]=='\0')||(buffer[k]=='\n')){
			//break;
		//}
		//if ((buffer[k]=='\0')){
			//break;
		//}
		/*
		self->i=(self->j+1) % 256;
		self->j = (self->j+self->S[self->i]) % 256;
		swap(self->S,self->i,self->j);
		indice=(self->S[self->i]+self->S[self->j]) % 256;
		buffer_procesado[k]=buffer[k]^self->S[indice]; */
        *i = (*i + 1) % CANT_CARACTERES_ASCII;
        *j = (*j + S[*i]) % CANT_CARACTERES_ASCII;
        swap(S, *i, *j);
        indice=(S[*i] + S[*j]) % CANT_CARACTERES_ASCII;
        buffer_procesado[k]=buffer[k]^S[indice];
        k++;
    }
}

void rc4_descifrar(unsigned char* S,unsigned char* buffer_procesado,\
		unsigned char* buffer_normalizado,rc4_t* self,int* i,int* j,int tamanio) {
	int k=0;
	while (k<tamanio){
		int indice;
		/*
		self->i=(self->j+1) & 255;
		self->j = (self->j+self->S[self->i]) & 255;
		swap(self->S,self->i,self->j);
		indice=(self->S[self->i]+self->S[self->j]) & 255;
		buffer_normalizado[k]=buffer_procesado[k]^self->S[indice]; */

        *i = (*i + 1) % CANT_CARACTERES_ASCII;
        *j = (*j + S[*i]) % CANT_CARACTERES_ASCII;
        swap(S, *i, *j);
        indice=(S[*i] + S[*j]) % CANT_CARACTERES_ASCII;
        buffer_normalizado[k]=buffer_procesado[k]^S[indice];
        k++;
    }
}
