#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "client_client.h"
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#define BUFFER_SIZE 64
#define CANT_CARACTERES_ASCII 256
#define ERROR -1
#define EXITO 0
#define METODO_CESAR 1
#define METODO_VIGENERE 2
#define METODO_RC4 3


int abrir_y_validar_archivo(int argc,char const *argv[],\
		archivo_t* archivo,socket_t* socket){
	if(argc<5){
		fprintf(stderr,"Cantidad de parametros invalidos \n");
		return ERROR;
	}
    if (argc==5){ //Si son 5 argumentos, la entrada es por stdin
    	archivo->fp= stdin;
    }else{
    	archivo->fp=fopen(argv[6],"rb");
    			if (archivo->fp==NULL){
    				fprintf(stderr,"No se pudo leer el archivo\n");
    				return ERROR;
    			}
    }
    return EXITO;
}

int cerrar_archivo(archivo_t* archivo){
    if (archivo->fp != stdin){
        fclose(archivo->fp);
    }
    return 0;
}

static void enviar_bloque(socket_t* socket,\
		unsigned char* buffer,size_t buffer_len,unsigned char* buffer_procesado,\
		size_t buffer_proc_len){
	socket_send(socket,buffer_procesado,buffer_proc_len);
	memset(buffer,0,buffer_len);
	memset(buffer_procesado,0,buffer_proc_len);
}

//Encripta el mensaje dado usando el metodo pasado como parametro,
//el mensaje desencriptado va a guardarse en el "buffer_procesado"
static void encriptar(unsigned char* buffer,unsigned char* buffer_procesado,\
		char* clave,void* tipo,int bytes_leidos,int cifrador_a_usar,unsigned char* S,
		int* i,int* j){
	if(cifrador_a_usar==METODO_CESAR){
		int clave_numerica=atoi(clave);
		cifrado_cesar(buffer,buffer_procesado,clave_numerica,bytes_leidos);
	}
	if(cifrador_a_usar==METODO_VIGENERE){
		cifrado_vigenere(buffer,buffer_procesado,clave,tipo,bytes_leidos);
	}
	if(cifrador_a_usar==METODO_RC4){
		rc4_cifrar(S,buffer,buffer_procesado,\
								i,j,bytes_leidos);
	}
}

//Funcion generica para el envio del mensaje en cualquier metodo
static int enviar_mensaje(archivo_t* archivo,socket_t* socket,\
		char* clave,void* tda,int cifrador_a_usar,unsigned char* S,int* i,int* j){
    unsigned char buff[BUFFER_SIZE];
	while (!feof(archivo->fp)) {
		int bytes_leidos=fread(buff, 1, BUFFER_SIZE, archivo->fp);
		if (bytes_leidos==0){
			break;
		}
		unsigned char buff_procesado[BUFFER_SIZE];
		encriptar(buff,buff_procesado,clave,tda,bytes_leidos,cifrador_a_usar,S,i,j);
		enviar_bloque(socket,buff,sizeof(buff),buff_procesado\
				,bytes_leidos);
	}
    return 0;
}

void enviar_datos(const char* metodo,char* clave\
		, archivo_t* archivo,socket_t* socket){
    if (strcmp(metodo,"--method=cesar")==0){
    	enviar_mensaje(archivo,socket,clave,NULL,METODO_CESAR,NULL,NULL,NULL);
    }
    if (strcmp(metodo,"--method=vigenere")==0){
    	vigenere_t vigenere_cliente;
        inicializar_vigenere(&vigenere_cliente,strlen((char*)clave));
    	enviar_mensaje(archivo,socket,clave,&vigenere_cliente,\
    			METODO_VIGENERE,NULL,NULL,NULL);
    }
    if (strcmp(metodo,"--method=rc4")==0){
    	unsigned char S_cliente[CANT_CARACTERES_ASCII];
    	int i_cliente=0,j_cliente=0;
    	inicializar_rc4(clave, strlen((char*)clave),\
    			S_cliente);
    	enviar_mensaje(archivo,socket,clave,NULL,METODO_RC4,\
    			S_cliente,&i_cliente,&j_cliente);
    }
}
