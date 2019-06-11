CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g 
LDLIBS=-lm -lcurses
OUTPUT=game
all: game 

game: main.o k.o hof.o ui.o
	$(CC) $(CFLAGS) main.o k.o hof.o ui.o $(LDLIBS) -o $(OUTPUT)	
main.o: main.c
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) main.c $(LDLIBS) -o main.o -c 
k.o: k.c
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) k.c $(LDLIBS) -o k.o -c 
hof.o: hof.c 
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) hof.c $(LDLIBS) -o hof.o -c 
ui.o: ui.c
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) ui.c $(LDLIBS) -o ui.o -c 
	
clean:
	rm game main.o k.o hof.o ui.o 