#define _POSIX_C_SOURCE 200112L
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "server_server.h"
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#define CANT_CARACTERES_ASCII 256
#define BUFFER_ESPERADO 64
#define METODO_CESAR 1
#define METODO_VIGENERE 2
#define METODO_RC4 3

static void desencriptar(unsigned char* mensaje,unsigned char* \
		mensaje_desencriptado,char* clave,int tamanio,int metodo,void* tda_t){
	if(metodo==METODO_CESAR){
		int clave_numerica=atoi(clave);
		descifrado_cesar(mensaje,mensaje_desencriptado,clave_numerica,tamanio);
	}
	if(metodo==METODO_VIGENERE){
		descifrado_vigenere(mensaje,mensaje_desencriptado,\
						clave,tda_t,tamanio);
	}
	if(metodo==METODO_RC4){
		rc4_descifrar(mensaje,mensaje_desencriptado,tda_t,tamanio);
	}
}


static void recibir_mensaje(socket_t* socket_peer,char* clave,void* tda_t,int metodo){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;
	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		desencriptar(mensaje,mensaje_desencriptado,clave,recibidos,metodo,tda_t);
		fwrite(mensaje_desencriptado, 1, recibidos, stdout);
	}
}


void recibir_datos(const char* metodo,char* clave,socket_t* socket_peer){
    if (strcmp(metodo,"--method=cesar")==0){
    	recibir_mensaje(socket_peer,clave,NULL,METODO_CESAR);
    }
    if (strcmp(metodo,"--method=vigenere")==0){
    	vigenere_t vigenere;
    	inicializar_vigenere(&vigenere,strlen((char*)clave));
    	recibir_mensaje(socket_peer,clave,&vigenere,METODO_VIGENERE);
    }
    if (strcmp(metodo,"--method=rc4")==0){
    	rc4_t rc4;
    	inicializar_rc4(clave,strlen((char*)clave),&rc4);
    	recibir_mensaje(socket_peer,clave,&rc4,METODO_RC4);
    }
}
