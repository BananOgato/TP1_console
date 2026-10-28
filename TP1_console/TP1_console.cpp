/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBRARIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */
// test
#define _CRT_SECURE_NO_WARNINGS
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
#define PI 3,141592653589793
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

double distance(t_point* pA, t_point* pB);

int alea(int min, int max);

double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref);

int trouver_pt_minimal(const t_point tab_pts[], int taille);

void swap(t_point tab_pts[], int a, int b);

t_point placer_pt_reference(t_point tab_pts[], int pos_min);

void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);

void trier_pts(t_point tab_pts[], int taille);

void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref);

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * MAIN
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */


int main() {
	//Variables
	t_point tab_pts[TAILLE], h_ref;
	int pos_pt_min;

	/*initialise le générateur “rand()” */
	srand(time(NULL));
	/*Initialise tableau avec des points aléatoires*/
	alea(0, TAILLE);

	init_tab_alea(tab_pts, TAILLE, 1400, 800);



	pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);
	/*Permutation pour obtenir le h_ref*/
	h_ref = placer_pt_reference(tab_pts, pos_pt_min);

	/*Calcul et tri des angles polaires*/
	calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
	trier_pts(tab_pts, TAILLE);

	for (int i = 0; i < TAILLE; i++) {
		printf("%d ; %d ; dist: %lf ; angle %lf\n", tab_pts[i].posx, tab_pts[i].posy, (i) ? tab_pts[i].dist : 0, (i) ? tab_pts[i].rad : 0);
	}
	
	return EXIT_SUCCESS;
}


/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * FONCTIONS
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */


/// <summary>
/// 
/// </summary>
/// <param name="pA"></param>
/// <param name="pB"></param>
/// <returns></returns>
double distance(t_point* pA, t_point* pB) {
	return sqrt(CARRE(pA->posx - pB->posx) + CARRE(pA->posy - pB->posy));
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

double prod_vectoriel(t_point* p_ref, t_point* p1, t_point* p2) {
	return (p1->posx - p_ref->posx) * (p2->posy - p_ref->posy)
		   - (p1->posy - p_ref->posy) * (p2->posx - p_ref->posx);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// COORD_POLAIRE :
// SI xB > xA
//	 alors retourner l'angle grace a l'arcsin
//   sinon retourner l'angle grace a l'arcsin avec pi/2 
//
// cette condition sert a savoir si l'angle est ± grand que 90° car le sinus est le meme a x et -x
double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref) { // QUESTION AU PROFF CAR PAS CLAIR
	return (prod_vectoriel(h_ref, pA, pB) > 0) ?
		asin((pB->posy - pA->posy) / distance(pA, pB)) :
		asin((pB->posy - pA->posy) / distance(pA, pB)) + (PI / 2);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int alea(int min, int max) {	// retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {
	//randomize les points dans le tableau pour les x
	for (int i = 0;i < taille;i++) {
		tab_pts[i].posx = alea(1, maxx);		 /*Assignation aléatoire de x*/
		int memey;								/*Vérifier si deux y sont égaux*/
		do {
			tab_pts[i].posy = alea(1, maxy);				/*Assignation aléatoire de y*/
			memey = 1;
			/*Boucle de vérification pour la condition sur le posy*/
			for (int j = 0; j < i;j++) {
				if (tab_pts[i].posy == tab_pts[j].posy) {
					memey = 0;
					break;

				}
			}
		} while (!memey);	/* Exécute tant qu'y n'a pas de doublon*/
	}
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// TROUVER_PT_MINIMAL :
// on retiens dans tab_index la position du tableau
// en parcours toutes les cases du tableau et on retiens la position si
//	 la position Y de la case pos est plus petite que tab_index
//	 OU SI la position Y est egale ET que la position X est plus petite
// 
// Retourne tab_index
int trouver_pt_minimal(const t_point tab_pts[], int taille) {
	// l'indice du point le plus en bas a droite du graphique
	int tab_index = 0;

	for (int pos = 1; pos < taille; pos++) {
		if ((tab_pts[pos].posy < tab_pts[tab_index].posy) ||
		   (tab_pts[pos].posy == tab_pts[tab_index].posy &&
			tab_pts[pos].posx < tab_pts[tab_index].posx))
			tab_index = pos;
	}

	return tab_index;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void swap(t_point tab_pts[], int a, int b) {
	t_point temp = tab_pts[a]; /*Temporaire pour variable a*/
	/*Permutation des variables*/
	tab_pts[a] = tab_pts[b];
	tab_pts[b] = temp;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

t_point placer_pt_reference(t_point tab_pts[], int pos_min) {
	pos_min = trouver_pt_minimal(tab_pts, TAILLE);	/*Indice du point minimal*/
	/*Permutation point minimal et point case 0*/
	swap(tab_pts, 0, pos_min);
	/*Nouveau point de référence horizontale*/
	t_point pt_ref;
	pt_ref.posx = tab_pts[0].posx;
	pt_ref.posy = 800;

	/*Retourne le point de référence*/
	return pt_ref;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void trier_pts(t_point tab_pts[], int taille) {
	/*Triage des points par sélection*/
	for (int i = 1;i < taille - 1;i++) {		//Point min reste dans tab_pts[0]
		int min = i;	//plus petit élément

		for (int j = i + 1;j < taille;j++) {
			if (tab_pts[j].rad < tab_pts[min].rad)
				min = j;
			/*Si les angles sont égaux*/
			else if (tab_pts[j].rad == tab_pts[min].rad) {
				if (tab_pts[j].dist < tab_pts[min].dist)
					min = j;
			}
		}
		/*Changement du plus petit élément*/
		if (min != i)
			swap(tab_pts, min, i);
	}
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref) {
	for (int i = 1; i < taille; i++) {
		tab_pts[i].rad = coord_polaire(&tab_pts[0], &tab_pts[i], ref);
		tab_pts[i].dist = distance(&tab_pts[0], &tab_pts[i]);
	}
}