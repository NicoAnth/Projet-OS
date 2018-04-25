#include "deck.h"
#include "type.h"
#include "fichier.h"
#include "banque.h"
#include "cards.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
//~ // finirThread
//~ int finirThread(int jetonsRestants, int nMains, int nMainsMax){
	//~ if(!jetonsRestants || nMains > nMainsMax) return 1;
	//~ return 0;
//~ }

// Miser
int mise(JOUEUR j){
	int res = 0;
	
	if(j.nJetons == 0) return 0;
	
	// evaluation type mise : 50, 10+ ou 200-
	// si gain mise de base
	if(!strcmp(j.typeMise,"50")) {
		res = 50;
	} else if(!strcmp(j.typeMise,"10+")){
		if(!j.gain) 
			res = j.misePrecedente*2;
		else 
			res = 10;
	} else{
		if(!j.gain) 
			res = j.misePrecedente/2;
		else 
			res = 200;
	}
	
	// evaluation du nombre de jetons restants
	if(j.nJetons >= res){
		return res;
	} else{
		return j.nJetons;
	}
	
	return 0;
}

// Piocher
int pioche(card_t* hand, int valStop){
	return getHandValue(hand) < valStop;
}

// Action joueur
void* actionJoueur(void *arg){
	int i;
	arg_t *info = arg;
	for(i=0; i<info->nJoueurs; i++)
	{
		if(info->j.nJetons > 0)
		{
			info->j.misePrecedente = mise(info->j);
			info->j.nJetons -= info->j.misePrecedente;
			
			while(pioche(info->j.hand,info->j.valStop))
			{
				info->j.hand = distribuer(info->d,info->j.hand);
			}
		}
	}
	pthread_exit(NULL);
}

// Initialisation d'un joueur
JOUEUR initUnJoueur(FICHIER f){
	JOUEUR j;
	char* s[IMAX_JOUEUR];
	int i;
	
	for(i=0; i<IMAX_JOUEUR; i++){
		s[i] = malloc(sizeof(int));
	}
	
	// fichier
	lireFichierEntree(f,s,IMAX_JOUEUR);
	j.nJetons = atoi(s[0]);
	j.typeMise = s[1];
	j.valStop = atoi(s[2]);
	j.objectif = atoi(s[3]);
	
	// jeu
	j.gain = GAIN;
	j.misePrecedente = 0;
	j.hand = NULL;
	
	return j;
}

