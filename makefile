all: program_glowny P1 P2 P3

program_glowny: program_glowny.c sem.o
	gcc -o program_glowny program_glowny.c

P1: P1.c sem.o
	gcc -o P1 P1.c

P2: P2.c sem.o
	gcc -o P2 P2.c

P3: P3.c sem.o
	gcc -o P3 P3.c

sem.o: sem.c
	gcc -c sem.c

clean:
	rm -rf *~
