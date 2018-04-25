#ifndef H_JOUEURS
#define H_JOUEURS

JOUEUR initUnJoueur(FICHIER f);
int mise(JOUEUR j);
int pioche(card_t* hand, int valStop);
void* actionJoueur(void* arg);

#endif
