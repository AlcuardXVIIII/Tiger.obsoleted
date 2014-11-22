a.out: main.o 01-01.o util.o slp.o
	cc -g main.o 01-01.o util.o slp.o

main.o: main.c 01-01.h util.h
	cc -g -c main.c

01-01.o: 01-01.c 01-01.h util.h
	cc -g -c 01-01.c

util.o: util.c util.h
	cc -g -c util.c
slp.o: slp.c slp.h
	cc -g -c slp.c
clean:
	rm -f a.out util.o prog1.o 01-01.o main.o slp.o
