#include "common_vigenere_encryption.h"


void inicializar_vigenere(vigenere_t* self,int longitud_clave){
	self->posicion_cifrado=0;
	self->longitud_clave=longitud_clave;
}

void cifrado_vigenere(unsigned char* cadena,unsigned char*\
		cadena_procesada,char* clave,vigenere_t* self,int tamanio){
	//(vigenere_t *) self;
	for (int k=0; k<tamanio; k++){
		int indice_clave=(self->posicion_cifrado)%(self->longitud_clave);
		cadena_procesada[k]=cadena[k]+clave[indice_clave];
		self->posicion_cifrado++;
	}
}


void descifrado_vigenere(unsigned char* cadena_procesada,\
		unsigned char* cadena_normalizada,char* clave,\
		vigenere_t* self,int tamanio_buffer){
	for (int k=0; k<tamanio_buffer; k++){
		int indice_clave=(self->posicion_cifrado)%(self->longitud_clave);
		cadena_normalizada[k]=cadena_procesada[k]-clave[indice_clave];
		self->posicion_cifrado++;
	}
}
