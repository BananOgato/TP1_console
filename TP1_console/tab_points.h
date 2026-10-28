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

#define CARRE(x) ((x) * (x))
#define ABS(x) (x < 0) ? (-x) : (x)

 /* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
  * CONSTANTES
  * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

  // PI a la 15em décimal près
#define PI 3.141592653589793
#define TAILLE 20

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * DEFINITIONS Structure Global
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
 /// Permet de faire le produit vectoriel P1xP2 par rapport au point P_ref
 /// </summary>
 /// <param name="p0">Le point d'origine</param>
 /// <param name="p1">Le point A</param>
 /// <param name="p2">Le point B</param>
 /// <returns></returns>
double prod_vectoriel(t_point* p0, t_point* p1, t_point* p2);

/// <summary>
/// 
/// </summary>
/// <param name="pA"></param>
/// <param name="pB"></param>
/// <returns></returns>
double distance(t_point* pA, t_point* pB);

int alea(int min, int max);

double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref);

int trouver_pt_minimal(const t_point tab_pts[], int taille);

void swap(t_point tab_pts[], int a, int b);

t_point placer_pt_reference(t_point tab_pts[], int pos_min);

void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);

void trier_pts(t_point tab_pts[], int taille);

void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref);