/* Jeu.c
contient les fonctions pour animer une partie*/

#include "initJeu.h"

Joueur* partieDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2) {
    /* fonction principale pour le jeux a 2 joueurs*/
    Joueur* gagnant = NULL;

    affichageTerrain(terrain);

    /* calcul des positions pour le joueur 1*/
    calculMouvement(joueur1->listePiece, terrain);
    gestionSurbrillance(terrain, joueur1->listePiece[4]->mouvementPossible);  // test, on affiche le deplacement potentiel du roi
    calculMouvement(joueur2->listePiece, terrain);

    affichageTerrain(terrain);
    printf("affichage des deplacement possible du roi\n");
    return gagnant;
}


void affichageTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	/* affichage experimental du terrain
	 * on met en place TAILLETERRAIN-1 - y pour que le point de coordonné 0,0 soit en bas a gauche
	 */
    for (int i = 0; i < 10; i++) {  // on fait un peu d'espace pour l'affichage
        printf("\n");
    }
    /* affichage du terrain*/
    for (int y = 0; y<TAILLETERRAIN; y++) {
        for (int x = 0; x<TAILLETERRAIN; x++) {
            if (terrain[x][TAILLETERRAIN-1 - y].contenu == NULL) {  // s'il n'y a pas de piece sur cette case
            	if (terrain[x][TAILLETERRAIN-1 - y].surbrillance == 0) {  // dans le cas ou il n'y a pas de subrillance
	                if (terrain[x][TAILLETERRAIN-1 - y].couleur == 0) printf("   ");  // case noire
	                else if (terrain[x][TAILLETERRAIN-1 - y].couleur == 1) printf(" - ");  // case blanche
	            }
	            else printf(" * ");  // affichage de la surbrillance
            }
            else {
                printf(" %c ", terrain[x][TAILLETERRAIN-1 - y].contenu->type);  // affiche le type de la piece
            }
        }
        printf("\n");
    }
}


void gestionSurbrillance(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Element* liste){
	/*Initialisation, on nettoie toutes les cases du terrain*/
	for (int x = 0; x < TAILLETERRAIN; x++) {  // on parcours le terrain
		for (int y = 0; y < TAILLETERRAIN; y++) {
			if (terrain[x][y].surbrillance == 1) {
				terrain[x][y].surbrillance = 0;  // si le terrain est en surbrillance, on efface ce comportement
			}
		}
	}
	if (liste != NULL) {  // On fait attention au cas ou la liste est vide
		Element* curseur = liste;
		while (curseur != NULL) {  // on parcours la liste
			terrain[curseur->posX][curseur->posY].surbrillance = 1;  // on met la case choisie en surbrillance
			curseur = curseur->suivant;
		}
	}
}

void scanDeuxJoueurs(Joueur joueurActuel, int commande[2][2]) {
	/* initialisation des cases du tableau commandes */
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			commande[i][j] = 0;
		}
	}

	/* Interraction 1 avec le joueur
	 * Demande de la piece a bouger
	 */

}
