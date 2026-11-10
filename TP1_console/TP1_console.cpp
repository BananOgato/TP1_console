/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tab_points.h"
#include "tab_pile.h"
#include "tab_affichage.h"
#include "graham.h"

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

	// initialise le générateur "rand()"
	srand(time(NULL));
	// Initialise tableau avec des points aléatoires
	alea(0, TAILLE);
	init_tab_alea(tab_pts, TAILLE, 1400, 800);

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// TRIE DES POINTS

	pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);
	// Permutation pour obtenir le h_ref
	h_ref = placer_pt_reference(tab_pts, pos_pt_min);
	// Calcul et tri des angles polaires
	calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
	trier_pts(tab_pts, TAILLE);

	// afficher points trier dans le terminal
	for (int i = 0; i < TAILLE; i++) {
		printf("%d:    %d ; %d ; dist: %lf ; angle %lf\n", i, tab_pts[i].posx, tab_pts[i].posy, 
			  (i) ? tab_pts[i].dist : 0, (i) ? tab_pts[i].rad : 0);
	}
	
	// affichage des points
	mode_graphique();
	afficher_pts_en_ordre(tab_pts, TAILLE);
	pause_ecran();

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// ALGO GRAHAM

	t_pile pile;

	// algoritme graham
	algo_Graham_scan(tab_pts, TAILLE, &pile);

	//Fermeture de la fenêtre graphique
	fermer_mode_graph();
	
	/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */
	// LIBERATION MEMOIRE | FIN
	
	free(tab_pts);

	return EXIT_SUCCESS;
}