/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * Par : MUCCIARONE Briana et LABRE Paul
 * Date : 28 oct 2026
 *
 * Cette libraries permet de gerer les types t_point. 
 * On y retrouve les fonctions suivantes:
 * - distance: Cette fonction calcule la distance entre deux points
 * - prod_vectoriel: Cette fonction calcule le produit vectoriel de deux vecteurs.
 * - coord_polaire: Cette fonction retourne l'angle polaire d'un point.
 *					par rapport à l'origine.
 * - alea: Cette fonction retourne un entier aléatoire.
 * - init_tab_alea: Cette fonction initialise un tableau avec des points aléatoires.
 * - trouver_pt_minimal: Cette fonction trouve l'indice du point minimal.
 * - swap: Cette fonction permute deux point d'un tableau.
 * - placer_pt_reference: Cette fonction place le point minimal et crée la référence 
 *						  horizontale.
 * - trier_pts: Cette fonction trie les points en ordre croissant selon leurs
 *				angles polaires.
 * - calcul_coord_polaires: Cette fonction calcule les radians et  les distances 
 *							pour tous les points.
 * ======== ========== ========== ========== ========== ========== ========== ========== */

#include "tab_points.h"

 /* ======== ========== ========== ========== ========== ========== ========== ========== */
 /*										FONCTIONS										  */
 /* ======== ========== ========== ========== ========== ========== ========== ========== */

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * DISTANCE 
 * Codé par Paul
 * Cette fonction fais la racine carré de la somme des difference X et Y 
 * au carré (la norme du vecteur AB).
 * 
 * Paramètres: 
 *  -pA: point A
 *  -pB: point B
 * Valeur de retour: 
 
 * ======== ========== ========== ========== ========== ========== ========== ========== */

double distance(t_point* pA, t_point* pB) {
	return sqrt(CARRE(pA->posx - pB->posx) + CARRE(pA->posy - pB->posy));
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// PROD_VECTORIEL : (Par Paul)
//   le produit vectoriel ~ AxB
//   (Ax - Rx) * (By - Ry)  -  (Ay - Ry) * (Bx - Rx) 
double prod_vectoriel(t_point* p_ref, t_point* pA, t_point* pB) {
	return (pA->posx - p_ref->posx) * (pB->posy - p_ref->posy)
		- (pA->posy - p_ref->posy) * (pB->posx - p_ref->posx);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// COORD_POLAIRE : (Par Paul)
// SI xB > xA
//	 retourner l'angle grace a l'arcsin
// SINON
//   retourner PI - l'angle grace a l'arcsin
//
// cette condition sert a savoir si l'angle est ± grand que 90° car le sinus est le meme a x et -x
double coord_polaire(t_point* pA, t_point* pB, t_point* h_ref) {
	return (prod_vectoriel(h_ref, pA, pB) > 0) ?
		asin((pB->posy - pA->posy) / distance(pA, pB)) :
		(PI - asin((pB->posy - pA->posy) / distance(pA, pB)));
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// (par Briana)
int alea(int min, int max) {	// retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// (par Briana)
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

// TROUVER_PT_MINIMAL : (Par Paul)
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

// (par Briana)
void swap(t_point tab_pts[], int a, int b) {
	t_point temp = tab_pts[a]; /*Temporaire pour variable a*/
	/*Permutation des variables*/
	tab_pts[a] = tab_pts[b];
	tab_pts[b] = temp;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// (par Briana)
t_point placer_pt_reference(t_point tab_pts[], int pos_min) {
	/*
	pos_min = trouver_pt_minimal(tab_pts, TAILLE);	Indice du point minimal*/
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

// (par Briana)
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

// CALCUL_COORD_POLAIRES : (Par Paul)
// Pour tout les point i du tableau
//	 Ajouter dans la composante rad du point: la coordonnée polaire du point i en fonction du point 0
//	 Ajouter dans la composante dist du point: la distance entre le point i et le point 0
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref) {
	for (int i = 1; i < taille; i++) {
		tab_pts[i].rad = coord_polaire(&tab_pts[0], &tab_pts[i], ref);
		tab_pts[i].dist = distance(&tab_pts[0], &tab_pts[i]);
	}
}