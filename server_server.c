#include "server_server.h"
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#define BUFFER_ESPERADO 1
#define LARGO_VECTOR_CLAVE 300

void recibir_mensaje_cesar(socket_t* socket_peer,int clave){
	unsigned char mensaje[BUFFER_ESPERADO];
	ssize_t recibidos=BUFFER_ESPERADO;

	while (recibidos==BUFFER_ESPERADO){
		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if (recibidos<BUFFER_ESPERADO){
			unsigned char* ultimo_mensaje=malloc(sizeof(char)*(recibidos+1));
			unsigned char* ultimo_mensaje_desencriptado=malloc(sizeof(char)*(recibidos+1));
		//	unsigned char ultimo_mensaje[recibidos+1];
			//unsigned char ultimo_mensaje_desencriptado[recibidos+1];
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrado_cesar(ultimo_mensaje,\
					ultimo_mensaje_desencriptado,clave,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			//fprintf(stdout, "%s",ultimo_mensaje_desencriptado);
			printf("%s",ultimo_mensaje_desencriptado);
			free(ultimo_mensaje);
			free(ultimo_mensaje_desencriptado);
			shutdown(socket_peer->fd,SHUT_RDWR);
			break;
		}
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO+1];
		descifrado_cesar(mensaje,mensaje_desencriptado,clave,BUFFER_ESPERADO);
		mensaje_desencriptado[BUFFER_ESPERADO]=0;
		printf("%s",mensaje_desencriptado);
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
			unsigned char* ultimo_mensaje=malloc(sizeof(char)*(recibidos+1));
			unsigned char* ultimo_mensaje_desencriptado=malloc(sizeof(char)*(recibidos+1));
			//unsigned char ultimo_mensaje[recibidos+1];
			//unsigned char ultimo_mensaje_desencriptado[recibidos+1];
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrado_vigenere(ultimo_mensaje,ultimo_mensaje_desencriptado\
					,clave,&vigenere,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			//fprintf(stdout,"%s",ultimo_mensaje_desencriptado);
			printf("%s",ultimo_mensaje_desencriptado);
			free(ultimo_mensaje);
			free(ultimo_mensaje_desencriptado);
			shutdown(socket_peer->fd,SHUT_RDWR);
			break;
		}
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO+1];
		descifrado_vigenere(mensaje,mensaje_desencriptado,\
				clave,&vigenere,BUFFER_ESPERADO);
		mensaje_desencriptado[BUFFER_ESPERADO]=0;
	//	fprintf(stdout,"%s",mensaje_desencriptado);
		printf("%s",mensaje_desencriptado);
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
			//unsigned char ultimo_mensaje[recibidos+1];
			//unsigned char ultimo_mensaje_desencriptado[recibidos+1];
			unsigned char* ultimo_mensaje=malloc(sizeof(char)*(recibidos+1));
			unsigned char* ultimo_mensaje_desencriptado=malloc(sizeof(char)*(recibidos+1));
			memcpy(ultimo_mensaje,mensaje,recibidos);
			rc4_descifrar(S,ultimo_mensaje,ultimo_mensaje_desencriptado\
					,&rc4,&i,&j,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			printf("%s",ultimo_mensaje_desencriptado);
			//fprintf(stdout,"%s",ultimo_mensaje_desencriptado);
			free(ultimo_mensaje);
			free(ultimo_mensaje_desencriptado);
			shutdown(socket_peer->fd,SHUT_RDWR);
			break;
		}
		unsigned char mensaje_desencriptado[BUFFER_ESPERADO+1];
		rc4_descifrar(S,mensaje,mensaje_desencriptado,&rc4,&i,&j,recibidos);
		mensaje_desencriptado[BUFFER_ESPERADO]=0;
		printf("%s",mensaje_desencriptado);
	}
}


void recibir_mensajes(socket_t* socket_peer,\
		const char* metodo,const char* clave){
    int tamanio_clave= strlen(clave)-6;
    char subbuff[LARGO_VECTOR_CLAVE];
    memset(subbuff,0,sizeof(subbuff));
    memcpy(subbuff,&clave[6],tamanio_clave);
    subbuff[tamanio_clave] = '\0';

    if (atoi(subbuff)!=0){
    	int clave_numerica=atoi(subbuff);
    	recibir_mensaje_cesar(socket_peer,clave_numerica);
    }
    if (strcmp(metodo,"--method=vigenere")==0){
    	recibir_mensaje_vigenere(socket_peer,subbuff);
    }
    if (strcmp(metodo,"--method=rc4")==0){
        	recibir_mensaje_rc4(socket_peer,subbuff);
        }
}
