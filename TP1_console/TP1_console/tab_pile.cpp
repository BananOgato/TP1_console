/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : LABRE Paul
 * Date : 2 nov 2026
 *
 * Librarie de gestion pour une pile.
 * le nouveau type t_pile qui permet de creer une pile avec init_pile(int taille);
 *
 * les principales fonction sont implementé comme:
 * ajouter_a_pile(t_pile* pile, t_element item);
 * enlever_a_pile(t_pile* pile);
 * liberer_pile(t_pile* pile);
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "tab_pile.h"

 /* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
  * FONCTIONS
  * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

  // INIT_PILE
  // creer une nouvelle pile et y alloue la mémoire en fonction de la taille
  // met le sommet a -1 car la pile est vide
t_pile init_pile(int taille) {
	// futur pile qui sera retournée
	t_pile pile;

	// allocation de la mémoire avec malloc
	pile.items = (t_element*)malloc(taille * sizeof(t_element));
	// détection d'erreur d'allocation de memoire.
	if (pile.items == NULL) {
		printf("Erreur d'allocation de memoire\n");
		taille = NULL;
	}
	pile.max = taille;
	pile.sommet = -1;
	return pile;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// LIBERER_PILE :
// free l'espace alloué de la pile et la met a 0
void liberer_pile(t_pile* pile) {
	free(pile->items);
	pile->items = NULL;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// GET_SOMMET
// si la pile est vide, il n'y a pas de sommet don retourner un erreur
// sinon retourner l'element sommet de la pile
int get_sommet(const t_pile* pile, t_element* element) {
	if (vide(pile)) {
		printf("ERREUR la pile est vide");
		return 0;
	}

	*element = pile->items[pile->sommet];

	return 1;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// GET_SUIV_SOMMET
// si la pile a moin de 2 element retourné une erruer car l'element n'exsite pas
// sinon retourner l'element en dessous du sommet de la pile
int get_suiv_sommet(const t_pile* pile, t_element* element) {
	if ((pile->sommet - 1) < 0)
		return 0;

	*element = pile->items[pile->sommet - 1];

	return 1;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// AJOUTER_A_PILE
// si la pile est plein retourner un erruer
// sinon ajouter un element a la pile ET ajouter un au sommet de la pile
void ajouter_a_pile(t_pile* pile, t_element element) {
	if (pleine(pile)) {
		printf("ERREUR la pile est pleine\n");
		return;
	}

	pile->sommet++;
	pile->items[pile->sommet] = element;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// ENLEVER_A_PILE
// si la pile est vide retourner une erreur
// sinon enlever 1 a sommet
void enlever_a_pile(t_pile* pile) {
	if (vide(pile)) {
		printf("ERREUR la pile est vide\n");
		return;
	}

	pile->sommet--;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// GET_PILE_SIZE -> la taille actuel de la pile (+1 car on compte la pos 0)
int get_pile_size(const t_pile* pile) {
	return pile->sommet + 1;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// PLEINE -> verifie si sommet >= max - 1
int pleine(const t_pile* pile) {
	if (pile->sommet >= pile->max - 1)
		return 1;
	return 0;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// VIDE -> verifie si le sommet < 0
int vide(const t_pile* pile) {
	if (pile->sommet < 0)
		return 1;
	return 0;
}