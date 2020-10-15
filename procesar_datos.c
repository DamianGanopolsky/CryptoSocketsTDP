#include "procesar_datos.h"
#define BUFFER_SIZE 64


int abrir_archivo(archivo_t* self, const char* file_name){

	if(file_name!=NULL){
		self->fp=fopen(file_name,"rb");
	}
	else{
		self->fp= stdin;
	}
    //ACA SE PUEDEN HACER VERIFICACIONES
    return 0;
}


int cerrar_archivo(archivo_t* self){
    if(self->fp != stdin){
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

int enviar_datos_cesar(archivo_t* self,int clave,socket_t* socket){

	unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio=0;
	int longitud_mensaje=longitud_archivo(self);
	//int s;

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1){
			break;
		}

	    unsigned char buffer_procesado[tamanio];
		memset(buffer_procesado,0,sizeof(buffer_procesado));
		cifrado_cesar(buffer,buffer_procesado,clave,tamanio);
		//s=socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
		socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
		limpiar_buffers(buffer,sizeof(buffer),buffer_procesado,sizeof(buffer_procesado));

	}
    return 0;

}

int enviar_datos_vigenere(archivo_t* self,char* clave,socket_t* socket){

    unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio=0;
	int longitud_mensaje=longitud_archivo(self);
	vigenere_t vigenere_cliente;
    inicializar_vigenere(&vigenere_cliente,strlen((char*)clave));

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1) break;

	    unsigned char buffer_procesado[tamanio];
	    memset(buffer_procesado,0,sizeof(buffer_procesado));
		cifrado_vigenere(buffer,buffer_procesado,clave,&vigenere_cliente,tamanio);
		socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
		limpiar_buffers(buffer,sizeof(buffer),buffer_procesado,sizeof(buffer_procesado));

	}

    return 0;

}


int enviar_datos_rc4(archivo_t* self,char* clave,socket_t* socket){

    unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio=0;
	int longitud_mensaje=longitud_archivo(self);
    unsigned char S_cliente[256];
    memset(S_cliente,0,sizeof(S_cliente));
    rc4_t rc4_cliente;
	inicializar_rc4(clave, strlen((char*)clave),S_cliente,&rc4_cliente,longitud_mensaje);
	int i_cliente=0,j_cliente=0;

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1) break;

	    unsigned char buffer_procesado[tamanio];
	    memset(buffer_procesado,0,sizeof(buffer_procesado));
		rc4_cifrar(S_cliente,buffer,buffer_procesado,&rc4_cliente,&i_cliente,&j_cliente,tamanio);
		socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
		limpiar_buffers(buffer,sizeof(buffer),buffer_procesado,sizeof(buffer_procesado));

	}

    return 0;

}
