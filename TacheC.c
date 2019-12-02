#include <stdlib.h>
#include <stdio.h>
#include "Taches.h"
#include "outil.h"

int main (int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: ./progC nom_fichier\n");
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

	//Calculer la meilleure distance avec une complexite spatiale de Θ(m)
	long long start, end;
	start = current_timestamp_nsec();
	dist = DIST_2(&x,&y);
	end = current_timestamp_nsec();
	printf("Meilleure distance: %d\nTemps: %lld start: %lld end: %lld (ns)\n", dist, end-start,start, end);

	free(x);
	free(y);

	return 0;
}

