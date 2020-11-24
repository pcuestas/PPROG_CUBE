
all: cube_interface menu_interface clean

CFLAGS=-ansi -pedantic -Wall -g

menu_interface: interface.o menu_interface.o menu.o
	gcc menu_interface.o interface.o menu.o -o menu_interface

cube_interface: cube_interface.o cube.o interface.o print_c.o solver.o bcd.o
	gcc cube_interface.o cube.o interface.o print_c.o solver.o bcd.o -lpthread -o cube_interface

cube_interface.o: cube_interface.c
	gcc $(CFLAGS) -c cube_interface.c

cube.o: cube.c cube.h 
	gcc $(CFLAGS) -c cube.c

interface.o: interface.c interface.h 
	gcc $(CFLAGS) -c interface.c 

print_c.o: print_c.c print_c.h interface.h 
	gcc $(CFLAGS) -c print_c.c

solver.o: solver.c solver.h
	gcc $(CFLAGS) -c solver.c

bcd.o: bcd.h bcd.c interface.h
	gcc $(CFLAGS) -c bcd.c

menu.o: menu.h menu.c
	gcc $(CFLAGS) -c menu.c

menu_interface.o: menu_interface.c menu.h
	gcc $(CFLAGS) -c menu_interface.c

clean:
	rm -f *.o 