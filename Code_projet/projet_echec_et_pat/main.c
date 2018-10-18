/* Debut de ce "fantastique" projet pour faire un jeu d'echec
avec affichage sur le terminal*/


/* Mettre tout les #include pour les headers ici*/

#include "initJeu.h"


/* Fonction main*/

int main() {
    /* Initialisation des variables*/

    /* Affichage du message d'accueil*/
    printf("Bienvenu sur \"echec simulateur 2018\"\n\n");

    /* lancement du jeu*/
    Case terrain [TAILLETERRAIN][TAILLETERRAIN];
    Joueur* joueur1;
    joueur1 = initJoueur("joueur1", 1);  // creation du joueur1
    Joueur* joueur2;
    joueur2 = initJoueur("joueur2", 0);  // creation du joueur2
    initJeu(terrain, joueur1, joueur2);  // initialisition du terrain

    /* test du menu*/
    affichageMenu();

    /* test des pions*/
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            if (terrain[j][7-i].contenu == NULL) {
                printf("   ");
            }
            else {
                printf(" %c ", terrain[j][7-i].contenu->type);
            }
        }
        printf("\n");
    }
    return 0;
}
