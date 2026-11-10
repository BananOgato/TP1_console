#include "graham.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham) {
	// ALGORITHME DU PARCOURS DE GRAHAM (avec aide de wikipedia)

	*pile_Graham = init_pile(nb_pts);

	// Empile p0, p1
	for (int i = 0; i < 2; i++)
		ajouter_a_pile(pile_Graham, tab_pts[i]);
	
	// Initialisation point sommet et le point second (sommet - 1)
	t_point sommet, second;

	// Pour les points p3 à pN-1
	for (int i = 2; i < nb_pts; i++) {
		// Copie du point sommet de la pile (pB)
		get_sommet(pile_Graham, &sommet);
		// Copie du point suivant du somment de la pile (pA)
		get_suiv_sommet(pile_Graham, &second);
		
		// Segment Sommet-Second-Suivant est un virage vers la droite
		while (prod_vectoriel(&sommet, &second, &tab_pts[i]) > 0) {
			// Dépile pB de la pile
			enlever_a_pile(pile_Graham);
			get_sommet(pile_Graham, &sommet);
			get_suiv_sommet(pile_Graham, &second);
		}
		// Empile le point pi dans la pile
		ajouter_a_pile(pile_Graham, tab_pts[i]);
	}

	get_sommet(pile_Graham, &sommet);
	get_suiv_sommet(pile_Graham, &second);

	printf("pile %d : point %d : (%d; %d)\n",
		0,
		pile_Graham->items[0].position,
		pile_Graham->items[0].posx,
		pile_Graham->items[0].posy
	);
	for (int i = 0; i < pile_Graham->sommet; i++) {
		printf("pile %d : point %d : (%d; %d)\n",
			i + 1,
			pile_Graham->items[i + 1].position,
			pile_Graham->items[i + 1].posx,
			pile_Graham->items[i + 1].posy
		);
		dessiner_lig(
			pile_Graham->items[i].posx,		pile_Graham->items[i].posy, 
			pile_Graham->items[i + 1].posx, pile_Graham->items[i + 1].posy
		);
	}
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, sommet.posx, sommet.posy);

	pause_ecran();

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// AFFICHAGE DE LA SOLUTION
	// nettoyer l'écran
	nettoyer_ecran();

	// Redessiner tout les points (sans vecteurs polaires)
	for (int i = 0;i < nb_pts;i++) {
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, tab_pts[i].position);
	}

	return pile_Graham->sommet + 1;
}