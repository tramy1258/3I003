#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "outil.h"

int lire_sequences (int *n, int *m, char **x, char **y, const char *nom_fichier) {

	//Ouvrir le fichier
	FILE *f = fopen(nom_fichier,"r");
	
	if (f==NULL) {
		printf("Probleme d'ouverture du fichier\n");
		return 0;
	}
	
	//Recuperer les tailles des 2 sequences
	if (fscanf(f, "%d\n%d\n", n, m) != EOF) {
		printf("|x|=%d\n|y|=%d\n", *n, *m);
	} else {
		fclose(f);
		printf("Probleme dans le contenu du fichier\n");
		return 0;
	}

	//Lire x
	*x = malloc(sizeof(char)*(*n + 1));
	*y = malloc(sizeof(char)*(*m + 1));
	char c;
	int i = 0;
	while (i < *n) {
		if (feof(f)) {
			fclose(f);
			printf("Probleme dans le contenu du fichier\n");
			return 0;
		}
		c = fgetc(f);
		if (!isspace(c)) {
			if (!(c=='A' || c=='T' || c=='G' || c=='C')) {
				printf("Probleme dans le contenu du fichier\n");
				fclose(f);
				return 0;
			}
			(*x)[i] = c;
			i++;
		}
	}
	(*x)[i] = '\0';

	//Lire y
	i = 0;
	while (i < *m) {
		if (feof(f)) {
			fclose(f);
			printf("Probleme dans le contenu du fichier\n");
			return 0;
		}
		c = fgetc(f);
		if (!isspace(c)) {
			if (!(c=='A' || c=='T' || c=='G' || c=='C')) {
				printf("Probleme dans le contenu du fichier\n");
				fclose(f);
				return 0;
			}
			(*y)[i] = c;
			i++;
		}
	}
	(*y)[i] = '\0' ;

	//Affichage des deux sequences lues
	char ans;
	printf("Afficher x et y? y (yes) or n (no)\n");
	do {
		scanf("%c",&ans);
	} while (!(ans == 'y' || ans == 'n'));
	if (ans == 'y') {
		printf("%s\n%s\n",*x,*y);
	}
	
	fclose(f);
	return 1;
}

int calcul_csub (char a, char b) {
	if (a == 'A') {
		if (b == 'A') {
			return 0;
		}
		if (b == 'T') {
			return 3;
		}
		if (b == 'G' || b == 'C') {
			return 4;
		}
		return -1;
	}

	if (a == 'T') {
		if (b == 'T') {
			return 0;
		}
		if (b == 'A') {
			return 3;
		}
		if (b == 'G' || b == 'C') {
			return 4;
		}
		return -1;	
	}

	if (a == 'G') {
		if (b == 'G') {
			return 0;
		}
		if (b == 'C') {
			return 3;
		}
		if (b == 'A' || b == 'T') {
			return 4;
		}
		return -1;
	}

	if (a == 'C') {
		if (b == 'C') {
			return 0;
		}
		if (b == 'G') {
			return 3;
		}
		if (b == 'A' || b == 'T') {
			return 4;
		}
		return -1;
	}
	return -1;
}

PListe2Chainee nouveau_elem_liste (char c, PListe2Chainee pred, PListe2Chainee succ) {
	PListe2Chainee l = (PListe2Chainee) malloc(sizeof(Liste2Chainee));
	if (l == NULL) {
		printf("Probleme de creation nouveau element de la liste\n");
		return NULL;
	}
	l->pred = pred;
	l->succ = succ;
	l->c    = c;
	return l;
}

void liberer_alignement (Alignement a) {
	Liste2Chainee *first_x = a.x_bar_first;
	Liste2Chainee *first_y = a.y_bar_first;
	Liste2Chainee *tmp_x;
	Liste2Chainee *tmp_y;

	while (first_x != NULL) { //x_bar et y_bar de meme taille
		tmp_x = first_x->succ;
		free(first_x);
		first_x = tmp_x;

		tmp_y = first_y->succ;
		free(first_y);
		first_y = tmp_y;
	}
}

void afficher_alignement(Alignement a) {
	Liste2Chainee *first_x = a.x_bar_first;
	Liste2Chainee *first_y = a.y_bar_first;

	//afficher x_bar
	while (first_x != NULL) { 
		printf("%c", first_x->c);
		first_x = first_x->succ;
	}
	
	printf("\n");
	//afficher y_bar
	while (first_y != NULL) {
		printf("%c", first_y->c);
		first_y = first_y->succ;
	}	
}

long long current_timestamp_nsec () {
    struct timespec spec;
    if (clock_gettime(CLOCK_REALTIME, &spec) != 0) {
    	printf("error clock_gettime\n");
    	return 0;
    }
    return spec.tv_sec*1000000000LL + spec.tv_nsec; //en nanoseconds
}