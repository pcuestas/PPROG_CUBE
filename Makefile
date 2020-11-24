EXE=cube_interface
OBJ=cube.o solver.o print_c.o interface.o bcd.o $(EXE).o

TEMPEXE=prueba
LIB2=-lpthread
LIB=-lSDL2main -lSDL2 -lSDL2_image -lglut -lGLU -lGL -lm
OBJTEMPEXE=$(TEMPEXE).o cube.o print_c.o solver.o lib_funct.o lib_struct.o

MENU=menu_interface
OBJ2=$(MENU).o menu.o interface.o

CFLAGS=-ansi -pedantic -Wall -g
CC=gcc

HEADERS=cube.h solver.h print_c.h types.h menu.h interface.h bcd.h


all: $(EXE)

prueba: $(TEMPEXE)

menui: $(MENU)

game: 
	./$(EXE)

gamelib: 
	./$(TEMPEXE)

$(EXE): $(OBJ) $(HEADERS)
	$(CC) $(OBJ) $(LIB2) -o  $@

$(MENU): $(OBJ2) $(HEADERS)
	$(CC) $(OBJ2) -o $@

$(TEMPEXE): $(OBJTEMPEXE) $(HEADERS)
	$(CC) $(OBJTEMPEXE) $(LIB) -o $@

main: main.o cube.o print_c.o
	$(CC) main.o cube.o print_c.o -o main

lib_struct.o: lib_struct.c lib_funct.h
	$(CC) $(CFLAGS) -c $<

print_c.o: print_c.c print_c.h interface.h 
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(EXE) $(MENU) $(TEMPEXE) *.gch
cleantrash:
	rm -f *.o *.gch
