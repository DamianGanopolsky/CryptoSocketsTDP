#include "common_socket.h"
#include "stdio.h"

//El cliente va a tener un tipo archivo_t el cual va a contener
//un file pointer para manejar el archivo
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
