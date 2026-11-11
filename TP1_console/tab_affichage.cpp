/* ======== ========== ========== ========== ========== ========== ========== ========== ======== /
 * Par : LABRE Paul
 * Date : 3 nov 2026
 *
 * ce fichier gere l'affichage pour les points
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include "tab_affichage.h"

 // AFFICHER_PTS_EN_ORDRE
 // Pour tout les points i du tableau
 //	 Enregistrer dans la composante position du point: sa position i dans le tableau (apres le tri)
 //	 Dessiner le point a l'ecran avec son numero i
void afficher_pts_en_ordre(t_point tab_pts[], int taille) {
	for (int i = 0; i < taille; i++) {
		tab_pts[i].position = i;
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
	}
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// AFFICHER_LIGNE_VERS_0
// Pour tout les points i du tableau
//	 Dessiner une ligne entre le point minimal (case 0) et le point i

void afficher_ligne_vers_0(t_point tab_pts[], int taille) {
	for (int i = 0; i < taille; i++)
		dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[i].posx, tab_pts[i].posy);
}

/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */

// EFFACER_LIGNE_VERS_0
// Pour tout les points i du tableau
//	 Effacer la ligne entre le point minimal (case 0) et le point i
void effacer_ligne_vers_0(t_point tab_pts[], int taille) {
	for (int i = 0; i < taille; i++)
		effacer_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[i].posx, tab_pts[i].posy);
}