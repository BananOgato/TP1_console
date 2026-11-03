#pragma once

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "tab_points.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * CONSTANTES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS types
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

typedef t_point t_element;

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS Structure
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

typedef struct {
	t_element* items;
	int sommet;
	int max;
} t_pile;

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS DE FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

/// <summary>
/// Créer et renvoie une pile de la taille taille
/// </summary>
/// <param name="taille">La taille de la futur pile créer</param>
/// <returns>La pile créer</returns>
t_pile init_pile(int taille);

/// <summary>
/// Permet de liberer l'esapce alloué de la pile mise en arguement
/// </summary>
/// <param name="pile">la pile qui sera supprimé</param>
void liberer_pile(t_pile* pile);

/// <summary>
/// Permet d'obtenir l'element au sommet de la pile pile dans l'element element
/// </summary>
/// <param name="pile">La pile</param>
/// <param name="element">l'element dans lequel sera injecté le sommet de la pile</param>
/// <returns>1 pour succes, 0 pour echec</returns>
int get_sommet(const t_pile* pile, t_element* element);

/// <summary>
/// Permet d'obtenir l'element sous le sommet de la pile pile dans l'element element
/// </summary>
/// <param name="pile">La pile</param>
/// <param name="element">l'element dans lequel sera injecté l'element sous le sommet de la pile</param>
/// <returns>1 pour succes, 0 pour echec</returns>
int get_suiv_sommet(const t_pile* pile, t_element* element);

/// <summary>
/// Permet d'obtenir la taille de la pile pile
/// </summary>
/// <param name="pile">la pile a tester</param>
/// <returns>la taille de la pile</returns>
int get_pile_size(const t_pile* pile);

/// <summary>
/// Permet de vérifier si une pile pile est pleine
/// </summary>
/// <param name="pile"> la pile a tester</param>
/// <returns>0 si elle est n'est pas pleine, 1 si elle est pleine</returns>
int pleine(const t_pile* pile);

/// <summary>
/// Permet de vérifier si une pile pile est vide
/// </summary>
/// <param name="pile">0 si elle est pas vide, 1 si elle est vide</param>
/// <returns></returns>
int vide(const t_pile* pile);

/// <summary>
/// Pemet d'ajouter un nouvel element item au sommet de la pile
/// </summary>
/// <param name="pile">la pile dans lequel sera ajouter l'element</param>
/// <param name="item"> l'element qui sera ajouté a la pile</param>
void push(t_pile* pile, t_element item);

/// <summary>
/// Pemet de supprimer l'element au sommet de la pile
/// </summary>
/// <param name="pile">la pile ou sera enlevé son sommet</param>
void pop(t_pile* pile);

/// <summary>
/// Pemet de supprimer l'element en dessous du sommet de la pile
/// </summary>
/// <param name="pile">la pile ou sera enlevé son sommet</param>
/// void pop_suiv(t_pile* pile);
