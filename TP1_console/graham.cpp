/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : LABRE Paul
 * Date : 3 nov 2026
 *
 * ce fichier gere la gestion de l'algo pour Graham
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "graham.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int affichage) {
	// ALGORITHME DU PARCOURS DE GRAHAM (avec aide de wikipedia)

	*pile_Graham = init_pile(nb_pts);

	// Empile p0, p1
	for (int i = 0; i < 2; i++) {
		ajouter_a_pile(pile_Graham, tab_pts[i]);
	}
	if (affichage) {
		dessiner_lig(
			pile_Graham->items[0].posx, pile_Graham->items[0].posy,
			pile_Graham->items[1].posx, pile_Graham->items[1].posy
		);
		delai_ecran(DELAIS_ECRANS);
	}

	// Initialisation point sommet et le point second (sommet - 1)
	t_point sommet, second;

	// Pour les points p3 à pN-1
	for (int i = 2; i < nb_pts; i++) {
		// Copie du point sommet de la pile (pB)
		get_sommet(pile_Graham, &sommet);
		// Copie du point suivant du somment de la pile (pA)
		get_suiv_sommet(pile_Graham, &second);

		if (affichage) {
			dessiner_lig(second.posx, second.posy, sommet.posx, sommet.posy);
			delai_ecran(DELAIS_ECRANS);
		}

		// Segment Sommet-Second-Suivant est un virage vers la droite
		while (prod_vectoriel(&sommet, &second, &tab_pts[i]) > 0) {
			// Dépile pB de la pile
			if (affichage) {
				effacer_lig(second.posx, second.posy, sommet.posx, sommet.posy);
				delai_ecran(DELAIS_ECRANS);
			}
			enlever_a_pile(pile_Graham);
			get_sommet(pile_Graham, &sommet);
			get_suiv_sommet(pile_Graham, &second);
		}
		// Empile le point pi dans la pile
		ajouter_a_pile(pile_Graham, tab_pts[i]);
	}
	get_sommet(pile_Graham, &sommet);
	get_suiv_sommet(pile_Graham, &second);
	if (affichage) {
		dessiner_lig(second.posx, second.posy, sommet.posx, sommet.posy);
		delai_ecran(DELAIS_ECRANS);
		dessiner_lig(
			sommet.posx, sommet.posy, pile_Graham->items[0].posx, pile_Graham->items[0].posy);
	}

	if (affichage) {
		for (int i = 0; i <= pile_Graham->sommet; i++)
			printf("%d -> ", pile_Graham->items[i].position);
		printf("0\n");
		printf("Nombre points : %d\n", pile_Graham->sommet + 1);

		pause_ecran();
	}

	return pile_Graham->sommet + 1;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// SIMULATION_MOYENNE
// Effectue nb_tests parcours de Graham sur nb_pts points aleatoires, SANS affichage.
// Retourne la moyenne du nombre de points de l'enveloppe convexe.
double simulation_moyenne(int nb_pts, int nb_tests) {
	t_pile pile_Graham;			// la pile-solution de l'enveloppe
	t_point* tab_pts = NULL;	// le tableau dynamique des points
	t_point h_ref = { 0 };		// le point de référence horizontal
	int p_min;					// la position du point-minimal p0
	int nb_pts_tot = 0;			// le nb. total de points-enveloppe

	// Allocation du tableau dynamique + validation
	tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
	if (tab_pts == NULL) {
		printf("Erreur: allocation du tableau dynamique impossible\n");
		return NULL;
	}

	for (int i = 0; i < nb_tests; i++) {
		// Points aléatoires
		init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

		// Point minimal en case [0] et point de référence
		p_min = trouver_pt_minimal(tab_pts, nb_pts);
		h_ref = placer_pt_reference(tab_pts, p_min);

		// Angles polaires puis tri
		calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
		trier_pts(tab_pts, nb_pts);

		// Enveloppe convexe, sans affichage (mode_aff = 0)
		nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

		// Libération de la pile-solution
		liberer_pile(&pile_Graham);
	}

	free(tab_pts);

	return (double)nb_pts_tot / nb_tests;
}