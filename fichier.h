#include "type.h"

#ifndef H_FICHIER
#define H_FICHIER

FICHIER SE_ouverture(const char * chemin, int acces);
int SE_fermeture(FICHIER f);
int SE_suppression (const char * chemin);
TABLE initTable(FICHIER f);
void lireFichierEntree(FICHIER f, char* s[], int imax);
//

#endif
