#include "initJeu.h"

void initJeu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2) {
    /* Le support d'abord*/
    initTerrain(terrain);


}

void initTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {  // initialisation du terrain
    /* initialisation des variables*/
    int couleur;  // depend de la position, 0 pour une case noire, 1 pour une case blanche

    /* process */
    for(int x = 0; x<TAILLETERRAIN; x++) {
        for(int y = 0; y<TAILLETERRAIN; y++) {
            couleur = (x+y)%2;
            terrain[x][y] = initCase(couleur, x, y);
        }
    }
}


Case initCase(int couleur, int posX, int posY) {
    Case temp;  // on rempli d'abord temp, avant de le renvoyer.
    temp.couleur = couleur;
    temp.posX = posX;
    temp.posY = posY;
    temp.Contenu = NULL;  // les pieces ne sont pas encore creer, on est nul pour l'instant
    return temp;
}


Joueur* initJoueur(char* nom, int couleur) {
    Joueur* temporaire;
    temporaire = (Joueur*)malloc(sizeof(Joueur));  // on lui donne une taille memoire
    temporaire->nom = nom;  // on affecte les valeurs dans temporaire
    temporaire->couleur = couleur;
    return temporaire;
}
