#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "outil.h"
#include "Taches.h"
		
#define Csub_min 0
#define Csub_max 4			    
#define Cdel 2
#define Cins 2
#define min_bis(x,y) (x<y ? x : y)
#define min(x,y,z) (min_bis(x,min_bis(y,z)))
#define elem(T,i,j,m) (*((*T) + (m) * (i) + (j)))

int DIST_NAIF(char *x[], char *y[]) {
	printf("\nDIST_NAIF\n");
	return DIST_NAIF_REC(x,y,0,0,0,-1);
}

int DIST_NAIF_REC(char *x[], char *y[], int i, int j, int c, int dist) {
	int n = strlen(*x);
	int m = strlen(*y);
	if (i == n && j == m) {
		if (dist == -1 || c < dist) {
			dist = c;
		}
	} 
	else {
		if (i < n && j < m) {
			dist = DIST_NAIF_REC(x, y, i+1, j+1, c + calcul_csub((*x)[i],(*y)[j]), dist);			
		}
		if (i < n) {
			dist = DIST_NAIF_REC(x, y, i+1, j, c + Cdel, dist);
		} 
		if (j < m) {
			dist = DIST_NAIF_REC(x, y, i, j+1, c + Cins, dist);
		}
	}

	return dist;
}

void PROG_DYN(char *x[], char *y[], int *dist, Alignement *a, int **T) {

	long long start, end;

	//DIST_1
	start = current_timestamp_nsec();

	*dist = DIST_1(x,y,T);

	end = current_timestamp_nsec();
	printf("temps DIST_1 %lld start %lld end %lld (ns)\n", end-start, start, end);

	//SOL_1
	start = current_timestamp_nsec();

	*a    = SOL_1(x,y,T); 

	end = current_timestamp_nsec();
	printf("temps SOL_1 %lld start %lld end %lld (ns)\n",  end-start, start, end);
}

int DIST_1(char *x[], char *y[], int **T) {

	printf("\nDIST_1\n");
	int n = strlen(*x);
	int m = strlen(*y);
	*T = (int *) malloc(sizeof(int) * (m + 1) * (n + 1)); //tableau 2-dimensionnel de m+1 colonnes et n+1 lignes
	**T = 0; //T[0][0]
	int i, j;

	//premiere ligne
	for (j = 1; j <= m; j++) {
		elem(T,0,j,m+1) = j * Cins; //T[0][j]
	}

	//premiere colonne
	for (i = 1; i <= n; i++) {
		elem(T,i,0,m+1) = i * Cdel; //T[i][0]
	}

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			elem(T,i,j,m+1) = min(elem(T,i-1,j-1,m+1) + calcul_csub((*x)[i-1],(*y)[j-1]), 
								  elem(T,i  ,j-1,m+1) + Cins,
							  	  elem(T,i-1,j  ,m+1) + Cdel);
		}
	}

	//Affichage du tableau des meilleures distances
	char ans;
	printf("Afficher le tableau des meilleures distances? y (yes) or n (no)\n");
	do {
		scanf("%c", &ans);
	} while (!(ans == 'y' || ans == 'n'));
	if (ans == 'y') {
		for (i = 0; i <= n; i++) {
			for (j = 0; j <= m; j++) {
				printf("%5d", elem(T,i,j,m+1));
			}
			printf("\n");
		}
	}
	
	return elem(T,n,m,m+1);
}

int DIST_2(char *x[], char *y[]) {

	printf("\nDIST_2\n");
	int n = strlen(*x);
	int m = strlen(*y);
	int T[2][m+1]; //tableau 2-dimensionnel de m+1 colonnes et 2 lignes
	int j;
	int i = 1; //indice des caracteres de x
	int ancienne = 0;
	int nouvelle = 1;

	//premiere ligne
	for (j = 0; j <= m; j++) {
		T[ancienne][j] = j * Cins;
	}

	//ALGO
	//on fait des calculs dans la ligne "nouvelle" du tableau en utilisant les valeurs dans la ligne "ancienne"
	//on inverse les valeurs d'"ancienne " et "nouvelle" (0 ou 1) pour chaque tour de boucle
	while (i<=n) {

		//premiere colonne de la 2eme ligne
		T[nouvelle][0] = i * Cdel;

		//les colonnes restantes
		for (j = 1; j <= m; j++) {
			T[nouvelle][j] = min(T[ancienne][j-1] + calcul_csub((*x)[i-1],(*y)[j-1]), 
								 T[nouvelle][j-1] + Cins,
					  	  		 T[ancienne][j]   + Cdel);
		}

		//la nouvelle ligne devient la ligne ancienne
		ancienne = (ancienne + 1) % 2;
		nouvelle = 1 - ancienne;

		//avancer au caractere suivant dans x
		i++;
	}

	return T[ancienne][m];
}

