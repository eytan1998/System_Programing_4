CC = gcc
AR = ar
CFLAGS = -Wall -g

OBJECT_MAIN = main.o
OBJECTS_LIB = algo.o edges.o nodes.o

.Phony : all clean

all: graph

graph: libmy_mat.a $(OBJECT_MAIN)
	${CC} ${CFLAG} -L. $(OBJECT_MAIN) -lmy_mat -o $@

libmy_mat.a : $(OBJECTS_LIB)
	$(AR) $(FLAGS) -rcs libmy_mat.a $(OBJECTS_LIB)

$(OBJECT_MAIN): main.c algo.h edges.h nodes.h graph.h
	${CC} ${CFLAG} -c main.c

algo.o: algo.h graph.h
	${CC} ${CFLAG} -c algo.c

edges.o: edges.h graph.h
	${CC} ${CFLAG} -c edges.c

nodes.o: nodes.h graph.h
	${CC} ${CFLAG} -c nodes.c

clean:
	rm -f *.o *.a graph

