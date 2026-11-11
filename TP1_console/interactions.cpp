/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : MUCCIARONE Briana
 * Date : 10 nov 2026
 *
 * DESCIRPTION
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "interactions.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== */
/*                              DEFINITIONS DE FONCTIONS								 */
/* ======== ========== ========== ========== ========== ========== ========== ========== */

//Fonction qui demande le mode voulu (Avec aide de TRIGONO.cpp du cours 04)
int demander_mode(void) {
	//Variables pour le choix de l'utilisateur
	unsigned char choix;

	//Menu qui propose les options d'exécutions
	printf("/* =========== =========== =========== ===========*/ ");
	printf("\nChoisir un mode d'execution parmi les suivantes : \n");
	printf(" 1) Mode aleatoire de 20 points\n");
	printf(" 2) Mode a partir d'un fichier texte\n");
	printf(" 3) Mode simulation de moyenne\n");
	printf("/* =========== =========== =========== ===========*/\n");

	//Capture du choix de l'utilisateur
	do {
		printf("> ");
		scanf("%c", &choix);
		FFLUSH();
	} while ((choix != '3') && (choix != '2') && (choix != '1'));

	//Valeur de retour selon le choix de l'utilisateur
	switch (choix) {
	case '1': return 1;
		break;
	case '2': return 2;
		break;
	case '3': return 3;
		break;
	default:
		return 0;
	}
}

/* ======== ========== ========== ========== ========== ========== ========== ========== */

//Fonction qui permet de sélectionner un des fichiers points
FILE* choisir_fichier(void) {
	//Variable pour le nom du fichier
	char nom_fichier[80];
	//Pointeur pour le fichier ouvert
	FILE* fichier = NULL;

	//Boucle pour ouvrir le fichier
	do {
		//Demande le nom du fichier à l'utilisateur
		printf("\nChoisir un fichier:\n");
		scanf("%s", nom_fichier);

		//Ouverture du fichier en mode lecture
		fichier = fopen(nom_fichier, "r");

		//Si l'ouverture échoue
		if (fichier == NULL) {
			printf("Erreur: L'ouverture du fichier a echoue");
		}
	} while (fichier == NULL);
	//Retourne le pointeur du fichier ouvert
	return fichier;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== */

//Fonction qui lit et assigne les points du fichier dans le tableau dynamique
t_point* lire_points(FILE* fichier, int* nb_pts) {
	//Valeur pour la lecture du nombre de points
	int n = 0;

	//Lecture du nombre de points 
	fscanf(fichier, "%d", &n);
	*nb_pts = n;

	//Allocation du tableau dynamique
	t_point* tab_dyn = (t_point*)malloc(n * sizeof(t_point));
	//Validation de l'allocation
	assert(tab_dyn != NULL);

	//Boucle de lecture et assignation des points
	for (int i = 0;i < n;i++) {
		fscanf(fichier, "%d %d", &tab_dyn[i].posx, &tab_dyn[i].posy);
		tab_dyn[i].position = -1;

	}
	//Fermeture du fichier
	fclose(fichier);

	//Retourne le pointeur du tableau dynamique
	return tab_dyn;
}