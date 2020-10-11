#include "client_file_reader.h"

#include <stdio.h>
#include <string.h>
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"

#define BUFFER_SIZE 4


int file_reader_init(file_reader_t* self, const char* file_name){

    self->fp=file_name != NULL ? fopen(file_name,"rb"): stdin;
    //ACA SE PUEDEN HACER VERIFICACIONES
    return 0;
}


int file_reader_uninit(file_reader_t* self){
    if(self->fp != stdin){  //STDIN nunca lo tiene que cerrar el proceso. Pero el archivo si
        fclose(self->fp);   //fclose tambien puede devolver errores asi que hay que chequear
    }
    return 0;
}

int file_reader_length(file_reader_t* self){

    fseek(self->fp, 0, SEEK_END);
    int longitud_mensaje = ftell(self->fp);
    rewind(self->fp);
    return longitud_mensaje;

}

int file_reader_iterate(file_reader_t* self){

    unsigned char buffer[BUFFER_SIZE];
    memset(buffer,0,sizeof(buffer));

    unsigned char S_cliente[256];
    unsigned char S_servidor[256];
    rc4_t rc4_cliente;
    rc4_t rc4_servidor;
    //vigenere_t vigenere_cliente;
    //vigenere_t vigenere_servidor;
    memset(S_cliente,0,sizeof(S_cliente));
    memset(S_servidor,0,sizeof(S_servidor));

   // FILE* puntero;

    //puntero=fopen("client_a_server.txt","w");

	int bytes_enviados=0;
	int tamanio;

	int longitud_mensaje=file_reader_length(self);
/*
    fseek(self->fp, 0, SEEK_END);
    int longitud_mensaje = ftell(self->fp);
    rewind(self->fp);
*/
	unsigned char clave[]="queso";
	inicializar_rc4(clave, strlen((char*)clave),S_cliente,&rc4_cliente,longitud_mensaje);
	inicializar_rc4(clave, strlen((char*)clave),S_servidor,&rc4_servidor,0);

	int i_cliente=0,j_cliente=0, i_servidor=0, j_servidor=0;

    //int clave_numerica=5;



   // inicializar_vigenere(&vigenere_cliente,strlen((char*)clave),longitud_mensaje);
    //inicializar_vigenere(&vigenere_servidor,strlen((char*)clave),longitud_mensaje);

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		if(longitud_mensaje-bytes_enviados-1<BUFFER_SIZE) tamanio=longitud_mensaje-bytes_enviados-1;

		else tamanio=BUFFER_SIZE;

		bytes_enviados=bytes_enviados+tamanio;

		if(tamanio<1) break;

	    unsigned char buffer_procesado[tamanio];
		unsigned char buffer_normalizado[tamanio];
		memset(buffer_procesado,0,sizeof(buffer_procesado));
		memset(buffer_normalizado,0,sizeof(buffer_normalizado));


		rc4_cifrar(S_cliente,buffer,buffer_procesado,&rc4_cliente,&i_cliente,&j_cliente,tamanio);

		//fwrite(buffer_procesado,1,BUFFER_SIZE,puntero);
		//memset(S_cliente,0,sizeof(S_cliente));
	//	memset(S_servidor,0,sizeof(S_servidor));

		rc4_descifrar(S_servidor,buffer_procesado,buffer_normalizado,&rc4_servidor,&i_servidor,&j_servidor,tamanio);

	//	cifrado_cesar(buffer,buffer_procesado,clave_numerica);
		//cifrado_vigenere(buffer,buffer_procesado,clave,&vigenere_cliente);
		//descifrado_vigenere(buffer_procesado,buffer_normalizado,clave,&vigenere_servidor,tamanio);
		//descifrado_cesar(buffer_procesado,buffer_normalizado,clave_numerica);

		memset(buffer_procesado,0,sizeof(buffer_procesado));
		memset(buffer,0,sizeof(buffer));
		memset(buffer_normalizado,0,sizeof(buffer_normalizado));

	}

    return 0;
}
