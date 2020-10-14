
#include "server_server.h"
#include "common_cesar_encryption.h"


void recibir_mensajes(socket_t* socket_peer,const char* metodo,const char* clave){

    int tamanio_clave= strlen(clave)-6;
    char subbuff[tamanio_clave+1];
    memcpy( subbuff, &clave[6], tamanio_clave );
    subbuff[tamanio_clave] = '\0';


	unsigned char client_message[64];
	ssize_t recibidos=0;

	recibidos=socket_receive(socket_peer,client_message, sizeof(client_message));

	unsigned char message_final[recibidos+1];
	memset(message_final,0,sizeof(message_final));
	memcpy(message_final,client_message,recibidos);

	printf("The client sent the data: %s \n",message_final);

    if(atoi(subbuff)!=0){
    	int clave_numerica=atoi(subbuff);
    	unsigned char buffer_normalizado[sizeof(message_final)];
    	memset(buffer_normalizado,0,sizeof(buffer_normalizado));

    	descifrado_cesar(message_final,buffer_normalizado,clave_numerica,sizeof(message_final));

    	buffer_normalizado[recibidos]=0;
    	printf("El mensaje es %s \n",buffer_normalizado);
    }
}
