/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : MUC Briana
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

/* ======== ========== ========== ========== ========== ========== ========== ========== */

double simulation_moyenne(int nb_pts, int nb_tests) {
	t_pile pile_Graham;          // la pile-solution de l'enveloppe
	t_point* tab_pts = NULL;     // le tableau dynamique des points
	t_point h_ref = { 0 };       // le point de référence horizontal
	int p_min;                   // la position du point-minimal p0
	int nb_pts_tot = 0;          // le nb. total de points-enveloppe

	// Allocation du tableau dynamique et validation
	tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
	assert(tab_pts != NULL);

	for (int i = 0; i < nb_tests; i++) {
		// Points aléatoires
		init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

		// Point minimal -> case [0] + point de référence
		p_min = trouver_pt_minimal(tab_pts, nb_pts);
		h_ref = placer_pt_reference(tab_pts, p_min);

		// Angles polaires puis tri
		calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
		trier_pts(tab_pts, nb_pts);

		// Graham SANS affichage (la fonction crée la pile avec init_pile)
		nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

		// Libérer la pile-solution
		liberer_pile(&pile_Graham);
	}

	free(tab_pts);

	return (double)nb_pts_tot / nb_tests;
}