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

	//Allocation dynamique avec malloc
	tab_pts = (t_point*)malloc(TAILLE * sizeof(t_point));

	//Validation de l'allocation
	assert(tab_pts != NULL);

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
	//int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham);

	t_pile pile = init_pile(TAILLE);

	//Empile p0,p1 et p2
	for (int i = 0; i < 3; i++)
		push(&pile, tab_pts[i]);

	//Affichage des lignes entre les points (p0 à p1 et p1 à p2)
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
	dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);
	//Delai d'écran
	delai_ecran(300);
	
	//Initialisation point sommet (pA) et le point second (pB)
	t_point sommet, second;

	for (int i = 0; i < 2; i++)
		push(&pile, tab_pts[i]);

	//Pour les points p3 à pN-1
	for (int i = 2; i < TAILLE; i++) {
		//Copie du point sommet de la pile (pB)
		get_sommet(&pile, &sommet);
		//Copie du point suivant du somment de la pile (pA)
		get_suiv_sommet(&pile, &second);
		
		//Segment pA-pB-pi est un virage vers la droite
		while (prod_vectoriel(&sommet, &second, &tab_pts[i]) > 0) {
			//Dépile pB de la pile
			pop(&pile);
			//Efface la ligne entre pA-pB
			effacer_lig(sommet.posx, sommet.posy, second.posx, second.posy);
			//Delai d'écran
			delai_ecran(150);
			//Récupère les nouveau points sommet et second
			get_sommet(&pile, &sommet);
			get_suiv_sommet(&pile, &second);
		}
		//Empile le point pi dans la pile
		push(&pile, tab_pts[i]);
		//Affichage d'une ligne entre pB et pi
		dessiner_lig(second.posx, second.posy, tab_pts[i].posx, tab_pts[i].posy);
		//Délai d'écran
		delai_ecran(300);
	}
	//Retourne le nb d'éléments dans la pile
	//get_pile_size(const t_pile* pile);

	get_sommet(&pile, &sommet);
	get_suiv_sommet(&pile, &second);

	for (int i = 0; i < pile.sommet; i++) {
		printf("point %d: (%d; %d)\n", i + 1, pile.items[i + 1].posx, pile.items[i + 1].posy);
		dessiner_lig(pile.items[i].posx, pile.items[i].posy,
			pile.items[i + 1].posx, pile.items[i + 1].posy);
	}
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, sommet.posx, sommet.posy);

	pause_ecran();

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// AFFICHAGE DE LA SOLUTION
	//nettoyer l'écran
	nettoyer_ecran();

	//Redessiner tout les points (sans vecteurs polaires)
	for (int i = 0;i < TAILLE;i++) {
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, tab_pts[i].position);
	}

	//Initialiser la pile solution avec le nombre de points actuel
	algo_Graham_scan(tab_pts, nb_pts, t_pile * pile_Graham);

	//Affiche la pile solution
	affiche_segment(&pile);

	//Pausse écran
	pause_ecran();

	//Fermeture de la fenêtre graphique
	fermer_mode_graph();
	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */

	//Fonction d'affichage des segments de l'enveloppe
	/*void affiche_segment(t_pile *pile){
	//Affichage du nombre de points de la pile
	int tot;
	tot=get_pile_size(const t_pile* pile);
	printf("Il y a %d points dans la pile\n",tot);

	//Copie du point sommet
	t_points pt_fin;
	get_sommet(pile,&pt_fin);
	//Dépiler le point sommet
	pop(&pile);
	//Affichage du dernier numéro sur l'écran
	printf("%d\n",pt_fin.position);

	//Initiation des points p0 et p1
	t_points p0=pt_fin;
	t_point p1;

	while(vide(pile)==0){
	//Dépile le prochain point (p1)
	get_sommet(pile,&p1);
	pop(pile);
	//Dessine une ligne entre p0 et p1
	dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);
	//Affiche le numéro du p1
	printf("%d\n",p1.position);
	//Transfert de p1 dans p0
	p0=p1;
	}
	//Dessigne une ligne entre p0 et pt_fin
	dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, pt_fin.posx, pt_fin.posy);
	//Affiche le numéro du pt_fin
	printf("%d\n",pt_fin.pos);
	}
	*/

	/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */
	//Liberation de la mémoire
	free(tab_pts);

	return EXIT_SUCCESS;
}