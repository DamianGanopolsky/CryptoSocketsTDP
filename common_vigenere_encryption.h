#ifndef COMMON_VIGENERE_ENCRYPTION_H_
#define COMMON_VIGENERE_ENCRYPTION_H_

//El struct va a contener el estado del TDA vigenere, la
//posicion del cifrado se ira actualizando ya que esta va a ir
//cambiando a medida que se lean los chunks. Y la longitud de la clave
// se necesita para saber con que posicion mapear cuando se encripta
typedef struct {
	int posicion_cifrado;
	int longitud_clave;
} vigenere_t;

//Inicializa el TDA vigenere, estableciendo su estado inicial
void inicializar_vigenere(vigenere_t* self,int longitud_clave);

//Cifra la cadena enviada como argumento, y genera una
//cadena_procesada con la cadena anterior codificada
void cifrado_vigenere(unsigned char* cadena,unsigned char* cadena_procesada\
		,char* clave,vigenere_t* self,int tamanio);

//Descifra la cadena_procesada enviada como argumento y
//genera la cadena original cuyo nombre es 'cadena_normalizada'
void descifrado_vigenere(unsigned char* cadena_procesada,unsigned char*\
		cadena_normalizada,char* clave,vigenere_t* self,int tamanio_buffer);

#endif /* COMMON_VIGENERE_ENCRYPTION_H_ */
