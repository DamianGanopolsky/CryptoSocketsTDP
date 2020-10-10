#include <stdio.h>

#include "client_file_reader.h"



int main(int argc, char const *argv[]) {

    file_reader_t file_reader;  //ACA DECIDIMOS QUE EL FILE READER VIVA EN EL STACK
   // file_reader_t* file_reader=malloc(sizeof());  ACA DECIDIRIAMOS QUE VIVA EN EL HEAP. LO DECIDIMOS NOSOTROS.
    if(argc>1){
    	file_reader_init(&file_reader,argv[1]);
    }
    else {
    	file_reader_init(&file_reader, NULL); //ACA INICIALIZO MI TDA READER
    }


    file_reader_iterate(&file_reader);

    file_reader_uninit(&file_reader); //ACA CIERRO MI TDA READER

	return 0;
}
