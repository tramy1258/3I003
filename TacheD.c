#include <stdlib.h>
#include <stdio.h>
#include "Taches.h"
#include "outil.h"

int main (int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: ./progD nom_fichier\n");
		return 1;
	}

	//int dist;
	int n,m;
	char *x,*y;
	Alignement a;

	//Recuperer les 2 sequences
	if (!lire_sequences(&n, &m, &x, &y, argv[1])) {
		free(x);
		free(y);
		return 1;
	}

	//Calculer un alignement optimal
	long long start, end;
	start = current_timestamp_nsec();
	
	a = SOL_2(&x,&y,n,m);
	
	end = current_timestamp_nsec();
	printf("temps SOL_2 %lld start %lld end %lld (ns)\n", end-start,start, end);

	char ans;
	printf("Afficher l'alignement ? y (yes) or n (no)\n");
	do {
		scanf("%c", &ans);
	} while (!(ans == 'y' || ans == 'n') );

	if (ans == 'y') {
		printf("Alignement optimal:\n");
		afficher_alignement(a);
	}

	liberer_alignement(a);
	free(x);
	free(y);

	return 0;
}

