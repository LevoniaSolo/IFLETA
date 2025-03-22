CC=clang
FLAGS=-Wno-error=incompatible-function-pointer-types -Wno-incompatible-function-pointer-types -Wno-visibility -Wno-incompatible-pointer-types -g -O0

program.out: main.o vector.o complex.o fractions.o
	$(CC) main.o vector.o complex.o fractions.o -o program.out

main.o: main.c
	$(CC) -c main.c $(FLAGS) -o main.o

vector.o: vector.c
	$(CC) -c vector.c $(FLAGS) -o vector.o

complex.o: complex.c
	$(CC) -c complex.c $(FLAGS) -o complex.o

fractions.o: fractions.c
	$(CC) -c fractions.c $(FLAGS) -o fractions.o


.PHONY: clean

clean:
	rm -f *.o

fullclean: clean
	rm -f *.out