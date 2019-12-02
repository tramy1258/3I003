#ifndef TACHES_H_
#define TACHES_H_
#include "outil.h"

int DIST_NAIF(char *x[], char *y[]);

int DIST_NAIF_REC(char *x[], char *y[], int i, int j, int c, int dist);

void PROG_DYN(char *x[], char *y[], int *dist, Alignement *a, int **T);

int DIST_1(char *x[], char *y[], int **T);

int DIST_2(char *x[], char *y[]);

Alignement SOL_1(char *x[], char *y[], int **T);

Alignement SOL_2(char *x[], char *y[], int n, int m);

void mot_gaps(int k, PListe2Chainee *last, PListe2Chainee *first);

Alignement align_lettre_mot(char *x[], char *y[], int n, int m);

int coupure(char *x[], char *y[], int n, int m);

#endif