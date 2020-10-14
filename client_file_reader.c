#include "client_file_reader.h"
#define BUFFER_SIZE 2


int file_reader_init(file_reader_t* self, const char* file_name){

	if(file_name!=NULL){
		self->fp=fopen(file_name,"rb");
	}
	else{
		printf("paso por aca\n");
		self->fp= stdin;
	}
    //ACA SE PUEDEN HACER VERIFICACIONES
    return 0;
}


int file_reader_uninit(file_reader_t* self){
    if(self->fp != stdin){
        fclose(self->fp);
    }
    return 0;
}

int file_reader_length(file_reader_t* self){

    fseek(self->fp, 0, SEEK_END);
    int longitud_mensaje = ftell(self->fp);
    rewind(self->fp);
    return longitud_mensaje;

}

int file_reader_iterate_cesar(file_reader_t* self,int clave,socket_t* socket){

	unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio=0;
	int longitud_mensaje=file_reader_length(self);
	int s;

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1){
			break;
		}

	    unsigned char buffer_procesado[tamanio];
		//unsigned char buffer_normalizado[tamanio];
		//limpiar_buffers(buffer_procesado,sizeof(buffer_procesado),buffer_normalizado,sizeof(buffer_normalizado));
		memset(buffer_procesado,0,sizeof(buffer_procesado));
		//fwrite(buffer_procesado,1,BUFFER_SIZE,puntero);
		cifrado_cesar(buffer,buffer_procesado,clave,tamanio);

		s=socket_send(socket,buffer_procesado,sizeof(buffer_procesado));

		printf("No se pudieron enviar %i caracteres \n",s);

		//descifrado_cesar(buffer_procesado,buffer_normalizado,clave,tamanio);

		limpiar_buffers(buffer,sizeof(buffer),buffer_procesado,sizeof(buffer_procesado));
		//memset(buffer_normalizado,0,sizeof(buffer_normalizado));

	}
    return 0;

}

int file_reader_iterate_vigenere(file_reader_t* self,char* clave,socket_t* socket){

    unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio=0;
	int longitud_mensaje=file_reader_length(self);
	//vigenere_t vigenere_cliente,vigenere_servidor;
	vigenere_t vigenere_cliente;
    inicializar_vigenere(&vigenere_cliente,strlen((char*)clave));
    //inicializar_vigenere(&vigenere_servidor,strlen((char*)clave),longitud_mensaje);

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1) break;

	    unsigned char buffer_procesado[tamanio];
	    memset(buffer_procesado,0,sizeof(buffer_procesado));
		//unsigned char buffer_normalizado[tamanio];
		//limpiar_buffers(buffer_procesado,sizeof(buffer_procesado),buffer_normalizado,sizeof(buffer_normalizado));
		//fwrite(buffer_procesado,1,BUFFER_SIZE,puntero);
		cifrado_vigenere(buffer,buffer_procesado,clave,&vigenere_cliente);

		socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
		//descifrado_vigenere(buffer_procesado,buffer_normalizado,clave,&vigenere_servidor,tamanio);

		limpiar_buffers(buffer,sizeof(buffer),buffer_procesado,sizeof(buffer_procesado));
		//memset(buffer_normalizado,0,sizeof(buffer_normalizado));

	}

    return 0;

}


int file_reader_iterate_rc4(file_reader_t* self,char* clave,socket_t* socket){

    unsigned char buffer[BUFFER_SIZE];
	int bytes_enviados=0,tamanio=0;
	int longitud_mensaje=file_reader_length(self);
    unsigned char S_cliente[256];
    memset(S_cliente,0,sizeof(S_cliente));
    //unsigned char S_servidor[256];
    //limpiar_buffers(S_cliente,sizeof(S_cliente),S_servidor,sizeof(S_servidor));
   // rc4_t rc4_cliente,rc4_servidor;
    rc4_t rc4_cliente;
	inicializar_rc4(clave, strlen((char*)clave),S_cliente,&rc4_cliente,longitud_mensaje);
	//inicializar_rc4(clave, strlen((char*)clave),S_servidor,&rc4_servidor,0);
	//int i_cliente=0,j_cliente=0, i_servidor=0, j_servidor=0;
	int i_cliente=0,j_cliente=0;

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1) break;

	    unsigned char buffer_procesado[tamanio];
	    memset(buffer_procesado,0,sizeof(buffer_procesado));
		//unsigned char buffer_normalizado[tamanio];
		//limpiar_buffers(buffer_procesado,sizeof(buffer_procesado),buffer_normalizado,sizeof(buffer_normalizado));
		//fwrite(buffer_procesado,1,BUFFER_SIZE,puntero);

		rc4_cifrar(S_cliente,buffer,buffer_procesado,&rc4_cliente,&i_cliente,&j_cliente,tamanio);

		socket_send(socket,buffer_procesado,sizeof(buffer_procesado));
		//rc4_descifrar(S_servidor,buffer_procesado,buffer_normalizado,&rc4_servidor,&i_servidor,&j_servidor,tamanio);

		limpiar_buffers(buffer,sizeof(buffer),buffer_procesado,sizeof(buffer_procesado));
		//memset(buffer_normalizado,0,sizeof(buffer_normalizado));

	}

    return 0;

}
