#include "client_procesar_datos.h"
#define BUFFER_SIZE 64
#define ERROR -1
#define EXITO 0

int abrir_archivo(archivo_t* self, const char* file_name){
	if (file_name!=NULL){
		self->fp=fopen(file_name,"rb");
		if (self->fp==NULL){
			fprintf(stderr,"No se pudo leer el archivo\n");
			return ERROR;
		}
	}else{
		self->fp= stdin;
	}
    return EXITO;
}


int cerrar_archivo(archivo_t* self){
    if (self->fp != stdin){
        fclose(self->fp);
    }
    return 0;
}

int longitud_archivo(archivo_t* self){
    fseek(self->fp, 0, SEEK_END);
    int longitud_mensaje = ftell(self->fp);
    rewind(self->fp);
    return longitud_mensaje;
}


void enviar_datos(const char* argumento,char* clave, archivo_t* archivo,socket_t* socket){
    if (strcmp(argumento,"--method=cesar")==0){
    	int clave_numerica=atoi(clave);
    	enviar_datos_cesar(archivo,clave_numerica,socket);
    }
    if (strcmp(argumento,"--method=vigenere")==0){
    	enviar_datos_vigenere(archivo,clave,socket);
    }
    if (strcmp(argumento,"--method=rc4")==0){
    	enviar_datos_rc4(archivo,clave,socket);
    }
}

int enviar_datos_cesar(archivo_t* self,int clave,socket_t* socket){
	unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio;
	int longitud_mensaje=longitud_archivo(self);

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if (longitud_mensaje-bytes_enviados<BUFFER_SIZE){
			tamanio=longitud_mensaje-bytes_enviados;
		    unsigned char* buffer_procesado=malloc(sizeof(char)*tamanio);
		    memset(buffer_procesado,0,tamanio);
		    cifrado_cesar(buffer,buffer_procesado,clave,tamanio);
			socket_send(socket,buffer_procesado,tamanio);
			free(buffer_procesado);
		}else{
			tamanio=BUFFER_SIZE;
		    unsigned char buffer_procesado[BUFFER_SIZE];
		    memset(buffer_procesado,0,sizeof(buffer_procesado));
		    cifrado_cesar(buffer,buffer_procesado,clave,tamanio);
			socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
			limpiar_buffers(buffer,sizeof(buffer),\
					buffer_procesado,sizeof(buffer_procesado));
		}
		bytes_enviados=bytes_enviados+tamanio;
	}
    return 0;
}

int enviar_datos_vigenere(archivo_t* self,char* clave,socket_t* socket){
    unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio;
	int longitud_mensaje=longitud_archivo(self);
	vigenere_t vigenere_cliente;
    inicializar_vigenere(&vigenere_cliente,strlen((char*)clave));

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if (longitud_mensaje-bytes_enviados<BUFFER_SIZE){
			tamanio=longitud_mensaje-bytes_enviados;
		    unsigned char* buffer_procesado=malloc(sizeof(char)*tamanio);
		    memset(buffer_procesado,0,tamanio);
			cifrado_vigenere(buffer,buffer_procesado,clave,&vigenere_cliente,tamanio);
			socket_send(socket,buffer_procesado,tamanio);
			free(buffer_procesado);
			//bytes_enviados=bytes_enviados+tamanio;
		}else{
			tamanio=BUFFER_SIZE;
		    unsigned char buffer_procesado[BUFFER_SIZE];
		    memset(buffer_procesado,0,sizeof(buffer_procesado));
			cifrado_vigenere(buffer,buffer_procesado,clave,&vigenere_cliente,BUFFER_SIZE);
			socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
			limpiar_buffers(buffer,sizeof(buffer),\
					buffer_procesado,sizeof(buffer_procesado));
			//bytes_enviados=bytes_enviados+BUFFER_SIZE;
		}
		bytes_enviados=bytes_enviados+tamanio;
	}
    return 0;
}


int enviar_datos_rc4(archivo_t* self,\
		char* clave,socket_t* socket){
    unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio;
	int longitud_mensaje=longitud_archivo(self);
    unsigned char S_cliente[256];
    memset(S_cliente,0,sizeof(S_cliente));
    rc4_t rc4_cliente;
	inicializar_rc4(clave, strlen((char*)clave),\
			S_cliente,&rc4_cliente,longitud_mensaje);

	int i_cliente=0,j_cliente=0;  //Inicializo los estados de rc4

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if (longitud_mensaje-bytes_enviados<BUFFER_SIZE){
			tamanio=longitud_mensaje-bytes_enviados;
		    unsigned char* buffer_procesado=malloc(sizeof(char)*tamanio);
		    memset(buffer_procesado,0,tamanio);
		    rc4_cifrar(S_cliente,buffer,buffer_procesado,\
		    				&rc4_cliente,&i_cliente,&j_cliente,tamanio);
			socket_send(socket,buffer_procesado,tamanio);
			free(buffer_procesado);
		}else{
			tamanio=BUFFER_SIZE;
		    unsigned char buffer_procesado[BUFFER_SIZE];
		    //memset(buffer_procesado,0,sizeof(buffer_procesado));
		    rc4_cifrar(S_cliente,buffer,buffer_procesado,\
		    				&rc4_cliente,&i_cliente,&j_cliente,tamanio);
			socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
			limpiar_buffers(buffer,sizeof(buffer),\
					buffer_procesado,sizeof(buffer_procesado));
		}
		bytes_enviados=bytes_enviados+tamanio;
	}
    return 0;
}
