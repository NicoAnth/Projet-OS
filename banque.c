#include "type.h"
#include "deck.h"
#include "cards.h"
#include "stdio.h"
#include "stdlib.h"

//~ void creerThreads(int nJoueurs, message_t msg[]){
	//~ int i;
	//~ pthread_t thread[nJoueurs];
	
	//~ for(i=0; i<nJoueurs; i++){
		//~ pthread_create(&thread[i], NULL, 
	//~ }
//~ }

//#######################
//### I. DISTRIBUER #####
//#######################

// distribuer une carte
card_t* distribuer(deck_t* d, card_t* hand){
	if(!getDrawPileSize(d)) shuffleDeck(d);
	return addCard(hand,drawCard(d));
}

// distribuer une carte aux joueurs
void distribuerJoueurs(deck_t* d, JOUEUR j[], int nJoueurs){
	int i;
	for(i=0; i<nJoueurs; i++){
		if(j[i].nJetons > 0)
			j[i].hand = distribuer(d,j[i].hand);
	}
}

// distribuer cartes aux joueurs et à la banque 
// condition mutex ?
void distribuerAll(deck_t* d, BANQUE *b, JOUEUR j[], int nJoueurs){
	distribuerJoueurs(d,j,nJoueurs);
	b->hand = distribuer(d,b->hand);
	distribuerJoueurs(d,j,nJoueurs);
	b->hand = distribuer(d,b->hand);
}

//#######################
//### II. DEFAUSSER #####
//#######################

// defausser main
card_t* defausserMain(card_t* hand){
	card_t* tmp;
	
	if(hand == NULL || hand->next == NULL) 
		return NULL;
	else{
		while(hand->next != NULL){
			tmp = hand->next;
			hand->next = tmp->next;
			free(tmp);
		}
		return NULL;
	}
}

// defausser main de tous les joueurs
void defausserJoueurs(JOUEUR j[], int nJoueurs){
	int i;
	for(i=0; i<nJoueurs; i++){
		j[i].hand = defausserMain(j[i].hand);
	}
}

// defausser toutes les mains
void defausseAll(deck_t* d, BANQUE* b, JOUEUR j[], int nJoueurs){
	// defausser banque et joueurs
	b->hand = defausserMain(b->hand);
	defausserJoueurs(j,nJoueurs);
	
	// mettre toutes les cartes dans la défausse
	while(d->handCards->next != NULL) 
		discardCard(d,d->handCards->next->value);
		
	discardCard(d,d->handCards->value);
} 

//#######################
//## III. FIN MANCHE ####
//#######################

// booléen blackjack
int blackjack(card_t* hand){
	int compteur = 1;
	if(hand == NULL || hand->next == NULL) return 0;
	
	while(hand->next != NULL){
		compteur ++;
		hand = hand->next;
	}
	if(compteur > 2) return 0;
	
	return 1;
}

// booléen gain
int battreBanque(card_t* bHand, card_t* pHand){
	int bValue, pValue;
	bValue = getHandValue(bHand);
	pValue = getHandValue(pHand);
	
	// blackjack
	if(pValue == 21){
		if(blackjack(pHand) && !blackjack(bHand)){
			 return BLACKJACK;
		}
		if(blackjack(pHand) && bValue == 21) return GAIN;
	}
	
	// autres
	if(pValue > 21) return PERTE;
	else{
		if(bValue > 21 || pValue > bValue) return GAIN;
		if(pValue == bValue) return EGALITE;
	}
	
	return PERTE;
}

// gainManche : mise à jour du nombre de jetons
void modifierJoueurs(card_t* bHand, JOUEUR j[], int nJoueurs){
	int i;
	
	for(i=0; i<nJoueurs; i++){
		if(j[i].nJetons > 0){		
			j[i].gain = battreBanque(bHand,j[i].hand);
			j[i].nJetons += j[i].gain*j[i].misePrecedente;
			printf("gain j[%d]: %d ; nJetons : %d\n", i, j[i].gain*j[i].misePrecedente, j[i].nJetons);
		}
	}
}

// finManche
void finManche(deck_t* d, BANQUE *b, JOUEUR j[], int nJoueurs){
	modifierJoueurs(b->hand,j,nJoueurs);
	defausseAll(d,b,j,nJoueurs);
}

//#######################
//## IV. INIT BANQUE ####
//#######################

// initialiser la banque
BANQUE initBanque(){
	BANQUE b;
	b.valStop = VAL_STOP_BANQUE;
	b.hand = NULL;
	
	return b;
}
