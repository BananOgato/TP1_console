#pragma once

#define _CRT_SECURE_NO_WARNINGS

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include "tab_points.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== */
/*                              PROTOTYPES DES FONCTIONS								 */
/* ======== ========== ========== ========== ========== ========== ========== ========== */

int demander_mode(void); 
FILE* choisir_fichier(void);
t_point* lire_points(FILE* fichier, int* nb_pts);
/* ======== ========== ========== ========== ========== ========== ========== ========== */

int demander_mode(void); 
FILE* choisir_fichier(void);
t_point* lire_points(FILE* fichier, int* nb_pts);
