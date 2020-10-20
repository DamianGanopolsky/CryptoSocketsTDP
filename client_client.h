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

//Inicializa el valor de fp, apuntando a stdin o al archivo
//dependiendo del caso. Realiza todas las validaciones necesarias
//y libera recursos en caso de error
int abrir_y_validar_archivo(int argc,char const *argv[],\
		archivo_t* archivo,socket_t* socket);

//Cierra el archivo en el caso que fp apunte a un archivo
int cerrar_archivo(archivo_t* archivo);

//Envia todos los datos contenidos en el archivo al servidor
void enviar_datos(const char* metodo,char* clave,\
		archivo_t* archivo,socket_t* socket);
