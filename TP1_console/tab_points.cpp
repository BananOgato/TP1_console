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
 * Cette fonction calcule la distance eucledienne de deux points.
 * 
 * Paramètres: 
 *  -pA: Le premier point A (type: t_point*)
 *  -pB: Le deuxième point B (type: t_point*)
 * Valeur de retour: La distance entre pA et pB (type: double)
 * ======== ========== ========== ========== ========== ========== ========== ========== */

double distance(t_point* pA, t_point* pB) {
	return sqrt(CARRE(pA->posx - pB->posx) + CARRE(pA->posy - pB->posy));
}

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * PROD_VECTORIEL
 * Codé par Paul
 * Cette fonction calcule le produit vectoriel de deux vecteurs formés par 
 * 3 points (h_ref, pA, pB)
 *
 * Paramètres:
 *  -p_ref: Le point de référence (type: t_point*)
 *  -pA: Le premier point A (type: t_point*)
 *  -pB: Le deuxième point B (type: t_point*)
 * Valeur de retour: Le résultat du produit vectoriel (type: double)
 * ======== ========== ========== ========== ========== ========== ========== ========== */
double prod_vectoriel(t_point* p_ref, t_point* pA, t_point* pB) {
	return (pA->posx - p_ref->posx) * (pB->posy - p_ref->posy)
		- (pA->posy - p_ref->posy) * (pB->posx - p_ref->posx);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * COORD_POLAIRE
 * Codé par Paul
 * Cette fonction calcule l'angle polaire d'un point par rapport a une origine
 *
 * Paramètres:
 *  -pA: Le point de départ (type: t_point*)
 *  -pB: Le point d'arriver (type: t_point*)
 *  -p_ref: Le point de référence (type: t_point*)
 * 
 * Valeur de retour: L'angle polaire en radians (type: double)
 * ======== ========== ========== ========== ========== ========== ========== ========== */
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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * ALEA
 * Codé par Briana
 * Cette fonction renvoie un nombre entier aléatoire dans l'intervalle [min, max].
 *
 * Paramètres:
 *  -min: La borne inférieur de l'intervalle (type: int)
 *  -max: La borne supérieur de l'intervalle (type: int)
 *
 * Valeur de retour: Entier aléatoire inclue dans l'intervalle [min, max] (type: int)
 * ======== ========== ========== ========== ========== ========== ========== ========== */
int alea(int min, int max) {	// retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * INIT_TAB_ALEA
 * Codé par Briana
 * Cette fonction initialise un tableau de points avec des coordonées (x,y) aléatoires
 *
 * Paramètres:
 *  -tab_pts: Le tableau de point à initialiser (type: t_point*)
 *  -taille: Le nombre de points dans le tableau (type: int)
 *  -maxx: La valeur maximale pour la coordonnée en x (type: int)
 *  -maxy: La valeur maximale pour la coordonnée en y (type: int)
 *
 * Valeur de retour: Aucune
 * ======== ========== ========== ========== ========== ========== ========== ========== */
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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * TROUVER_PT_MINIMAL
 * Codé par Paul
 * Cette fonction trouve l'indice du point le plus en bas dans le tableau de points
 * 
 * Paramètres:
 *  -tab_pts: Le tableau de point à analyser (type: const t_point[])
 *  -taille: Le nombre de points dans le tableau (type: int)
 *
 * Valeur de retour: L'indice du point minimal dans le tableau (type: int)
 * ======== ========== ========== ========== ========== ========== ========== ========== */
// on retiens dans tab_index la position du tableau
// en parcours toutes les cases du tableau et on retiens la position si
//	 la position Y de la case pos est plus petite que tab_index
//	 OU SI la position Y est egale ET que la position X est plus petite
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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * SWAP
 * Codé par Briana
 * Cette fonction permute deux points d'un tableau
 *
 * Paramètres:
 *  -tab_pts: Le tableau de point ayant les points (type: t_point[])
 *  -a: L'indice du premier point à échanger (type: int)
 *  -b: L'indice du deuxième point à échanger (type: int)
 *
 * Valeur de retour: Aucune
 * ======== ========== ========== ========== ========== ========== ========== ========== */
void swap(t_point tab_pts[], int a, int b) {
	t_point temp = tab_pts[a]; /*Temporaire pour variable a*/
	/*Permutation des variables*/
	tab_pts[a] = tab_pts[b];
	tab_pts[b] = temp;
}

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * PLACER_PT_REFERENCE
 * Codé par Briana
 * Cette fonction crée le point de référence horizontale qui sert au calcul
 * des angles polaires
 *
 * Paramètres:
 *  -tab_pts: Le tableau de point ayant les points (type: t_point[])
 *  -pos_min: L'indice du point minimal dans le tableau (type: int)
 *
 * Valeur de retour: Le point de référence horizontale crée (type: t_point)
 * ======== ========== ========== ========== ========== ========== ========== ========== */
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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * TRIER_PTS
 * Codé par Briana
 * Cette fonction trie les points du tableau par ordre croissant de leurs
 * angles polaire en utilisant le tri par sélection.
 *
 * Paramètres:
 *  -tab_pts: Le tableau de point à trier (type: t_point[])
 *  -taille: Le nombre de points dans le tableau (type: int)
 *
 * Valeur de retour: Aucune
 * ======== ========== ========== ========== ========== ========== ========== ========== */
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

/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * CALCUL_COORD_POLAIRES
 * Codé par Paul
 * Cette fonction calcul l'angle polaire et la distance par rapport au point
 * de référence.
 *
 * Paramètres:
 *  -tab_pts: Le tableau de point (type: t_point[])
 *  -taille: Le nombre de points dans le tableau (type: int)
 *  -ref: Le point de référence horizontale (type: t_point*)
 *
 * Valeur de retour: Aucune
 * ======== ========== ========== ========== ========== ========== ========== ========== */
// Pour tout les point i du tableau
//	 Ajouter dans la composante rad du point: la coordonnée polaire du point i en fonction du point 0
//	 Ajouter dans la composante dist du point: la distance entre le point i et le point 0
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref) {
	for (int i = 1; i < taille; i++) {
		tab_pts[i].rad = coord_polaire(&tab_pts[0], &tab_pts[i], ref);
		tab_pts[i].dist = distance(&tab_pts[0], &tab_pts[i]);
	}
}