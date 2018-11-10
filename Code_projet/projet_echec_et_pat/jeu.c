/* Jeu.c
contient les fonctions pour animer une partie*/

#include "initJeu.h"

Joueur* partieDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2) {
    /* fonction principale pour le jeux a 2 joueurs*/
    Joueur* gagnant = NULL;

    /* affichage experimental du terrain*/
    for (int i = 0; i<TAILLETERRAIN; i++) {
        for (int j = 0; j<TAILLETERRAIN; j++) {
            if (terrain[j][TAILLETERRAIN -1 -i].contenu == NULL) {
                if (terrain[j][TAILLETERRAIN -1 -i].couleur == 0) printf("   ");
                else if (terrain[j][TAILLETERRAIN -1 -i].couleur == 1) printf(" - ");
                else printf(" $ ");
            }
            else {
                printf(" %c ", terrain[j][TAILLETERRAIN -1 -i].contenu->type);
            }
        }
        printf("\n");
    }

    /* calcul des positions pour le joueur 1*/
    calculMouvement(joueur1->listePiece, terrain);
    return gagnant;
}
