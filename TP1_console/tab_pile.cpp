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
		printf("Erreur d'allocation de memoire.\n");
		pile.sommet = -1;
		return pile;
	}
	pile.sommet = -1;
	
	return pile;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void liberer_pile(t_pile* pile) {
	free(pile);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int get_sommet(const t_pile* pile, t_element* element) {
	if (pile->sommet < 0)
		return 0;

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
		printf("ERREUR la pile est pleine");
		return;
	}

	pile->sommet++;
	pile->items[pile->sommet] = element;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void pop(t_pile* pile) {
	if (vide(pile)) {
		printf("ERREUR la pile est vide");
		return;
	}

	pile->sommet--;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

/*void display(t_pile* pile, int taille) {
	for (int i = 0; i < taille; i++) {
		printf("");
	}
}*/