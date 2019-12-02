#ifndef OUTIL_H_
#define OUTIL_H_

typedef struct Liste2Chainee_ *PListe2Chainee;

typedef struct Liste2Chainee_ { //liste doublement chainee
	PListe2Chainee pred;
	PListe2Chainee succ;
	char c;
} Liste2Chainee;

typedef struct Alignement_ {
	PListe2Chainee x_bar_first;
	PListe2Chainee y_bar_first;		
	PListe2Chainee x_bar_last;
	PListe2Chainee y_bar_last;		
} Alignement;

int lire_sequences(int *n, int *m, char **x, char **y, const char *nom_fichier);

int calcul_csub (char a, char b);

PListe2Chainee nouveau_elem_liste (char c, PListe2Chainee pred, PListe2Chainee succ);

void liberer_alignement (Alignement a);

void afficher_alignement(Alignement a);

long long current_timestamp_nsec();

#endif
