#include "type.h"
#include "cards.h"
#include <stdio.h>
#include <stdlib.h>

// afficher une main
void afficheHand(card_t* c){
	if(c == NULL) return;
	
	printCard(c->value);
	printf(" ");
	
	if(c->next == NULL){
		return;
	}
	
	afficheHand(c->next);
}

// afficher l'état du jeu
void afficheJeu(JOUEUR j[], BANQUE b, int nJoueurs, int nMains){
	int i;
	for(i=0; i<nJoueurs; i++){
		printf("Joueur[%d] : %d jetons; typeMise : %s; valStop : %d; objectif : %d \n", i, j[i].nJetons, j[i].typeMise, j[i].valStop, j[i].objectif);
		printf("joueur j[%d] : ",i);
		afficheHand(j[i].hand);
		printf("\n");
		
		printf("handvalue = %d \n\n",getHandValue(j[i].hand));
	}
	printf("banque : ");
	afficheHand(b.hand);
	printf("\nhandvalue = %d \n\n",getHandValue(b.hand));
	
	printf("nMains : %d\n\n", nMains);
}
