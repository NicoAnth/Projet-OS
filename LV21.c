#include "deck.h"
#include "fichier.h"
#include "affichage.h"
#include "type.h"
#include "joueurs.h"
#include "banque.h"
#include "cards.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

// initialiser tableau joueurs
void initLesJoueurs(FICHIER f, JOUEUR j[], int nJoueurs){
	int i;

	for(i=0; i<nJoueurs; i++){
		j[i] = initUnJoueur(f);
	}
}

int finJeu(JOUEUR j[], int nJoueurs, int nMains, int nMainsMax){
	int i;
	int banqueRoute = 0;
	int objectif = 0;
	
	// mains max
	if(nMains == nMainsMax){
		printf("\nNombre de mains maximal atteint \n");
		return 1;
	}
	
	// banque route ou objectif atteint
	for(i=0; i<nJoueurs; i++){
		if(j[i].nJetons <=0) banqueRoute++;
		if(j[i].nJetons >= j[i].objectif) objectif++;
	}
	if(banqueRoute == nJoueurs){
		printf("\nTous les joueurs ont perdus. GAME OVER. atteint \n");
		return 1;
	}
	if(objectif == nJoueurs){
		printf("\nTous les joueurs ont atteint leurs objectifs. \n");
		return 1;
	}
	
	return 0;
}

int main(int argc, char* argv[]){
	// argument
	if(argc != 2){
		 printf("erreur commande. Format attendu : ./executable fichier\n");
		 return 0;
	}
	// ouverture fichier
	FICHIER f = SE_ouverture(argv[1],O_RDWR);
	
	// variables
	TABLE t = initTable(f);
	JOUEUR *j = malloc(t.nJoueurs*sizeof(JOUEUR));
	BANQUE b = initBanque();
	deck_t* d;
	int i;
	int nMains = 0;
	arg_t *arg = NULL;
	pthread_t* joueurth;
	
	//allocation mémoire pour les threads
	joueurth = calloc(t.nJoueurs,sizeof(pthread_t));
	
	// gestion decks
	initDeckLib();
	d = initDeck(P52,t.nDecks);
	shuffleDeck(d);

	// initialisation des joueurs
	initLesJoueurs(f,j,t.nJoueurs);
	
	//créations des threads
	for (i=0; i<t.nJoueurs; i++)
		{ 	
			// configuration de la variable arg
			arg->j = j[i];
			arg->d = d;
			arg->nJoueurs = t.nJoueurs;
			pthread_create(&joueurth[i],NULL,actionJoueur,arg);
		}
		
	// tours jusqu'à la fin du jeu
	while((finJeu(j,t.nJoueurs,nMains,t.nMainsMax))==0)
	{	
		nMains++;	
		distribuerAll(d,&b,j,t.nJoueurs);
		
		while(pioche(b.hand,VAL_STOP_BANQUE)){
			b.hand = distribuer(d,b.hand);
		}
		
		afficheJeu(j,b,t.nJoueurs,nMains);
		finManche(d,&b,j,t.nJoueurs);	
	}
	
	removeDeck(d);
	SE_fermeture(f);
	return 0;
}
