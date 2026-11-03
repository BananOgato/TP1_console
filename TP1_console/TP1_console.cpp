/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "tab_points.h"
#include "tab_pile.h"
#include "tab_affichage.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * MAIN
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int main() {
	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// INITIALISATION 

	//Variables
	t_point tab_pts[TAILLE], h_ref;
	int pos_pt_min;

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

	printf("%d : %d\n", h_ref.posx, h_ref.posy);

	// Calcul et tri des angles polaires
	calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
	trier_pts(tab_pts, TAILLE);

	for (int i = 0; i < TAILLE; i++) {
		printf("%d:    %d ; %d ; dist: %lf ; angle %lf\n", i, tab_pts[i].posx, tab_pts[i].posy, 
			  (i) ? tab_pts[i].dist : 0, (i) ? tab_pts[i].rad : 0);
	}
	
	mode_graphique();
	afficher_pts_en_ordre(tab_pts, TAILLE);
	//pause_ecran();

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// ALGORITHME DU PARCOURS DE GRAHAM (avec aide de wikipedia)

	t_pile pile = init_pile(TAILLE);

	for (int i = 0; i < 3; i++)
		push(&pile, tab_pts[1]);
	
	t_point sommet, second;

	for (int i = 0; i < 2; i++)
		push(&pile, tab_pts[i]);

	for (int i = 2; i < TAILLE; i++) {
		get_sommet(&pile, &sommet);
		get_suiv_sommet(&pile, &second);
		
		while (prod_vectoriel(&sommet, &second, &tab_pts[i]) > 0) {
			pop(&pile);
			get_sommet(&pile, &sommet);
			get_suiv_sommet(&pile, &second);
		}
		push(&pile, tab_pts[i]);
	}
	get_sommet(&pile, &sommet);
	get_suiv_sommet(&pile, &second);

	for (int i = 0; i < pile.sommet; i++) {
		printf("point %d: (%d; %d)\n", i + 1, pile.items[i + 1].posx, pile.items[i + 1].posy);
		dessiner_lig(pile.items[i].posx, pile.items[i].posy, 
					 pile.items[i + 1].posx, pile.items[i + 1].posy);
	}
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, sommet.posx, sommet.posy);

	pause_ecran();

	/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

	return EXIT_SUCCESS;
}