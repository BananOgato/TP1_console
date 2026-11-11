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
#define DELAIS_ECRANS 50
// nombre de simulations par moyenne
#define NB_TESTS		10000	
// nombre de points minimal de la simulation
#define NB_PTS_MIN		5		
// nombre de points maximal de la simulation
#define NB_PTS_MAX		200		
// pas entre chaque nombre de points
#define NB_PTS_PAS		5		

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

/// <summary>
/// Permet d'effectuer nb_tests parcours de Graham sur nb_pts points aleatoires,
/// sans affichage graphique, et de calculer la moyenne de points de l'enveloppe
/// </summary>
/// <param name="nb_pts">le nombre de points aleatoires generes a chaque test</param>
/// <param name="nb_tests">le nombre de parcours de Graham a effectuer</param>
/// <returns>la moyenne du nombre de points de l'enveloppe convexe</returns>
double simulation_moyenne(int nb_pts, int nb_tests);
