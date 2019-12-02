#makefile

all: 
	make progA
	make progB
	make progC
	make progD

Taches.o: Taches.c Taches.h outil.h
	gcc -Wall -c Taches.c

outil.o: outil.c outil.h
	gcc -Wall -c outil.c

TacheA.o: Taches.h outil.h TacheA.c
	gcc -Wall -c TacheA.c

TacheB.o: Taches.h outil.h TacheB.c
	gcc -Wall -c TacheB.c

TacheC.o: Taches.h outil.h TacheC.c
	gcc -Wall -c TacheC.c

TacheD.o: Taches.h outil.h TacheD.c
	gcc -Wall -c TacheD.c

progA: Taches.o outil.o TacheA.o
	gcc -o progA TacheA.o Taches.o outil.o

progB: Taches.o outil.o TacheB.o
	gcc -o progB TacheB.o Taches.o outil.o

progC: Taches.o outil.o TacheC.o
	gcc -o progC TacheC.o Taches.o outil.o

progD: Taches.o outil.o TacheD.o
	gcc -o progD TacheD.o Taches.o outil.o

clean:
	rm *.o