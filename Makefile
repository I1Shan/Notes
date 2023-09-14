CC=gcc -g
CFLAGS=-Wall -Werror -Wextra

all:
	$(CC) $(CFLAGS) dbNotes.c -o dbNotes
