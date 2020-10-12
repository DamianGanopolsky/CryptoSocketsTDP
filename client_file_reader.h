#include <stdio.h>
#include <string.h>

typedef struct{
    FILE* fp;
} file_reader_t;



int file_reader_init(file_reader_t* self, const char* file_name);           

int file_reader_length(file_reader_t* self);

int file_reader_uninit(file_reader_t* self);

int file_reader_iterate(file_reader_t* self,const char* metodo,void* clave);

int file_reader_iterate_rc4(file_reader_t* self,char* clave);

int file_reader_iterate_vigenere(file_reader_t* self,char* clave);

int file_reader_iterate_cesar(file_reader_t* self,int clave);


