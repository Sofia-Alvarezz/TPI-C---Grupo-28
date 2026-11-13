CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
OBJ = main.o simulador.o validaciones.o
TARGET = artemis

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

main.o: main.c simulador.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

simulador.o: simulador.c simulador.h validaciones.h
	$(CC) $(CFLAGS) -c simulador.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET).exe