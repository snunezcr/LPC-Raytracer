PREFIX=lpc-raytracer
CC=g++
CFLAGS=-I./include

MAIN=main.cpp

OBJS=base-rt/String.o base-rt/Punto.o base-rt/Vector.o base-rt/Color.o base-rt/Escena.o base-rt/Configuracion.o base-rt/Raytracer.o

all: objects
	$(CC) $(CFLAGS) -o $(PREFIX) $(MAIN) $(OBJS)
	
objects:
	make -C base-rt base

clean:
	make -C base-rt clean
	rm -f $(PREFIX)
