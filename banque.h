#ifndef H_BANQUE
#define H_BANQUE

// initialiser la banque, valStop = 17, hand = NULL
BANQUE initBanque();

// distribuer une carte
card_t* distribuer(deck_t* d, card_t* hand);

// distribuer deux cartes aux joueurs et à la banque (début de manche)
void distribuerAll(deck_t* d, BANQUE *b, JOUEUR j[], int nJoueurs);

// conditions fin de manche, mise à jour des informations joueurs + défausse de toutes les cartes
void finManche(deck_t* d, BANQUE* b, JOUEUR j[], int nJoueurs);

#endif
