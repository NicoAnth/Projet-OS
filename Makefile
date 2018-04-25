#Edition de liens
all:
	gcc  fichier.o joueurs.o deck.o banque.o cards.o affichage.o LV21.o -o lv21 -pthread
test: all
	./lv21 table.txt

#Compilation
LV21.o: LV21.c fichier.h type.h deck.h banque.h cards.h affichage.h
	gcc -c -g -Wall LV21.c -pthread

fichier.o: fichier.c
	gcc -c -g -Wall fichier.c

joueurs.o: joueurs.c
	gcc -c -g -Wall joueurs.c -pthread

deck.o: deck.c
	gcc -c -g -Wall deck.c

banque.o: banque.c
	gcc -c -g -Wall banque.c

cards.o: cards.c
	gcc -c -g -Wall cards.c

affichage.o: affichage.c
	gcc -c -g -Wall affichage.c
clean :
	 rm -rf *.o
mrproper : clean
	rm -rf lv21

