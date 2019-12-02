#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./auto dir_instances fic_resultat\n");
		return 0;
	}
	//Ouvrir le directoire pour prendre les instances
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);
    
    //Ouvrir le fichier résultat pour écrire
    FILE *f = fopen(agrv[2],"w");
    
    if (f== NULL) {
		printf("Probleme d'ouverture du fichier résultat\n");
		return 0;
    }
    if (d) {
        while ((dir = readdir(d)) != NULL) {
			system("./progB \"dir\"");
        }
        closedir(d);
    }
    return(0);     
}

50000 0 0 29181989300 70374798947
100000 0 0 116719499608 279712143389
