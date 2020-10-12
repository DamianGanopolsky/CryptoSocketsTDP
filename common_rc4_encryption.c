#include "common_rc4_encryption.h"

#define BUFFER_SIZE 64

void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void inicializar_rc4(char *key,unsigned int key_length,unsigned char* S,rc4_t* self,int longitud_mensaje) {
	int i,j;
	self->posicion_cifrado=0;
	self->longitud_mensaje=longitud_mensaje;

    for (i = 0; i < 256; i++){
    	S[i] = i;

    }

    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }

    i = j = 0;
}

void rc4_cifrar(unsigned char* S,unsigned char* buffer,unsigned char* buffer_procesado,rc4_t* self,int* i,int* j,int tamanio) {

	size_t k=0;
	int indice;

	while(k<tamanio){

		if((buffer[k]=='\0')||(buffer[k]=='\n')) break;

    	self->posicion_cifrado++;
    	if(self->posicion_cifrado==self->longitud_mensaje) break;
        *i = (*i + 1) & 255;
        *j = (*j + S[*i]) & 255;
        swap(S, *i, *j);
        indice=(S[*i] + S[*j]) & 255;
        buffer_procesado[k]=buffer[k]^S[indice];
        k++;


    }
}

void rc4_descifrar(unsigned char* S,unsigned char* buffer_procesado,unsigned char* buffer_normalizado,rc4_t* self,int* i,int* j,int tamanio) {

	int k=0;
	int indice;

  //  while(k< strlen((char*)buffer_procesado)){
	while(k<tamanio){

		//if(buffer_procesado[k]=='\0') break;

        *i = (*i + 1) & 255;
        *j = (*j + S[*i]) & 255;
        swap(S, *i, *j);
        indice=(S[*i] + S[*j]) & 255;
        buffer_normalizado[k]=buffer_procesado[k]^S[indice];
        k++;
        self->posicion_cifrado++;

    }
}



