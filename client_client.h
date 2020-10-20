#include <stdio.h>
#include <string.h>
#include "common_cesar_encryption.h"
#include "common_vigenere_encryption.h"
#include "common_rc4_encryption.h"
#include "common_util.h"
#include "common_socket.h"

typedef struct{
    FILE* fp;
} archivo_t;


int abrir_y_validar_archivo(int argc,char const *argv[],\
		archivo_t* archivo,socket_t* socket);

int cerrar_archivo(archivo_t* archivo);

void enviar_datos(const char* argumento,char* clave, archivo_t* archivo,socket_t* socket);
