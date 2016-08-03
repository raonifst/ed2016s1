CC = gcc
CFLAGS = -c -Wall
EXEC = 1
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: projeto

projeto: $(OBJ)
	@$(CC) $^ -o $(EXEC)

main.o: main.c lista.h indice.h
	@$(CC) $(CFLAGS) main.c

lista.o: lista.c
	@$(CC) $(CFLAGS) lista.c

indice.o: indice.c
	@$(CC) $(CFLAGS) indice.c

.PHONY: clean

clean:
	@rm -rf $(OBJ) $(EXEC)

run:
	-./$(EXEC)

 
