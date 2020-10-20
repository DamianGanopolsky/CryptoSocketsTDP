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

int cerrar_archivo(archivo_t* self);

void enviar_datos(const char* argumento,char* clave, archivo_t* archivo,socket_t* socket);
