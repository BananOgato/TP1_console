/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : MUC Briana et LABRE Paul
 * Date : 10 nov 2026
 *
 * ce programme permet de jouer avec l'algorithme de graham
 * il possede 3 modes:
 * - Appliquer l'algorithme a 20 point repartis aleatoirement
 * - Appliquer l'algorithme a un fichier de point predefinis
 * - Faire la moyenne sur un nombre de points de l’enveloppe
 * 
 * Le github associer: https://github.com/BananOgato/TP1_console/commits/Graham_/
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#define _CRT_SECURE_NO_WARNINGS

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tab_points.h"
#include "tab_pile.h"
#include "tab_affichage.h"
#include "graham.h"
#include "interactions.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * MAIN
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int main() {
	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// INITIALISATION 

	//Variables
	t_point *tab_pts = NULL;
	t_point h_ref;
	int pos_pt_min;

	// Allocation dynamique avec malloc
	tab_pts = (t_point*)malloc(TAILLE * sizeof(t_point));
	if (tab_pts == NULL)
		printf("ERREUR d'allocation de mémoire de tab_pts");

	int mode = 0;
	int nb_pts = 0;

	// initialise le générateur "rand()"
	srand(time(NULL));

	//Demande du mode à l'utilisateur
	mode = demander_mode();

	switch (mode) {
	case 1: //Pour le mode aléatoire
		nb_pts = TAILLE;
		//Allocation dynamique avec malloc
		tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
		//Validation de l'allocation
		assert(tab_pts != NULL);
		init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);
		break;
	case 2: //Pour le mode fichier
		FILE * fichier = choisir_fichier();
		tab_pts = lire_points(fichier, &nb_pts);
		break;
	}

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// TRIE DES POINTS

	pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);
	// Permutation pour obtenir le h_ref
	h_ref = placer_pt_reference(tab_pts, pos_pt_min);
	// Calcul et tri des angles polaires
	calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
	trier_pts(tab_pts, nb_pts);

	// afficher points trier dans le terminal
	for (int i = 0; i < nb_pts; i++) {
		printf("%d:    %d ; %d ; dist: %lf ; angle %lf\n", i, tab_pts[i].posx, tab_pts[i].posy, 
			  (i) ? tab_pts[i].dist : 0, (i) ? tab_pts[i].rad : 0);
	}
	
	// affichage des points
	mode_graphique();
	afficher_pts_en_ordre(tab_pts, nb_pts);
	pause_ecran();

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// ALGO GRAHAM

	t_pile pile;

	// algoritme graham
	algo_Graham_scan(tab_pts, nb_pts, &pile);

	//Fermeture de la fenêtre graphique
	fermer_mode_graph();
	
	/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */
	// LIBERATION MEMOIRE | FIN
	
	free(tab_pts);

	return EXIT_SUCCESS;
}