#include "deck.h"
#include "type.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// ouverture
FICHIER SE_ouverture(const char * chemin, int acces){
	FICHIER f;
	f.descripteur = open(chemin,acces,0666);
	f.chemin = strdup(chemin);
	f.acces = acces;
	
	return f;
}

// fermeture
int SE_fermeture(FICHIER f){
	return close(f.descripteur);
}

// suppression
int SE_suppression (const char * chemin){
	return remove(chemin);
}

// lecture caractere dans fichier
int SE_lectureCaractere (FICHIER f, char * caractere){
	if(f.acces & (O_RDONLY | O_RDWR))
		return read(f.descripteur, caractere, sizeof(char));
	else printf("erreur permissions lecture\n");
	
	return -1;
}

// ecriture chaine dans fichier
int SE_ecritureChaine (FICHIER f, const char * chaine, int taille){
	if(f.acces & (O_RDONLY | O_RDWR))
		return write(f.descripteur, chaine, taille);
	else 
		printf("erreur permissions ecriture\n");
		
	return -1;
}

// initialisation du fichier d'entrée LV21
FICHIER initFichierEntree(const char* chemin){
	FICHIER f = SE_ouverture(chemin, O_RDWR | O_CREAT); // ouverture fichier
	char* s = "#nbJoueurs; nbDecks; nbMains\n";
	
	// LIGNE 1 : description table
	s = "#nbJoueurs; nbDecks; nbMains\n";
	SE_ecritureChaine(f,s,strlen(s));
		
	// LIGNE 2 : valeurs table
	s = "3; 4; 20\n";
	SE_ecritureChaine(f,s,strlen(s));
		
	// LIGNE 3 : description joueurs
	s = "#nbJetons; typeMise; valStop; objJetons\n";
	SE_ecritureChaine(f,s,strlen(s));
		
	// LIGNE 4 : valeurs joueur 1
	s = "400; 50; 16; 1000\n";
	SE_ecritureChaine(f,s,strlen(s));
	
	// LIGNE 5 : valeurs joueur 2
	s = "750; 10+; 18; 3000\n";
	SE_ecritureChaine(f,s,strlen(s));
		
	// LIGNE 6 : valeurs joueur 3
	s = "1500; 200-; 17; 3000\n";
	SE_ecritureChaine(f,s,strlen(s));
		
	SE_fermeture(f); // fermeture fichier
	return f;
}

// lecture du fichier d'entrée
/* boucle lecture
	 * On initialise l'incrémenteur i à 0
	 * Tant que i est inférieur à 3, on lit un caractere dans le fichier
	 * Si le caractère lu est un #commentaire, on passe à la ligne suivante grâce à une boucle qui lit caractère par caractère jusqu'à un saut de ligne
	 * Sinon, tant que l'on ne trouve pas de ; \n ou d'espace, on concatène le caractère lu dans la chaine s[i]
	 * A la fin du else, on vérifie que le caractère lu n'est pas un espace (les autres caractères sont déjà traités)
	 * Si ce n'est pas un espace, on incrémente i et on va donc stocker des caractères dans la chaine suivante s[i] 
 */
void lireFichierEntree(FICHIER f, char* s[], int imax){
	int i;
	char c = 0;
	char* tmp;
	
	// allocation mémoire
	tmp = malloc(sizeof(int));
	
	// boucle lecture fichier
	i = 0;
	while(i<imax){
		SE_lectureCaractere(f,&c);
		//~ printf("carac lu : %c\n",c);
		//~ if(imax == 4) printf("%d\n",i);
		if(c == '#'){
			while(c != '\n'){
				SE_lectureCaractere(f,&c);
				//~ printf("carac lu : %c\n",c);
			}
		}
		else{
			while(c != '\n' && c != ';' && c!=' '){
				sprintf(tmp,"%c",c);
				strcat(s[i],tmp);
				SE_lectureCaractere(f,&c);
				//~ printf("carac lu : %c\n",c);

			}
			if(c != ' ') i++;
		}
	}
}

// Initialisation des paramètres de la partie
TABLE initTable(FICHIER f){
	TABLE t;
	char* s[IMAX_TABLE];
	int i;
	
	for(i=0; i<IMAX_TABLE; i++){
		s[i] = malloc(sizeof(int));
	}
	
	lireFichierEntree(f,s,IMAX_TABLE);
	for(i=0; i<IMAX_TABLE; i++) printf("t = %s\n",s[i]);
	t.nJoueurs = atoi(s[0]);
	t.nDecks = atoi(s[1]);
	t.nMainsMax = atoi(s[2]);
	
	return t;
}

// suppression fichier (à écrire)
void supprimerFichier(FICHIER f){
	
}
