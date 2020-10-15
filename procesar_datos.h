#include <stdio.h>
#include <string.h>
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#include "common_operaciones_buffer.h"
#include "common_socket.h"

typedef struct{
    FILE* fp;
} archivo_t;



int abrir_archivo(archivo_t* self, const char* file_name);           

int longitud_archivo(archivo_t* self);

int cerrar_archivo(archivo_t* self);

int file_reader_iterate(archivo_t* self,const char* metodo,void* clave);

int enviar_datos_rc4(archivo_t* self,char* clave,socket_t* socket);

int enviar_datos_vigenere(archivo_t* self,char* clave,socket_t* socket);

int enviar_datos_cesar(archivo_t* self,int clave,socket_t* socket);


