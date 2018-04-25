#include "deck.h"
#include "pthread.h"

#ifndef H_TYPE
#define H_TYPE

#define IMAX_TABLE 3
#define IMAX_JOUEUR 4
#define VAL_STOP_BANQUE 17
#define PERTE 0
#define EGALITE 1
#define GAIN 2
#define BLACKJACK 3

// type fichier
typedef struct {
	int descripteur;
	char * chemin;
	int acces;
} FICHIER;

// type table
typedef struct{
	int nJoueurs;
	int nDecks;
	int nMainsMax;
} TABLE;

// type joueur
typedef struct{
	// fichier
	char* typeMise;
	int valStop;
	int objectif;
	int nJetons;
	
	// jeu
	int gain;
	int misePrecedente;
	card_t* hand;
} JOUEUR;

// type banque
typedef struct{
	int valStop;
	card_t* hand;
} BANQUE;

// informations nécessaires aux threads
typedef struct{
	JOUEUR j;
	deck_t* d;
	int nJoueurs;
	pthread_cond_t condition;
	pthread_mutex_t mutex;
} arg_t;

#endif