Alignement SOL_1(char *x[], char *y[], int **T) {

	printf("\nSOL_1\n");
	int n = strlen(*x);
	int m = strlen(*y);
	int i = n, j = m;

	//l'alignement resultat
	Alignement a;
	a.x_bar_first = NULL;
	a.y_bar_first = NULL;
	a.x_bar_last  = NULL;
	a.y_bar_last  = NULL;

	PListe2Chainee tmp_x, tmp_y;

	//Contruire un alignement optimal du dernier caractere au premier caractere
	while (i>0 || j>0) {

		//Remplacer un caractere de x par un caractere de y
		if (i>0 && j>0) {
			if (elem(T,i,j,m+1) == elem(T,i-1,j-1,m+1) + calcul_csub((*x)[i-1],(*y)[j-1])) {				
				tmp_x = nouveau_elem_liste((*x)[i-1], NULL, a.x_bar_first);
				tmp_y = nouveau_elem_liste((*y)[j-1], NULL, a.y_bar_first);
				if (a.x_bar_first != NULL) {
					(a.x_bar_first)->pred = tmp_x;
					(a.y_bar_first)->pred = tmp_y;
				}
				a.x_bar_first = tmp_x;
				a.y_bar_first = tmp_y;

				//Reference vers les derniers caracteres de l'alignement (pour la concatenation)
				if (i==n && j==m) {
					a.x_bar_last = a.x_bar_first;
					a.y_bar_last = a.y_bar_first;
				}	

				i--;
				j--;
				continue;
			}
		}

		//Supprimer un caractere de x
		if (j>0) {
			if (elem(T,i,j,m+1) == elem(T,i,j-1,m+1) + Cins) {
				tmp_x = nouveau_elem_liste('-'      , NULL, a.x_bar_first);
				tmp_y = nouveau_elem_liste((*y)[j-1], NULL, a.y_bar_first);
				if (a.x_bar_first != NULL) {
					(a.x_bar_first)->pred = tmp_x;
					(a.y_bar_first)->pred = tmp_y;
				}
				a.x_bar_first = tmp_x;
				a.y_bar_first = tmp_y;

				//Reference vers les derniers caracteres de l'alignement (pour la concatenation)
				if (i==n && j==m) {
					a.x_bar_last = a.x_bar_first;
					a.y_bar_last = a.y_bar_first;
				}	

				j--;
				continue;
			}
		}

		//Inserer un caractere dans x
		if (i>0) {
			if (elem(T,i,j,m+1) == elem(T,i-1,j,m+1) + Cdel) {
				tmp_x = nouveau_elem_liste((*x)[i-1], NULL, a.x_bar_first);
				tmp_y = nouveau_elem_liste('-'      , NULL, a.y_bar_first);
				if (a.x_bar_first != NULL) {
					(a.x_bar_first)->pred = tmp_x;
					(a.y_bar_first)->pred = tmp_y;
				}
				a.x_bar_first = tmp_x;
				a.y_bar_first = tmp_y;

				//Reference vers les derniers caracteres de l'alignement (pour la concatenation)
				if (i==n && j==m) {
					a.x_bar_last = a.x_bar_first;
					a.y_bar_last = a.y_bar_first;
				}		

				i--;
				continue;
			}
		}

	}
	
	return a;
}

void mot_gaps(int k, PListe2Chainee *last, PListe2Chainee *first) {

	if (k <= 0) {
		*first = NULL;
		*last  = NULL;
		return;
	}

	int i;
	PListe2Chainee tmp;
	PListe2Chainee res = nouveau_elem_liste('-', NULL, NULL);

	*last = res; //garder la reference vers le dernier element pour la concatenation

	for (i = 1; i < k; i++) {
		tmp = nouveau_elem_liste('-', NULL, res);
		res->pred = tmp;
		res = tmp;
	}

	*first = res;
}

