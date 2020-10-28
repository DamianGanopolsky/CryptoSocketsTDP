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


static void recibir_mensaje_cesar(socket_t* socket_peer,int clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;
	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		descifrado_cesar(mensaje,mensaje_desencriptado,clave,BUFFER_ESPERADO);
		fwrite(mensaje_desencriptado, 1, recibidos, stdout);
	}
}


static void recibir_mensaje_vigenere(socket_t* socket_peer,char* clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;
	vigenere_t vigenere;
	inicializar_vigenere(&vigenere,strlen((char*)clave));
	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		descifrado_vigenere(mensaje,mensaje_desencriptado,\
				clave,&vigenere,BUFFER_ESPERADO);
		fwrite(mensaje_desencriptado, 1, recibidos, stdout);
	}
}


static void recibir_mensaje_rc4(socket_t* socket_peer,char* clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;
	rc4_t rc4;
	inicializar_rc4(clave,strlen((char*)clave),&rc4);
	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		rc4_descifrar(mensaje,mensaje_desencriptado,&rc4,recibidos);
		fwrite(mensaje_desencriptado, 1, recibidos, stdout);
	}
}


void recibir_datos(const char* metodo,char* clave,socket_t* socket_peer){
    if (strcmp(metodo,"--method=cesar")==0){
    	int clave_numerica=atoi(clave);
    	recibir_mensaje_cesar(socket_peer,clave_numerica);
    }
    if (strcmp(metodo,"--method=vigenere")==0){
    	recibir_mensaje_vigenere(socket_peer,clave);
    }
    if (strcmp(metodo,"--method=rc4")==0){
    	recibir_mensaje_rc4(socket_peer,clave);
    }
}
