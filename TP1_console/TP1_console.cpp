/* ======== ========== ========== ========== ========== ========== ========== ========== *
 * Par : MUCCIARONE Briana et LABRE Paul
 * Date : 10 nov 2026
 *
 * ce programme permet de jouer avec l'algorithme de graham
 * il possede 3 modes:
 * - Appliquer l'algorithme a 20 point repartis aleatoirement
 * - Appliquer l'algorithme a un fichier de point predefinis
 * - Faire la moyenne sur un nombre de points de l’enveloppe
 *
 * Le github associer: https://github.com/BananOgato/TP1_console
 * ======== ========== ========== ========== ========== ========== ========== ========== */

#define _CRT_SECURE_NO_WARNINGS

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * LIBARAIES
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tab_points.h"
#include "tab_pile.h"
#include "tab_affichage.h"
#include "graham.h"
#include "interactions.h"

/* ======== ========== ========== ========== ========== ========== ========== ========== =======  /
 * MAIN
 * ======== ========== ========== ========== ========== ========== ========== ========== ======= */

int main() {
	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// INITIALISATION

	// Tableau dynamique contenant les points à traiter
	t_point* tab_pts = NULL;
	// Point de référence horizontal utilisé pour calculer les angles
	t_point h_ref;
	// Position du point minimal dans le tableau
	int pos_pt_min;
	// Mode d'exécution choisi par l'utilisateur
	int mode = 0;
	// Nombre de points chargés ou générés
	int nb_pts = 0;
	// Fichier contenant les points lorsque le mode fichier est utilisé
	FILE* fichier = NULL;

	// initialise le générateur "rand()"
	srand((unsigned int)time(NULL));

	// Demande du mode à l'utilisateur
	mode = demander_mode();

	switch (mode) {
	case 1: // Pour le mode aléatoire
		nb_pts = TAILLE;
		// Allocation dynamique avec malloc
		tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
		// Validation de l'allocation
		assert(tab_pts != NULL);
		init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);
		break;

	case 2: // Pour le mode fichier
		fichier = choisir_fichier();
		tab_pts = lire_points(fichier, &nb_pts);
		break;

	case 3: 
		// Fichier dans lequel les moyennes des simulations seront enregistrées
		FILE* log = fopen("moyennes.txt", "w");
		if (log == NULL) {
			printf("Erreur: creation du fichier-log impossible\n");
			return EXIT_FAILURE;
		}

		printf("Simulation en cours | %d tests par moyenne :\n", NB_TESTS);
		// Nombre de points utilisé pour la série de simulations courante.
		for (int n = NB_PTS_MIN; n <= NB_PTS_MAX; n += NB_PTS_PAS) {
			// Moyenne du nombre de sommets de l'enveloppe convexe.
			double moyenne = simulation_moyenne(n, NB_TESTS);
			fprintf(log, "%d\t%f\n", n, moyenne);
			printf("%d points -> moyenne : %.2f\n", n, moyenne);
		}

		fclose(log);
		printf("Fichier %s genere.\n", "moyennes.txt");

		// Pas de partie graphique pour ce mode
		return EXIT_SUCCESS;
	}

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// TRIE DES POINTS

	pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);
	// Permutation pour obtenir le h_ref
	h_ref = placer_pt_reference(tab_pts, pos_pt_min);
	// Calcul et tri des angles polaires
	calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
	trier_pts(tab_pts, nb_pts);

	// affichage des points
	mode_graphique();
	afficher_pts_en_ordre(tab_pts, nb_pts);
	afficher_ligne_vers_0(tab_pts, nb_pts);
	pause_ecran();
	effacer_ligne_vers_0(tab_pts, nb_pts);

	/* ==== ========== ========== ========== ========== ========== ========== ========== ======= */
	// ALGO GRAHAM

	// Pile contenant l'enveloppe calculée par Graham
	t_pile pile;

	// algoritme graham (avec affichage)
	algo_Graham_scan(tab_pts, nb_pts, &pile, 1);

	// Fermeture de la fenêtre graphique
	nettoyer_ecran();
	fermer_mode_graph();

	/* ======== ========== ========== ========== ========== ========== ========== ========== ======= */
	// LIBERATION MEMOIRE | FIN

	liberer_pile(&pile);
	free(tab_pts);

	return EXIT_SUCCESS;
}