Alignement align_lettre_mot(char *x[], char *y[], int n, int m) {
	
	//x de longueur 1, y non vide de longueur quelconque
	//ALGO
	//chercher l'indice i_best pour que la substitution de y[i] et x[0] soit de cout min
	//comparer le cout de la substitution (c1) avec le cout d'une suppression suivi d'une insertion (c2)
	//ici, c1 <= c2
	//inserer les gaps pour les autres caracteres de y

	int gaps_debut = 0; //nombre gaps au debut de x_bar = i_best
	int cout_best = Csub_max;
	int i = 0;
	int tmp_cout;

	do {
		tmp_cout = calcul_csub((*x)[0],(*y)[i]);
		
		if (cout_best > tmp_cout || cout_best == -1) {
			cout_best = tmp_cout;
			gaps_debut   = i;
		} 
		i++;
	} while (cout_best != Csub_min && i < m);

	Alignement a;
	a.x_bar_first = NULL;
	a.y_bar_first = NULL;
	a.x_bar_last  = NULL;
	a.y_bar_last  = NULL;

	PListe2Chainee debut_align1, fin_align1, debut_align2, fin_align2, tmp;

	if (cout_best > Cdel+Cins) { //jamais le cas ici mais pour etre plus general
		gaps_debut = m;
	}

	//-----x_bar de l'alignement a-----

	//gaps jusqu'a la substitution
	mot_gaps(gaps_debut, &fin_align1, &debut_align1); 

	//la lettre x
	tmp = nouveau_elem_liste((*x)[0], fin_align1, NULL);

	if (fin_align1 != NULL)	{
		fin_align1->succ = tmp;
	}

	//gaps jusqu'a la fin
	mot_gaps(m - gaps_debut - 1, &fin_align2, &debut_align2);
	tmp->succ = debut_align2;

	a.x_bar_first = debut_align1;
	a.x_bar_last  = fin_align2;

	//substitution au debut
	if (debut_align1 == NULL) {
		a.x_bar_first = tmp;
	}

	//substitution a la fin ou pas de substitution
	if (fin_align2 == NULL) {
		a.x_bar_last = tmp;
	}

	//-----y_bar de l'alignement a-----

	//y_bar contitent tous les caracteres de y
	a.y_bar_first = nouveau_elem_liste((*y)[m-1], NULL, NULL); //y non vide
	a.y_bar_last  = a.y_bar_first;

	for (i = m-2; i >= 0; i--) {
		tmp = nouveau_elem_liste((*y)[i], NULL, a.y_bar_first);
		(a.y_bar_first)->pred = tmp;
		a.y_bar_first = tmp;
	}

	//pas de substitution
	if (gaps_debut == m) {
		tmp = nouveau_elem_liste('-',a.y_bar_last,NULL);
		(a.y_bar_last)->succ = tmp;
		a.y_bar_last = tmp;
	}

	return a;
}

