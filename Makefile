all: client_file_reader.c common_cesar_encryption.c common_vigenere_encryption.c client_main.c common_rc4_encryption.c
	gcc -std=c99 -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline client_main.c client_file_reader.c common_cesar_encryption.c common_vigenere_encryption.c common_rc4_encryption.c  -o ejecutable

run: all
	./ejecutable < texto
