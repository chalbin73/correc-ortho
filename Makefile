
.PHONY: all

all:
	gcc dictionnaire.c alphabet.c main.c read_with_mmap.c -Wall -Werror -o main
