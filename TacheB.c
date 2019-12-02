#include <stdlib.h>
#include <stdio.h>
#include "Taches.h"
#include "outil.h"

int main (int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: ./progB nom_fichier\n");
		return 1;
	}

	int dist;
	int n,m;
	char *x,*y;
	int *T;
	Alignement a;

	//Recuperer les 2 sequences
	if (!lire_sequences(&n, &m, &x, &y, argv[1])) {
		free(x);
		free(y);
		return 1;
	}

	//Calculer la meilleure distance et un alignement optimal
	long long start, end;
	start = current_timestamp_nsec();
	
	PROG_DYN(&x,&y,&dist,&a,&T);
	
	end = current_timestamp_nsec();
	printf("\ntemps PROG_DYN: %lld start: %lld end: %lld (ns)\n", end-start,start, end);
	printf("Meilleure distance: %d\n", dist);

	char ans;
	printf("Afficher l'alignement ? y (yes) or n (no)\n");
	do {
		scanf("%c", &ans);
	} while (!(ans == 'y' || ans == 'n') );

	if (ans == 'y') {
		printf("Alignement optimal:\n");
		afficher_alignement(a);
	}

	free(x);
	free(y);
	free(T);
	liberer_alignement(a);

	return 0;
}

