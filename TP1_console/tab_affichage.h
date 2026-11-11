/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : LABRE Paul
 * Date : 3 nov 2026
 *
 * ce fichier gere l'affichage pour les points 
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#pragma once

#include "WINBGIM.h"
#include "affichage.h"
#include "tab_points.h"

/// <summary>
/// permet d'afficher les points en les numérotant de 0 à taille-1
/// </summary>
/// <param name="tab_pts"></param>
/// <param name="taille"></param>
void afficher_pts_en_ordre(t_point tab_pts[], int taille);

/// <summary>
/// permet d'afficher une ligne vers le point 0
/// </summary>
/// <param name="tab_pts"></param>
/// <param name="taille"></param>
void afficher_ligne_vers_0(t_point tab_pts[], int taille);

/// <summary>
/// permet d'effacer la ligne vers le point 0
/// </summary>
/// <param name="tab_pts"></param>
/// <param name="taille"></param>
void effacer_ligne_vers_0(t_point tab_pts[], int taille);
