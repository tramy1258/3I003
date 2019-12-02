#include <stdlib.h>
#include <stdio.h>
#define Csub(a,b) (a==b?0:(abs(a-b)==19||abs(a-b)==4?3:4))

/*struct Point {
	int x;
	int y;
};

struct Point a (int x, int y) {
	return (x,y);
};*/

int main () {
	/*printf("%d %d\n",'T'-'A','G'-'T');
	printf("%d\n%d\n", Csub('T','T'),Csub('G','T')); //4 lignes 3 cols
	int **T;
	//T = (int **)malloc(sizeof(int) * 3 * 4);
	*T = (int *)malloc(sizeof(int) * 1 * 2);
	printf("a\n");
	**T = 0;
	*((*T)+1) = 19;
	printf("b\n");
	/*	int i,j;
	for (i=1;i<3;i++) { //1ere ligne
		(*T)[0+i] = 2*i;
	}
	for (i=1;i<4;i++) { //1ere colonne
		(*T)[i*3] = 3*i;
	}
	for (i=1;i<3;i++) {
		for (j=1;j<4;j++) {
			(*T)[i*3+j] = 5;
		}
	}
	for (i=0;i<4;i++) {
		for (j=0;j<3;j++) {
			printf("%c\n",(*T)[i*3+j]+'0' );
		}
		printf("\n");
	}
	printf("T[0] = %d\nT[1] = %d\n",**T,*((*T)+1));

		/*PListe2Chainee test = mot_gaps(5);
	PListe2Chainee tmp = test;

	while (tmp!=NULL) {
		printf("%c", tmp->c);
		tmp = tmp->succ;
	}
	printf("\n");

	tmp = test;

	while (test != NULL) {
		free(test);
		test = tmp->succ;
		if (test == NULL) {
			break;
		}
		tmp = test->succ;
	}
*/
	//Tester align_lettre_mot
	/*char *x2 = malloc(sizeof(char));
	*x2 = 'A';
	char *y2 = malloc(sizeof(char) * 6);
	*y2 = 'C';
	*(y2+1) = 'C';
	*(y2+2) = 'C';
	*(y2+3) = 'G';
	*(y2+4) = 'G';
	*(y2+5) = 'G';
	Alignement a1 = align_lettre_mot(&x2,&y2);
	afficher_alignement(a1);

	liberer_alignement(a1);


	free(x2);
	free(y2);*/

	return 0;
}