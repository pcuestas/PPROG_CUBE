CFLAGS=-ansi -pedantic -Wall -g
CC=gcc
HEADERS=*.h

EXE=game
OBJ=cube.o solver.o print_c.o interface.o bcd.o terminal_funct.o cube_interface.o menu.o lib_funct.o lib_struct.o SDL_interface.o $(EXE).o


LIB_SDL=-lSDL2main -lSDL2 -lSDL2_ttf -lGLU -lGL 
LIB2=-lpthread $(LIB_SDL)


#TEST=tests
#OBJTEST=cube.o solver.o print_c.o interface.o bcd.o terminal_funct.o cube_interface.o menu.o $(TEST).o
#TEMPEXE=prueba
#OBJTEMPEXE=$(TEMPEXE).o cube.o print_c.o solver.o lib_funct.o lib_struct.o interface.o


all: $(EXE)

#prueba: $(TEMPEXE)

run:
	./$(EXE)


$(EXE): $(OBJ) $(HEADERS)
	@echo $@ :
	$(CC) $(OBJ) $(LIB2) -o  $@


%.o: %.c $(HEADERS)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(EXE) $(TEST) $(TEMPEXE) *.gch

cleantrash:
	rm -f *.o *.gch

#$(TEST): $(OBJTEST) $(HEADERS)
#	$(CC) $(OBJTEXT) $(LIB2) -o  $@

#$(MENU): $(OBJ2) $(HEADERS)
#	$(CC) $(OBJ2) -o $@

#$(TEMPEXE): $(OBJTEMPEXE) $(HEADERS)
#	$(CC) $(OBJTEMPEXE) $(LIB) $(LIB2) -o $@

#lib_struct.o: lib_struct.c lib_funct.h
#	$(CC) $(CFLAGS) -c $<
#
#print_c.o: print_c.c print_c.h interface.h cube.h
#	$(CC) $(CFLAGS) -c $<
#
#solver.o: solver.c solver.h cube.h
#	$(CC) $(CFLAGS) -c $<


