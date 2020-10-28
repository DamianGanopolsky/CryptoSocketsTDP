#ifndef COMMON_RC4_ENCRYPTION_H_
#define COMMON_RC4_ENCRYPTION_H_

//El struct va a contener el estado del cifrador rc4
//a medida que se vaya llamando para encriptar los distintos
//bloques este ira cambiando
typedef struct {
	int i;
	int j;
	unsigned char S[256];
} rc4_t;


//Inicializa el vector de caracteres de estado S e
//inicializa los valores de los atributos del TDA.
void inicializar_rc4(char *key,unsigned int key_length,\
		rc4_t* self);


//Cifra el buffer enviado como argumento, y genera un
//buffer_procesado con el buffer anterior codificado
//Tiene en cuenta el estado en el que se encuentra debido a que se
//le envian los parametros S,i y j que pudieron haber sido modificados
//en alguna iteracion
void rc4_cifrar(unsigned char* buffer,unsigned char*\
		buffer_procesado,rc4_t* self,int tamanio);

//Descifra el buffer_procesado enviado como argumento y genera
//un buffer_normalizado que sera el buffer desencriptado
//Tiene en cuenta el estado en el que se encuentra debido a que se
//le envian los parametros S,i y j que pudieron haber sido modificados
//en alguna iteracion
void rc4_descifrar(unsigned char* buffer_procesado,\
		unsigned char* buffer_normalizado,rc4_t* self,int tamanio);

#endif /* COMMON_RC4_ENCRYPTION_H_ */