int coupure(char *x[], char *y[], int n, int m) {

	int i = 1;
	int j;
	int i_star = n/2;
	int anciD = 0;
	int nouvD = 1;
	int anciI = 0;
	int nouvI = 1;
	int tmp;

	int D[2][m+1]; //tableau des meilleures distances
	int I[2][m+1]; //tableau des coupures

	//premiere ligne
	for (j = 0; j <= m; j++) {
		D[anciD][j] = j * Cins;
		I[anciI][j] = j;
	}

	//Calculer les meilleures distances pour i=1 a i=i_star
	while (i <= i_star) {
		
		//premiere colonne de la nouvelle ligne
		D[nouvD][0] = i * Cdel;

		//les colonnes restantes
		
		for (j = 1; j <= m; j++) {			
			D[nouvD][j] = min(D[anciD][j-1] + calcul_csub((*x)[i-1],(*y)[j-1]), 
							  D[nouvD][j-1] + Cins,
					  	  	  D[anciD][j]   + Cdel);
		}
		
		//la nouvelle ligne devient la ligne ancienne
		anciD = (anciD + 1) % 2;
		nouvD = 1 - anciD;

		//avancer au caractere suivant dans x
		i++;
	}

	//Calculer les meilleures distances et les coupures pour i=i_star+1 a i=n-1
	while (i <= n) {
		
		//premiere colonne de la nouvelle ligne
		D[nouvD][0] = i * Cdel;
		I[nouvI][0] = 0;

		//les colonnes restantes	
		for (j = 1; j <= m; j++) {

			//si la substitution est optimale
			D[nouvD][j] = D[anciD][j-1] + calcul_csub((*x)[i-1],(*y)[j-1]);
			I[nouvI][j] = I[anciI][j-1];

			//si l'insertion est optimale
			tmp = D[nouvD][j-1] + Cins;
			if (tmp < D[nouvD][j]) {
				D[nouvD][j] = tmp;
				I[nouvI][j] = I[nouvI][j-1];
			}

			//si la suppression est optimale
			tmp = D[anciD][j]   + Cdel;
			if (tmp < D[nouvD][j]) {
				D[nouvD][j] = tmp;
				I[nouvI][j] = I[anciI][j];				
			}
		}

		//la nouvelle ligne devient la ligne ancienne
		anciD = (anciD + 1) % 2;
		nouvD = 1 - anciD;

		anciI = (anciI + 1) % 2;
		nouvI = 1 - anciI;

		//avancer au caractere suivant dans x
		i++;
	}

	return I[anciI][m];

}

Alignement SOL_2(char *x[], char *y[], int n, int m) {

	//Affichage les sequences recursives
	/*
	int k;

	printf("SOL_2 ");
	if (n>0) {
		for (k = 0; k<n;k++) {
			printf("%c",(*x)[k] );
		}
	} else {
		printf("vide");
	}
	printf(" ");
	if (m>0) {
		for (k = 0; k<m;k++) {
			printf("%c",(*y)[k] );
		}
	} else {
		printf("vide");
	}
	printf("\n");
	*/

	Alignement a;
	int i;
	PListe2Chainee tmp;

	//-----3 cases de base-----
	if (n==0) {

		//x_bar contenant m gaps
		mot_gaps(m,&(a.x_bar_last),&(a.x_bar_first));

		//y_bar contenant tous les caracteres de y
		a.y_bar_first = nouveau_elem_liste((*y)[m-1], NULL, NULL); //y non vide
		a.y_bar_last  = a.y_bar_first;

		for (i = m-2; i >= 0; i--) {
			tmp = nouveau_elem_liste((*y)[i], NULL, a.y_bar_first);
			(a.y_bar_first)->pred = tmp;
			a.y_bar_first = tmp;
		}

		return a;
	}

	if (m==0) {

		//x_bar contenant tous les caracteres de x
		a.x_bar_first = nouveau_elem_liste((*x)[n-1], NULL, NULL); //y non vide
		a.x_bar_last  = a.x_bar_first;

		for (i = n-2; i >= 0; i--) {
			tmp = nouveau_elem_liste((*x)[i], NULL, a.x_bar_first);
			(a.x_bar_first)->pred = tmp;
			a.x_bar_first = tmp;
		}

		//y_bar contenant n gaps
		mot_gaps(n,&(a.y_bar_last),&(a.y_bar_first));

		return a;
	}

	if (n==1) {
		return align_lettre_mot(x,y,n,m);
	}

	//-----cas general-----
	int j_star = coupure(x,y,n,m);
	int i_star = n/2;

	//Calculer l'alignement de x1,y1
	Alignement a1 = SOL_2(x,y,i_star,j_star);

	//Calculer l'alignement de x2,y2
	char *p1 = *x+i_star, *p2 = *y+j_star; //probleme avec c si l'on fait directement dans l'appel
	Alignement a2 = SOL_2(&p1,&p2,n-i_star,m-j_star);

	//Concatener les deux alignements
	(a1.x_bar_last)->succ  = a2.x_bar_first;
	(a2.x_bar_first)->pred = a1.x_bar_last;
	(a1.y_bar_last)->succ  = a2.y_bar_first;
	(a2.y_bar_first)->pred = a1.y_bar_last;

	a.x_bar_first = a1.x_bar_first;
	a.y_bar_first = a1.y_bar_first;
	a.x_bar_last  = a2.x_bar_last;
	a.y_bar_last  = a2.y_bar_last;

	return a;

}
