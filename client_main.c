#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "client_file_reader.h"
#include "common_socket.h"



int main(int argc, char const *argv[]) {

    file_reader_t file_reader;
    socket_t socket;

    socket_init(&socket);

    socket_connect(&socket, argv[1], argv[2]);

    if(argc<6){
    	file_reader_init(&file_reader,NULL);

    }

    else file_reader_init(&file_reader, argv[6]); //ACA INICIALIZO MI TDA READER

    int tamanio_clave= strlen(argv[4])-6;
    char subbuff[tamanio_clave+1];
    memcpy( subbuff, &argv[4][6], tamanio_clave );
    subbuff[tamanio_clave] = '\0';

    if(atoi(subbuff)!=0){
    	int clave_numerica=atoi(subbuff);
    	file_reader_iterate_cesar(&file_reader,clave_numerica,&socket);
    	shutdown(socket.fd,SHUT_RDWR);
    }

    if(strcmp(argv[3],"--method=vigenere")==0){
    	file_reader_iterate_vigenere(&file_reader,subbuff,&socket);
    	shutdown(socket.fd,SHUT_RDWR);
    }

    if(strcmp(argv[3],"--method=rc4")==0){
    	file_reader_iterate_rc4(&file_reader,subbuff,&socket);
    	shutdown(socket.fd,SHUT_RDWR);
    }

    file_reader_uninit(&file_reader); //ACA CIERRO MI TDA READER
    socket_uninit(&socket);
	return 0;
}
