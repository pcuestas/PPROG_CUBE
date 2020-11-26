EXE=game
OBJ=cube.o solver.o print_c.o interface.o bcd.o terminal_funct.o cube_interface.o menu.o $(EXE).o

TEMPEXE=prueba
LIB2=-lpthread
LIB=-lSDL2main -lSDL2 -lSDL2_image -lglut -lGLU -lGL -lm
OBJTEMPEXE=$(TEMPEXE).o cube.o print_c.o solver.o lib_funct.o lib_struct.o interface.o

MENU=menu_interface
OBJ2=$(MENU).o menu.o interface.o

CFLAGS=-ansi -pedantic -Wall -g
CC=gcc

HEADERS=*.h


all: $(EXE)

prueba: $(TEMPEXE)

menui: $(MENU)

run:
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

print_c.o: print_c.c print_c.h interface.o cube.o
	$(CC) $(CFLAGS) -c $<

solver.o: solver.c solver.h cube.o
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(EXE) $(MENU) $(TEMPEXE) *.gch
cleantrash:
	rm -f *.o *.gch
