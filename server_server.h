
#include "common_socket.h"

void descifrar(unsigned char* mensaje,unsigned char* mensaje_desencriptado,const char* metodo,char* clave,void* cifrador,int tamanio);

void recibir_mensajes(socket_t* socket_peer,const char* metodo,const char* clave);

