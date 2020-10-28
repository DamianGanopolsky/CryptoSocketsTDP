#ifndef COMMON_CESAR_ENCRYPTION_H_
#define COMMON_CESAR_ENCRYPTION_H_


//Cifra la cadena enviada como argumento, y genera una
//cadena_procesada con la cadena anterior codificada
void cifrado_cesar(unsigned char* cadena,\
		unsigned char* cadena_procesada,int clave_numerica,int tamanio);

//Descifra la cadena_procesada enviada como argumento y
//genera la cadena original cuyo nombre es 'cadena_normalizada'
void descifrado_cesar(unsigned char* cadena_procesada,\
		unsigned char* cadena_normalizada,int clave_numerica,int tamanio);

#endif /* COMMON_CESAR_ENCRYPTION_H_ */
