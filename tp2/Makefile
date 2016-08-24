CC = gcc
CFLAGS = -c -Wall
EXEC = tp2
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: projeto

projeto: $(OBJ)
	@$(CC) $^ -o $(EXEC)

main.o: main.c fila.h filtro.h
	@$(CC) $(CFLAGS) main.c

fila.o: fila.c
	@$(CC) $(CFLAGS) fila.c

filtro.o: filtro.c
	@$(CC) $(CFLAGS) filtro.c

.PHONY: clean

clean:
	@rm -rf $(OBJ) $(EXEC)

run:
	./$(EXEC);
