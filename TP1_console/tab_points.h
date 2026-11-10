#pragma once

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * MACRO-FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// retourne le carré de x
#define CARRE(x) ((x) * (x))
// retourne valeur absolue de x
#define ABS(x) (x < 0) ? (-x) : (x)

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * CONSTANTES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// PI a la 15em décimal près
#define PI 3.141592653589793
// La taille max du tableau de t_points
#define TAILLE 20

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS Structure
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

typedef struct {
	int posx, posy;	// coordonnées x, y du point dans le plan
	double rad;		// angle polaire relatif au point minimal
	double dist;	// la distance relative au point minimal
	int position;	// position-tableau du point suite au tri
} t_point;

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS DE FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

/// <summary>
/// Permet de faire le produit vectoriel de v(p_ref pa) X v(p_ref pB)
// </summary>
/// <param name="p_ref"></param>
/// <param name="pA"></param>
/// <param name="pB"></param>
/// <returns>v(p_ref pa) X v(p_ref pB)</returns>
double prod_vectoriel(t_point* p_ref, t_point* pA, t_point* pB);

/// <summary>
/// Permet de trouver la distance entre un point A et un point B
/// </summary>
/// <param name="pA">pointeur du point A</param>
/// <param name="pB">pointeur du point B</param>
/// <returns>la distacne entre A et B</returns>
double distance(t_point* pA, t_point* pB);

/// <summary>
/// Permet de generer un nombre aleatoire en MIN et MAX
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns>un nombre aleatoire en MIN et MAX</returns>
int alea(int min, int max);

/// <summary>
/// permet de trouver l'angle polaire du point B par rapport a un point d'origine A
/// </summary>
/// <param name="pA">le point d'origine</param>
/// <param name="pB">le point a tester l'angle</param>
/// <param name="h_ref">la verticale au point A</param>
/// <returns>l'angle polaire de B par raport a A</returns>
double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref);

/// <summary>
/// permet de trouver le point le plus en bas a droite du tableau de point
/// </summary>
/// <param name="tab_pts">le tableau contenant les points</param>
/// <param name="taille">la taille du tableau</param>
/// <returns>l'index du point minimal dans le tableau</returns>
int trouver_pt_minimal(const t_point tab_pts[], int taille);

/// <summary>
/// Permet d'echanger 2 elements a et b dans un tableau
/// </summary>
/// <param name="tab_pts">la tebleau dans le quel les points serons echangé</param>
/// <param name="a"></param>
/// <param name="b"></param>
void swap(t_point tab_pts[], int a, int b);

/// <summary>
/// pemet de placé la verticale au point minimal du tableau
/// </summary>
/// <param name="tab_pts">le tableau de réference</param>
/// <param name="pos_min">la position du point minimal</param>
/// <returns>le point de la verticale du point minimal du tableau</returns>
t_point placer_pt_reference(t_point tab_pts[], int pos_min);

/// <summary>
/// Permet de placer des points aléatoirement dans un tableau de t_point
/// </summary>
/// <param name="tab_pts">la tableau dans lequel sera placé les points</param>
/// <param name="taille">la taille du tableau</param>
/// <param name="maxx">l'intervale [0, maxx] dans lequel sera generer les point en X</param>
/// <param name="maxy">l'intervale [0, maxy] dans lequel sera generer les point en Y</param>
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);

/// <summary>
/// Permet de trier les points par angle par rapport au point 0 de tab_pts
/// </summary>
/// <param name="tab_pts">ta tableau a trier</param>
/// <param name="taille">la taille du tableau</param>
void trier_pts(t_point tab_pts[], int taille);

/// <summary>
/// permet de definir a chaque t_point leurs rad et leurs ditance en fonction du point de reference
/// dasn un tableau de t_point
/// </summary>
/// <param name="tab_pts">le tableau de t_point</param>
/// <param name="taille">taille du tableau</param>
/// <param name="ref">le point de reference h_ref (la verticale au point tab_pts[0])</param>
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref);
