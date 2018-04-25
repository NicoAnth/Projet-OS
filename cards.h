#ifndef H_CARDS
#define H_CARDS

// creer un nouveau pointeur pour une pile de cartes
card_t* createCard();

// ajouter une carte à une liste de cartes. Si vide, creer un nouveau pointeur
card_t* addCard(card_t* c, int value);

// recuperer la valeur d'une carte
// A = 11 ou 1
// 1 à 9 = valeur
// J,V,D,R = 10
int getCardValue(int cardValue, int points);

// recuperer la valeur d'une suite de cartes (parcours liste)
int getHandValue(card_t* hand);

#endif
