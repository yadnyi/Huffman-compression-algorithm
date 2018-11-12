all: project
project: main.o huffqueue.o
	cc main.o huffqueue.o -o project
main.o: huffqueue.h main.c
	cc -c main.c
huffqueue.o: huffqueue.c huffqueue.h
	cc -c huffqueue.c
clean:
	rm *.o
