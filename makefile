CC=gcc
CFLAGS=-c -Wall

all : bin/Laby2.0.exe bin/Laby1.0.exe

bin/Laby2.0.exe: obj/fonction_grille.o obj/fonction_jeu.o obj/jeu.o obj/main.o
	$(CC) -L.\lib\SDL-1.2.15\lib -o Laby2.0.exe obj\fonction_grille.o obj\fonction_jeu.o obj\jeu.o obj\main.o  -s  -lmingw32 -lSDLmain -lSDL.dll -luser32 -lgdi32 -lwinmm -ldxguid .\lib\SDL_image.lib .\lib\SDL_ttf.lib -mwindows
	mv Laby2.0.exe bin/
	
bin/Laby1.0.exe : obj\1.0\main.o obj\1.0\jeu.o
	$(CC) -o Laby1.0.exe obj\1.0\jeu.o obj\1.0\main.o lib\pdcurses.lib 
	mv Laby1.0.exe bin/

obj/fonction_grille.o : src\fonction_grille.c include\fonction_grille.h
	$(CC) $(CFLAGS) src\fonction_grille.c include\fonction_grille.h -O2 -lSDL_image -std=c99 -I.\lib\SDL-1.2.15\include
	mv fonction_grille.o obj/

obj/fonction_jeu.o : src\fonction_jeu.c include\fonction_jeu.h
	$(CC) $(CFLAGS) src\fonction_jeu.c include\fonction_jeu.h -O2 -lSDL_image -std=c99 -I.\lib\SDL-1.2.15\include
	mv fonction_jeu.o obj/

obj/jeu.o : src\jeu.c include\jeu.h
	$(CC) $(CFLAGS) src\jeu.c include\jeu.h -O2 -lSDL_image -std=c99 -I.\lib\SDL-1.2.15\include
	mv jeu.o obj/

obj/main.o : src\main.c include\fonction_grille.h include\fonction_jeu.h include\jeu.h
	$(CC) $(CFLAGS) src\main.c include\fonction_grille.h include\fonction_jeu.h include\jeu.h -O2 -lSDL_image -std=c99 -I.\lib\SDL-1.2.15\include
	mv main.o obj/
	
obj\1.0\main.o : src\1.0\main.c include\1.0\curses.h include\1.0\jeu.h
	$(CC) $(CFLAGS) src\1.0\main.c include\1.0\curses.h include\1.0\jeu.h -std=c99
	mkdir obj/1.0
	mv main.o obj/1.0/
	
obj\1.0\jeu.o : src\1.0\jeu.c include\1.0\jeu.h include\1.0\curses.h 
	$(CC) $(CFLAGS) src\1.0\jeu.c include\1.0\jeu.h include\1.0\curses.h -std=c99 
	mv jeu.o obj/1.0/
	
archive :
	tar -czvf archivejeu_ibis.tar.gz ./
	
clean : 
	rm -rf obj\* bin\Laby1.0.exe bin\Laby2.0.exe
	mkdir obj
	 

