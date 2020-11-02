* client_client.c: marcar como `static` a las funciones "privadas". 
    Funciones enviar: no es necesario saber la longitud del archivo: realizar un fread de 64 bytes, tomar la cantidad de bytes leidos y codificar esa cantidad de bytes. Es más, cuando la cantidad sea < 64 es porque se terminó el archivo. Tampoco es necesario usar un buffer dinámico, en uno estático de 64 bytes instanciado en el stack de la función enviar_datos ya debería servir para leer y procesar.
    Hay mucha repetición de código en los distintos enviar_datos_<encriptado>, modularizar utilizar punteros a funciones para evitar repetición de código
* client_main.c: crear un TDA "client" que le de cohesión a los que están instanciados en el main.
* common<_metodo_>encription.c: evitar código repetido
* common_socket.h: mover `#define _POSIX_C_SOURCE 200112L` a la unidad de compilación
* common_util: tanto slice como limpiar buffers no son necesaria. slice no lo es porque se puede utilizar el contenido de argv (sumándole un offset si es necesario), y limpiar buffers tampoco es necesario
* General: Documentar TDAs, tanto structs como funciones asociadas. Eliminar includes innecesarios (como unistd en client_client.c, o stdio.h en lugares donde no se usa). Usar defines para constantes hardcodeadas, con nombres significativos. Tratar de mover la mayor cantidad de includes a las unidades de compilación, no en los .h, ya que sino se propagan. Marcar funciones "privadas" como static.
