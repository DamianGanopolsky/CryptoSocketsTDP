#include <stdio.h>


typedef struct{
    FILE* fp;
} file_reader_t;



int file_reader_init(file_reader_t* self, const char* file_name);           


int file_reader_uninit(file_reader_t* self);

int file_reader_iterate(file_reader_t* self); 
