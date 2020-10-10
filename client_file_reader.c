#include "client_file_reader.h"

#include <stdio.h>
#include <string.h>
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"

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
  //  vigenere_t vigenere;
	memset(buffer_procesado,0,sizeof(buffer_procesado));
	memset(buffer,0,sizeof(buffer));
	memset(buffer_normalizado,0,sizeof(buffer_normalizado));


  /*  char* clave_vigenere= "Secret";
    fseek(self->fp, 0, SEEK_END);
    int longitud_total = ftell(self->fp);
    rewind(self->fp);
    inicializar_vigenere(&vigenere,strlen(clave_vigenere),longitud_total);
*/
	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t


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
