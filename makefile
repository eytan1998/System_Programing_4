.Phony : all clean

all: main

main: main.c
	gcc -Wall -g main.c algo.c edges.c nodes.c -o $@
clean:
	rm *.o main