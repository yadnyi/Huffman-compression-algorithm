all: project
project: array.o list.o mapping.o trylzw.o
	cc trylzw.o lzw.o -o project
array.o: array.c
	cc -c array.c
list.o: list.h list.c
	cc -c list.c
mapping.o: mapping.c
	cc -c mapping.c
trylzw.o: try.c trylzw.c
	cc -c trylzw.c
clean:
		rm *.o
