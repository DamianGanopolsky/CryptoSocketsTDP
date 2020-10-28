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


static int enviar_datos_cesar(archivo_t* archivo,int clave,socket_t* socket){
	unsigned char buffer[BUFFER_SIZE];
	int bytes_leidos;
	while (!feof(archivo->fp)) {
		bytes_leidos=fread(buffer, 1, BUFFER_SIZE, archivo->fp);  //Devuelve un size_t
		if(bytes_leidos==0){
			break;
		}
		unsigned char buffer_procesado[BUFFER_SIZE];
		cifrado_cesar(buffer,buffer_procesado,clave,BUFFER_SIZE);
		enviar_bloque(socket,buffer,sizeof(buffer),\
				buffer_procesado,bytes_leidos);
	}
    return 0;
}


static int enviar_datos_vigenere(archivo_t* archivo,\
		char* clave,socket_t* socket){
    unsigned char buff[BUFFER_SIZE];
	int bytes_leidos;
	vigenere_t vigenere_cliente;
    inicializar_vigenere(&vigenere_cliente,strlen((char*)clave));
	while (!feof(archivo->fp)) {
		bytes_leidos=fread(buff, 1, BUFFER_SIZE, archivo->fp);  //Devuelve un size_t
		if (bytes_leidos==0){
			break;
		}
		unsigned char buff_procesado[BUFFER_SIZE];
		cifrado_vigenere(buff,buff_procesado,clave,&vigenere_cliente,BUFFER_SIZE);
		enviar_bloque(socket,buff,sizeof(buff),buff_procesado\
				,bytes_leidos);
	}
    return 0;
}


static int enviar_datos_rc4(archivo_t* archivo,\
		char* clave,socket_t* socket){
    unsigned char buffer[BUFFER_SIZE],S_cliente[CANT_CARACTERES_ASCII];
    int bytes_leidos;
    rc4_t rc4_cliente;
	inicializar_rc4(clave, strlen((char*)clave),\
			S_cliente,&rc4_cliente);
	int i_cliente=0,j_cliente=0;  //Inicializo los estados de rc4
	while (!feof(archivo->fp)) {
		bytes_leidos=fread(buffer, 1, BUFFER_SIZE, archivo->fp);  //Devuelve un size_t
		if(bytes_leidos==0){
			break;
		}
		unsigned char buffer_procesado[BUFFER_SIZE];
		rc4_cifrar(S_cliente,buffer,buffer_procesado,\
						&rc4_cliente,&i_cliente,&j_cliente,bytes_leidos);
		enviar_bloque(socket,buffer,sizeof(buffer),buffer_procesado\
				,bytes_leidos);
	}
    return 0;
}


void enviar_datos(const char* metodo,char* clave\
		, archivo_t* archivo,socket_t* socket){
    if (strcmp(metodo,"--method=cesar")==0){
    	int clave_numerica=atoi(clave);
    	enviar_datos_cesar(archivo,clave_numerica,socket);
    }
    if (strcmp(metodo,"--method=vigenere")==0){
    	enviar_datos_vigenere(archivo,clave,socket);
    }
    if (strcmp(metodo,"--method=rc4")==0){
    	enviar_datos_rc4(archivo,clave,socket);
    }
}
