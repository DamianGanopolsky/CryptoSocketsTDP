
#include "server_server.h"
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#define BUFFER_ESPERADO 64

/*
void descifrar(unsigned char* mensaje,unsigned char* mensaje_desencriptado,const char* metodo,char* clave,void* cifrador,int tamanio){

    if(atoi(clave)!=0){

    	int clave_numerica=atoi(clave);

    	descifrado_cesar(mensaje,mensaje_desencriptado,clave_numerica,sizeof(mensaje));
    }

    if(strcmp(metodo,"--method=vigenere")==0){
    	(struct vigenere_t*)cifrador;
    	descifrado_vigenere(mensaje,mensaje_desencriptado,clave,cifrador,tamanio);
    	//file_reader_iterate_vigenere(&file_reader,subbuff);
    }

    if(strcmp(metodo,"--method=rc4")==0){
    	file_reader_iterate_rc4(&file_reader,subbuff);
    }

}
*/
void recibir_mensaje_cesar(socket_t* socket_peer,int clave){

	unsigned char mensaje[64];
	ssize_t recibidos=BUFFER_ESPERADO;

	while(recibidos==BUFFER_ESPERADO){

		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if(recibidos<BUFFER_ESPERADO){
			unsigned char ultimo_mensaje[recibidos+1];
			unsigned char ultimo_mensaje_desencriptado[recibidos];
			//memset(ultimo_mensaje,0,sizeof(ultimo_mensaje));
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrado_cesar(ultimo_mensaje,ultimo_mensaje_desencriptado,clave,recibidos);
			//descifrar(ultimo_mensaje,ultimo_mensaje_desencriptado,metodo,subbuff,puntero_a_cifrador,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			printf("El mensaje es %s \n",ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[64];
		descifrado_cesar(mensaje,mensaje_desencriptado,clave,BUFFER_ESPERADO);
		//descifrar(mensaje,mensaje_desencriptado,metodo,subbuff,puntero_a_cifrador,BUFFER_ESPERADO);
		printf("El mensaje es %s \n",mensaje_desencriptado);
	}
}

void recibir_mensaje_vigenere(socket_t* socket_peer,char* clave){

	unsigned char mensaje[64];
	ssize_t recibidos=BUFFER_ESPERADO;
	vigenere_t vigenere;
	inicializar_vigenere(&vigenere,strlen((char*)clave));

	while(recibidos==BUFFER_ESPERADO){

		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if(recibidos<BUFFER_ESPERADO){

			unsigned char ultimo_mensaje[recibidos+1];
			unsigned char ultimo_mensaje_desencriptado[recibidos];
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrado_vigenere(ultimo_mensaje,ultimo_mensaje_desencriptado,clave,&vigenere,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			printf("El mensaje es %s \n",ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[64];
		descifrado_vigenere(mensaje,mensaje_desencriptado,clave,&vigenere,BUFFER_ESPERADO);
		printf("El mensaje es %s \n",mensaje_desencriptado);
	}
}


void recibir_mensaje_rc4(socket_t* socket_peer,char* clave){

	unsigned char mensaje[64];
	ssize_t recibidos=BUFFER_ESPERADO;
	rc4_t rc4;
	unsigned char S[256];
	memset(S,0,sizeof(S));
	inicializar_rc4(clave,strlen((char*)clave),S,&rc4,0);

	int i=0,j=0;

	while(recibidos==BUFFER_ESPERADO){

		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if(recibidos<BUFFER_ESPERADO){

			unsigned char ultimo_mensaje[recibidos+1];
			unsigned char ultimo_mensaje_desencriptado[recibidos];
			memcpy(ultimo_mensaje,mensaje,recibidos);
			//descifrado_vigenere(ultimo_mensaje,ultimo_mensaje_desencriptado,clave,&vigenere,recibidos);
			rc4_descifrar(S,ultimo_mensaje,ultimo_mensaje_desencriptado,&rc4,&i,&j,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			printf("El mensaje es %s \n",ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[64];
		rc4_descifrar(S,mensaje,mensaje_desencriptado,&rc4,&i,&j,recibidos);
		printf("El mensaje es %s \n",mensaje_desencriptado);
	}
}


void recibir_mensajes(socket_t* socket_peer,const char* metodo,const char* clave){

    int tamanio_clave= strlen(clave)-6;
    char subbuff[tamanio_clave+1];
    memcpy( subbuff, &clave[6], tamanio_clave );
    subbuff[tamanio_clave] = '\0';

    if(atoi(subbuff)!=0){

    	int clave_numerica=atoi(subbuff);
    	recibir_mensaje_cesar(socket_peer,clave_numerica);
    }

    if(strcmp(metodo,"--method=vigenere")==0){
    	recibir_mensaje_vigenere(socket_peer,subbuff);
    }

    if(strcmp(metodo,"--method=rc4")==0){
        	recibir_mensaje_rc4(socket_peer,subbuff);
        }
}
/*
    if(strcmp(metodo,"--method=vigenere")==0){
    	(struct vigenere_t*)cifrador;
    	descifrado_vigenere(mensaje,mensaje_desencriptado,clave,cifrador,tamanio);
    	//file_reader_iterate_vigenere(&file_reader,subbuff);
    }

	unsigned char mensaje[64];
	ssize_t recibidos=BUFFER_ESPERADO;
	void* puntero_a_cifrador;

	while(recibidos==BUFFER_ESPERADO){

		recibidos=socket_receive(socket_peer,mensaje, sizeof(mensaje));

		if(recibidos<BUFFER_ESPERADO){
			unsigned char ultimo_mensaje[recibidos+1];
			unsigned char ultimo_mensaje_desencriptado[recibidos];
			//memset(ultimo_mensaje,0,sizeof(ultimo_mensaje));
			memcpy(ultimo_mensaje,mensaje,recibidos);
			descifrar(ultimo_mensaje,ultimo_mensaje_desencriptado,metodo,subbuff,puntero_a_cifrador,recibidos);
			ultimo_mensaje_desencriptado[recibidos]=0;
			printf("El mensaje es %s \n",ultimo_mensaje_desencriptado);
			break;
		}
		unsigned char mensaje_desencriptado[64];
		descifrar(mensaje,mensaje_desencriptado,metodo,subbuff,puntero_a_cifrador,BUFFER_ESPERADO);
		printf("El mensaje es %s \n",mensaje_desencriptado);

	}
*/


