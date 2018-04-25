#include "deck.h"
#include <stdlib.h>

// creer une carte
card_t* createCard(){
	card_t* c = malloc(sizeof(card_t));
	c->value = 0;
	c->next = NULL;
	
	return c;
}

// ajouter une carte à la main
card_t* addCard(card_t* c, int value){
	if(c == NULL){
		c = createCard();
		c->value = value;
		return c;
	}
	if(c->next == NULL){
		c->next = createCard();
		c->next->value = value;
		return c;
	}
	c->next = addCard(c->next, value);
	return c;
}

// compter les points d'une carte
int getCardValue(int cardValue, int points){	
	if(cardValue%13 == 0){
		if(points + 11 > 21) return 1;
		return 11;
	}
	if(cardValue%13 >= 9)
		return 10;
	
	return (cardValue%13) + 1;
}

// compter les points d'une suite de cartes
int getHandValue(card_t* hand){		
	int points = 0;
	
	if(hand == NULL) return 0;
	if(hand->next == NULL) return getCardValue(hand->value,points);
	while(hand->next != NULL){
		points += getCardValue(hand->value, points);
		hand = hand->next;
	}
	
	return points + getCardValue(hand->value, points);
}
