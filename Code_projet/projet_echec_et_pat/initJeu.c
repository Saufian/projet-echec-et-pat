/* initJeu.c
contient les fonctions pour initialyser le terrain, les pieces et les joueurs*/

#include "initJeu.h"

void initJeu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2) {
    /* Le support d'abord*/
    initTerrain(terrain);

    /* on place ensuite les pions*/
}

void initTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {  // initialisation du terrain
    /* initialisation des variables*/
    int couleur;  // depend de la position, 0 pour une case noire, 1 pour une case blanche

    /* process */
    /* on parcours chaque case*/
    for(int x = 0; x<TAILLETERRAIN; x++) {
        for(int y = 0; y<TAILLETERRAIN; y++) {
            couleur = (x+y)%2;  // couleur associe a la case
            terrain[x][y] = initCase(couleur, x+1, y+1);  // on y met une case nouvellement cree
            //on met un +1 pour que les indices des cases correspondent aux coordonnées utilisé dans les jeux d'echecs
        }
    }
}


Case initCase(int couleur, int posX, int posY) {
    Case temp;  // on rempli d'abord temp, avant de le renvoyer.
    temp.couleur = couleur;
    temp.posX = posX;
    temp.posY = posY;
    temp.Contenu = NULL;  // les pieces ne sont pas encore cree, on est nul pour l'instant
    return temp;
}


Joueur* initJoueur(char* nom, int couleur) {
    Joueur* temporaire;
    temporaire = (Joueur*)malloc(sizeof(Joueur));  // on lui donne une taille memoire
    temporaire->nom = nom;  // on affecte les valeurs dans temporaire
    temporaire->couleur = couleur;
    return temporaire;
}


void affichageMenu()
{
    printf("Menu Echec Simulator 2018\n\
        1 - Jouez\n\
        2 - Charger\n\
        3 - Options\n\
        4 - Credit\n\
        5 - Quitter\n");
    int choix = -1;
    while((choix!=1) && (choix!=2) && (choix!=3) && (choix!=4) && (choix!=5))/*Quitte le menu si un choix valide est fait*/
    {
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                /*Lance le jeu*/
                printf("Je lance le jeu\n");
                break;
            case 2:
                /*Ouvre un menu pour choisir une partie a charger*/
                printf("Allons charger une partie\n");
                break;
            case 3:
                /*Ouvre le menu options*/
                printf("Rien de mieux que de pimper sont jeu\n");
                break;
            case 4:
                /*Ouvre les credit*/
                printf("Vous avez dit qui?\n");
                break;
            case 5:
                /*Quitte le jeu*/
                printf("Au revoir et a bientot\n");
                break;
            default:
                /*Si l'utilisateur rentre autre chose*/
                printf("Ce choix n'existe pas\n");
                break;
        }
        printf("Je suis sortie du switch\n");
        printf("Choix : %d\n",choix);
    }
    printf("Je suis sortie de la boucle\n");
}
