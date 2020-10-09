
run: all
	./ejecutable < texto

all: common_main.c common_file_reader.c common_cesar_encryption.c
	gcc -std=c99 -g common_main.c common_file_reader.c common_cesar_encryption.c -o ejecutable
