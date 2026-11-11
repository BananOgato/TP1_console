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

#pragma once

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "tab_points.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS types
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

   // le type de l'elements qui constitura la pile
typedef t_point t_element;

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS STRUCTURES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

typedef struct {
	t_element* items; // l'item de la pile (ex: une assiette)
	int sommet;		  // l'item le plus au dessus de la pile (ex: l'assiette la plus au dessus)
	int max;		  // la taille max de la pile (ex: hauteur max du meuble ou sont les assiettes)
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
/// Permet d'obtenir le nombre d'elements de la pile pile
/// </summary>
/// <param name="pile">la pile a tester</param>
/// <returns>le nombre d'elements de la pile pile</returns>
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
void ajouter_a_pile(t_pile* pile, t_element item);

/// <summary>
/// Pemet de supprimer l'element au sommet de la pile
/// </summary>
/// <param name="pile">la pile ou sera enlevé son sommet</param>
void enlever_a_pile(t_pile* pile);
