.Phony : all clean

all: graph

graph: main.c
	gcc -Wall -g main.c algo.c edges.c nodes.c -o $@
clean:
	rm -f *.o graph
