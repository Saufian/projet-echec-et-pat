/* Debut de ce "fantastique" projet pour faire un jeu d'echec
avec affichage sur le terminal*/


/* Mettre tout les #include pour les headers ici*/

#include "initJeu.h"


/* Fonction main*/

int main() {
    /* Initialisation des variables*/
    char chaine [3] = {"oui"};  // oui ou non, initialisé avec oui

    /* Affichage du message d'accueil*/
    printf("Bienvenu sur \"echec simulateur 2018\"\n\n");
    printf("Voulez commencez une partie ?\n");
    printf("(pas comme si vous étiez venu juste pour cela)\n");
    scanf("%[^\n]", chaine);  // on recupere la chaine de characteres sans l'espace
    printf("\nVous etes de vouloir repondre %s ?\n", chaine);
    printf("De toutes façon, c'est trop tard.");

    /* Traitement*/
    if (strcmp(chaine, "oui") == 0 || strcmp(chaine, "Oui") == 0) {  // on compare la reponse
        /* lancement du jeu*/
        Case terrain [TAILLETERRAIN][TAILLETERRAIN];
        Joueur* joueur1;
        joueur1 = initJoueur("joueur1", 1);  // creation du joueur1
        Joueur* joueur2;
        joueur2 = initJoueur("joueur2", 0);  // creation du joueur2
        initJeu(terrain, joueur1, joueur2);  // initialisition du terrain

        /* verification du terrain*/
        printf("creation du plateau de jeu fini...\nC'est parti pour un petit test.\n");
        int x = 0;
        int y = 0;
        printf("\n\ncouleur de la case x, y. \n  x : ");
        scanf("%d", &x);
        printf("  y : ");
        scanf("%d", &y);
        printf("couleur de la case : %d", terrain[x][y].couleur);
    }
    return 0;
}

