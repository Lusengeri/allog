test: allog.o list.o test.c
	gcc -o test allog.o list.o test.c 

allog.o: allog.c
	gcc -c allog.c

list.o: list.c
	gcc -c list.c

all: test allog.o list.o
