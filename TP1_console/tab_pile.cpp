#include "tab_pile.h"
#include <stdlib.h>

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

t_pile init_pile(int taille) {
	// futur pile qui sera retournée
	t_pile pile;

	// allocation de la mémoire avec malloc
	pile.items = (t_element*)malloc(taille * sizeof(t_element));
	
	// détection d'erreur d'allocation de memoire.
	if (pile.items == NULL) {
		printf("Erreur d'allocation de memoire\n");
		pile.sommet = -1;
		return pile;
	}
	pile.max = taille;
	pile.sommet = -1;
	return pile;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void liberer_pile(t_pile* pile) {
	free(pile->items);
	pile->items = NULL;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int get_sommet(const t_pile* pile, t_element* element) {
	if (vide(pile)) {
		printf("ERREUR la pile est vide");
		return 0;
	}

	*element = pile->items[pile->sommet];

	return 1;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int get_suiv_sommet(const t_pile* pile, t_element* element) {
	if ((pile->sommet - 1) < 0)
		return 0;

	*element = pile->items[pile->sommet - 1];

	return 1;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void push(t_pile* pile, t_element element) {
	if (pleine(pile)) {
		printf("ERREUR la pile est pleine\n");
		return;
	}

	pile->sommet++;
	pile->items[pile->sommet] = element;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void pop(t_pile* pile) {
	if (vide(pile)) {
		printf("ERREUR la pile est vide\n");
		return;
	}

	pile->sommet--;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int get_pile_size(const t_pile* pile) {
	return pile->max;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int pleine(const t_pile* pile) {
	if (pile->sommet >= pile->max - 1)
		return 1;
	return 0;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int vide(const t_pile* pile) {
	if (pile->sommet < 0)
		return 1;
	return 0;
}