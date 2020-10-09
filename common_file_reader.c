#include "common_file_reader.h"

#include <stdio.h>
#include "common_cesar_encryption.h"

#define BUFFER_SIZE 1


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
   // unsigned char* cadena_nueva;

	while (!feof(self->fp)) {
		fread(buffer, 1, BUFFER_SIZE, self->fp);  //Devuelve un size_t

		printf("\033[0;31m");
		cifrado(buffer);

		//fwrite(buffer, 1, result, stdout);
		//fprintf(stdout,"\n fin buffer \n");
		printf("\033[0m");
	}

    return 0;
}
