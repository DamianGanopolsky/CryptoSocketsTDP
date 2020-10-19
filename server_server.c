#include "server_server.h"
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#define BUFFER_ESPERADO 64

void recibir_mensaje_cesar(socket_t* socket_peer,int clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;

	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if (recibidos<BUFFER_ESPERADO){
			unsigned char* ultimo_mensaje=malloc(sizeof(char)*(recibidos));
			unsigned char* ultimo_mensaje_desencriptado\
			=malloc(sizeof(char)*(recibidos));
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrado_cesar(ultimo_mensaje,\
					ultimo_mensaje_desencriptado,clave,recibidos);
			fwrite(ultimo_mensaje_desencriptado, 1, recibidos, stdout);
			free(ultimo_mensaje);
			free(ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		memset(mensaje_desencriptado,0,sizeof(mensaje_desencriptado));
		descifrado_cesar(mensaje,mensaje_desencriptado,clave,BUFFER_ESPERADO);
		fwrite(mensaje_desencriptado, 1, BUFFER_ESPERADO, stdout);
	}
}

void recibir_mensaje_vigenere(socket_t* socket_peer,char* clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;
	vigenere_t vigenere;
	inicializar_vigenere(&vigenere,strlen((char*)clave));

	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if (recibidos<BUFFER_ESPERADO){
			unsigned char* ultimo_mensaje=malloc(sizeof(char)*(recibidos));
			unsigned char* ultimo_mensaje_desencriptado=\
					malloc(sizeof(char)*(recibidos));
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrado_vigenere(ultimo_mensaje,ultimo_mensaje_desencriptado\
					,clave,&vigenere,recibidos);
			fwrite(ultimo_mensaje_desencriptado, 1, recibidos, stdout);
			free(ultimo_mensaje);
			free(ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		memset(mensaje_desencriptado,0,sizeof(mensaje_desencriptado));
		descifrado_vigenere(mensaje,mensaje_desencriptado,\
				clave,&vigenere,BUFFER_ESPERADO);
		fwrite(mensaje_desencriptado, 1, BUFFER_ESPERADO, stdout);
	}
}


void recibir_mensaje_rc4(socket_t* socket_peer,char* clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;
	rc4_t rc4;
	unsigned char S[256];
	memset(S,0,sizeof(S));
	inicializar_rc4(clave,strlen((char*)clave),S,&rc4,0);
	int i=0,j=0;

	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if (recibidos<BUFFER_ESPERADO){
			unsigned char* ultimo_mensaje=malloc(sizeof(char)*(recibidos));
			unsigned char* ultimo_mensaje_desencriptado=malloc(sizeof(char)*(recibidos));
			memcpy(ultimo_mensaje,mensaje,recibidos);
			rc4_descifrar(S,ultimo_mensaje,ultimo_mensaje_desencriptado\
					,&rc4,&i,&j,recibidos);
			fwrite(ultimo_mensaje_desencriptado, 1, recibidos, stdout);
			free(ultimo_mensaje);
			free(ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO];
		memset(mensaje_desencriptado,0,sizeof(mensaje_desencriptado));
		rc4_descifrar(S,mensaje,mensaje_desencriptado,&rc4,&i,&j,recibidos);
		fwrite(mensaje_desencriptado, 1, BUFFER_ESPERADO, stdout);
	}
}
