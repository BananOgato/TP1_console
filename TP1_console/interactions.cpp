/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * Par : MUCCIARONE Briana 
 * Date : 04 nov 2026
 *
 * Cette libraries permet de gerer les interaction entre l'utilisateur et les fichiers.
 * On y retrouve les fonctions suivantes:
 * - demander_mode: Cette fonction demande et renvoie le choix du mode
 *					d'exécution de l'utilisateur.
 * - choisir_fichier: Cette fonction permet de sélectionner et d'ouvrir un fichier texte
 *					  de points.
 * - lire_points: Cette fonction lit le nombre de points depuis un fichier pour allouer
 *				  et remplir un tableau dynamique.				  
 * ======== ========== ========== ========== ========== ========== ========== ========== */

#include "interactions.h"

 /* ======== ========== ========== ========== ========== ========== ========== ========== */
 /*                              DEFINITIONS DE FONCTIONS								 */
 /* ======== ========== ========== ========== ========== ========== ========== ========== */

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * DEMANDER_MODE
 * Codé par Briana
 * Cette fonction affiche un menu et demande à l'utilisateur de choisir le mode
 * d'exécution du programme
 *
 * Paramètres:
 *  - Aucun
 *
 * Valeur de retour: Un entier qui représente le mode choisie (type: int)
 * ======== ========== ========== ========== ========== ========== ========== ========== */
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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * CHOISIR_FICHIER
 * Codé par Briana
 * Cette fonction demande le nom d'un fichier et redemande en boucle jusqu'a
 * l'ouverture du fichier.
 *
 * Paramètres:
 *  -Aucun
 *
 * Valeur de retour: Le pointeur vers le fichier ouvert (type: FILE*)
 * ======== ========== ========== ========== ========== ========== ========== ========== */

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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * LIRE_POINTS
 * Codé par Briana
 * Cette fonction lit le nombre de points depuis un fichier pour allouer
 * et remplir un tableau dynamique .
 *
 * Paramètres:
 *  -fichier: Le pointeur vers le fichier contenant les points (type: FILE*)
 *  -nb_pts: Le pointeur vers un entier pour stocker le nombre total de
 8           points (type: int)
 *
 * Valeur de retour: Le pointeur vers le tableau dynamique de points alloué (type: t_points*)
 * ======== ========== ========== ========== ========== ========== ========== ========== */

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