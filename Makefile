allog.o: allog.c
	gcc -c allog.c

test: allog.o test.c
	gcc -o test allog.o test.c 

all: test allog.o
