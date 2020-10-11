#include "client_file_reader.h"

#include <stdio.h>
#include <string.h>
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"

#define BUFFER_SIZE 64


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

int file_reader_iterate(file_reader_t* self){

    unsigned char buffer[BUFFER_SIZE];
    unsigned char buffer_procesado[BUFFER_SIZE];
    unsigned char buffer_normalizado[BUFFER_SIZE];
    unsigned char S_cliente[256];
    unsigned char S_servidor[256];
    rc4_t rc4_cliente;
    rc4_t rc4_servidor;
  //  vigenere_t vigenere;
    memset(S_cliente,0,sizeof(S_cliente));
    memset(S_servidor,0,sizeof(S_servidor));

    FILE* puntero;

    puntero=fopen("client_a_server.txt","w");

	memset(buffer_procesado,0,sizeof(buffer_procesado));
	memset(buffer,0,sizeof(buffer));
	memset(buffer_normalizado,0,sizeof(buffer_normalizado));

    fseek(self->fp, 0, SEEK_END);
    int longitud_total = ftell(self->fp);
    rewind(self->fp);

	unsigned char clave_rc4[]="queso";
	inicializar_rc4(clave_rc4, strlen((char*)clave_rc4),S_cliente,&rc4_cliente,longitud_total);
	inicializar_rc4(clave_rc4, strlen((char*)clave_rc4),S_servidor,&rc4_servidor,0);
	int i_cliente=0;
	int j_cliente=0;
	int i_servidor=0;
	int j_servidor=0;

   // char* clave_vigenere= "Secret";

   // inicializar_vigenere(&vigenere,strlen(clave_vigenere),longitud_total);

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t


		rc4_cifrar(S_cliente,buffer,buffer_procesado,&rc4_cliente,&i_cliente,&j_cliente);

		fwrite(buffer_procesado,1,BUFFER_SIZE,puntero);
		//memset(S_cliente,0,sizeof(S_cliente));
	//	memset(S_servidor,0,sizeof(S_servidor));

		rc4_descifrar(S_servidor,buffer_procesado,buffer_normalizado,&rc4_servidor,&i_servidor,&j_servidor);

		//cifrado_cesar(buffer,buffer_procesado);
		//cifrado_vigenere(buffer,buffer_procesado,clave_vigenere,&vigenere);
		//descifrado_vigenere(buffer_procesado,buffer_normalizado,clave_vigenere,&vigenere);
	//	descifrado_cesar(buffer_procesado,buffer_normalizado);

		memset(buffer_procesado,0,sizeof(buffer_procesado));
		memset(buffer,0,sizeof(buffer));
		memset(buffer_normalizado,0,sizeof(buffer_normalizado));

	}

    return 0;
}
