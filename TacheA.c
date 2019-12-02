#include <stdlib.h>
#include <stdio.h>
#include "Taches.h"
#include "outil.h"

int main (int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: ./progA nom_fichier\n");
		return 1;
	}

	int dist;
	int n,m;
	char *x,*y;

	//Recuperer les 2 sequences
	if (!lire_sequences(&n, &m, &x, &y, argv[1])) {
		free(x);
		free(y);
		return 1;
	}

	//Calculer la meilleure distance 
	dist = DIST_NAIF(&x,&y);
	printf("Meilleure distance: %d\n", dist);

	free(x);
	free(y);

	return 0;
}