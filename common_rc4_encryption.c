#include "common_rc4_encryption.h"

void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void inicializar_rc4(unsigned char *key,unsigned int key_length,unsigned char* S) {
	int i,j;

    for (i = 0; i < 256; i++){
    	S[i] = i;

    }

    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }

    i = j = 0;
}

void rc4_cifrar(unsigned char* S,unsigned char* buffer,unsigned char* buffer_procesado) {
	int i=0;
	int j=0;
	int k=0;
	int indice;

    while(k< strlen((char*)buffer)){
	//while(k< 4){

        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        indice=(S[i] + S[j]) & 255;
        buffer_procesado[k]=buffer[k]^S[indice];
        k++;

    }
}

void rc4_descifrar(unsigned char* S,unsigned char* buffer_procesado,unsigned char* buffer_normalizado) {
	int i=0;
	int j=0;
	int k=0;
	int indice;

    while(k< strlen((char*)buffer_procesado)){
//	while(k< 4){

        i = (i + 1) & 255;
        j = (j + S[i]) & 255;
        swap(S, i, j);
        indice=(S[i] + S[j]) & 255;
        buffer_normalizado[k]=buffer_procesado[k]^S[indice];
        k++;

    }
}



