CC=gcc -g
CFLAGS=-Wall -Werror -Wextra

all:
	$(CC) $(CFLAGS) dn.c -o dn
