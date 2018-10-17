/* Debut de ce "fantastique" projet pour faire un jeu d'echec
avec affichage sur le terminal*/


/* Mettre tout les #include pour les headers ici*/

#include "initJeu.h"


/* Fonction main*/

int main() {
    /* Initialisation des variables*/

    /* Traitement*/
    Case terrain [TAILLETERRAIN][TAILLETERRAIN];
    Joueur* joueur1;
    joueur1 = initJoueur("joueur1", 1);  // creation du joueur1
    Joueur* joueur2;
    joueur2 = initJoueur("joueur2", 0);  // creation du joueur2
    initJeu(terrain, joueur1, joueur2);  // initialisition du terrain
    /* verification du terrain*/
    affichageMenu();
    printf("creation du plateau de jeu fini...\nC'est parti pour un petit test.\n");
    int x = 0;
    int y = 0;
    printf("\n\ncouleur de la case x, y. \n  x : ");
    scanf("%d", &x);
    printf("  y : ");
    scanf("%d", &y);
    printf("couleur de la case : %d", terrain[x][y].couleur);

    return 0;
}

