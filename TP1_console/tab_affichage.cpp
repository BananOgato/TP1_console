#include "tab_affichage.h"

void afficher_pts_en_ordre(t_point tab_pts[], int taille) {
	for (int i = 0; i < taille; i++) {
		tab_pts[i].position = i;
		dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
		dessiner_lig(tab_pts[0].posx, tab_pts[0].posy ,tab_pts[i].posx, tab_pts[i].posy);
	}
}