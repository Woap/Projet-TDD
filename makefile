main : jeu.o main.o
	gcc -o main main.o jeu.o -lncurses

jeu.o : jeu.c jeu.h
	gcc -c jeu.c

main.o : main.c
	gcc -c main.c


