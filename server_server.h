
#include "common_socket.h"

void descifrar(unsigned char* mensaje,unsigned char* mensaje_desencriptado,\
		const char* metodo,char* clave,void* cifrador,int tamanio);

void recibir_mensajes(socket_t* socket_peer,\
		const char* metodo,const char* clave);

void recibir_mensaje_cesar(socket_t* socket_peer,int clave);

void recibir_mensaje_vigenere(socket_t* socket_peer,char* clave);

void recibir_mensaje_rc4(socket_t* socket_peer,char* clave);



