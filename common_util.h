#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_
#include <stdio.h>
#include <string.h>

//Recibe el argumento correspondiente a la clave que
//le llega al main y devuelve la clave sin el --key
int slice(const char* argumento,char* clave);

#endif /* COMMON_UTIL_H_ */
