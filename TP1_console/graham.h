/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : LABRE Paul
 * Date : 3 nov 2026
 *
 * ce fichier gere la gestion de l'algo pour Graham
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#pragma once

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "tab_points.h"
#include "tab_pile.h"
#include "affichage.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * CONSTANTE
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// definis le temps de delais les dessins de trait
#define DELAIS_ECRANS 300

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS DE FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

/// <summary>
/// cette fonction sert a executer et afficher l'algorithme de graham
/// </summary>
/// <param name="tab_pts">la tableau de point sur laquel sera tester l'algorithme</param>
/// <param name="nb_pts">le nombre de point du tableau</param>
/// <param name="pile_Graham">la pile qui servira a l'algo de graham</param>
/// <param name="affichage">1 : affichage activé | 0 : affichage désactivé</param>
/// <returns></returns>
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int affichage);
