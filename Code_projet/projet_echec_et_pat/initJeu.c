/* initJeu.c
contient les fonctions pour initialyser le terrain, les pieces et les joueurs*/

#include "initJeu.h"

void initJeu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* blanc, Joueur* noir) {
    /*Initialisation des tables qui vont nous permettre de naviguer entres les pieces*/
    Piece* listePieceBlancVivante[NMBPIECEPARJOUEUR];
    Piece* listePieceNoirVivante[NMBPIECEPARJOUEUR];
    initListePiece(NMBPIECEPARJOUEUR, listePieceBlancVivante);
    initListePiece(NMBPIECEPARJOUEUR, listePieceNoirVivante);

    /* Le support ensuite*/
    initTerrain(terrain);

    /*On met chaque piece sur le tableau*/
    char nomPiece[NMBPIECEPARJOUEUR] = {'T','C','F','D','R','F','C','T'};  // disposition des pieces blanches
    for (int i = 0; i < NMBPIECEPARJOUEUR; ++i) {
        terrain[i][0].contenu = initPiece(nomPiece[i], i, 0, blanc);
        addListePiece(NMBPIECEPARJOUEUR, listePieceBlancVivante, terrain[i][0].contenu);
    }


    nomPiece[3] = 'R';  // on modifie pour les pieces noires
    nomPiece[4] = 'D';  // disposition des pieces noires
    for (int i = 0; i < NMBPIECEPARJOUEUR; ++i) {
        terrain[i][7].contenu = initPiece(nomPiece[i], i, 7, noir);
        addListePiece(NMBPIECEPARJOUEUR, listePieceNoirVivante, terrain[i][7].contenu);
    }

    /* on place ensuite les pions*/
    for(int x = 0; x<TAILLETERRAIN; x++) {
        terrain[x][1].contenu = initPiece('P', x, 1, blanc);  // on cree les pieces de pions (P)
        addListePiece(NMBPIECEPARJOUEUR, listePieceBlancVivante, terrain[x][1].contenu);
        //on ajoute les pieces dans les listes des joueurs
        terrain[x][6].contenu = initPiece('P', x, 6, noir);  // on leur attribut des joueurs
        addListePiece(NMBPIECEPARJOUEUR, listePieceNoirVivante, terrain[x][6].contenu);
    }
}

void initTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {  // initialisation du terrain
    /* initialisation des variables*/
    int couleur;  // depend de la position, 0 pour une case noire, 1 pour une case blanche

    /* process */
    /* on parcours chaque case*/
    for(int x = 0; x<TAILLETERRAIN; x++) {
        for(int y = 0; y<TAILLETERRAIN; y++) {
            couleur = (x+y)%2;  // couleur associe a la case
            terrain[x][y] = initCase(couleur, x, y);  // on y met une case nouvellement cree
        }
    }
}


Case initCase(int couleur, int posX, int posY) {
    Case temp;  // on rempli d'abord temp, avant de le renvoyer.
    temp.couleur = couleur;
    temp.posX = posX;
    temp.posY = posY;
    temp.contenu = NULL;  // les pieces ne sont pas encore cree, on est nul pour l'instant
    return temp;
}


Joueur* initJoueur(char* nom, int couleur) {
    Joueur* temporaire;
    temporaire = (Joueur*)malloc(sizeof(Joueur));  // on lui donne une taille memoire
    temporaire->nom = nom;  // on affecte les valeurs dans temporaire
    temporaire->couleur = couleur;
    return temporaire;
}


Piece* initPiece(char type, int posX, int posY, Joueur* possesseur){
    Piece* temporaire;
    temporaire = (Piece*)malloc(sizeof(Piece));  // on lui donne une taille memoire
    temporaire->type = type;  // on affecte les valeurs dans temporaire
    temporaire->posX = posX;
    temporaire->posY = posX;
    temporaire->possesseur = possesseur;
    temporaire->mouvementPossible = NULL;  // on va calculer les mouvements dans la suite
    return temporaire;
}


void initListePiece(int taille, Piece* liste[taille]){
    for (int i = 0; i < taille; ++i)
    {
        liste[i] = NULL;
    }
}


void addListePiece(int taille, Piece* liste[taille], Piece* elementSupplementaire){
    int compteur = 0;
    while (liste[compteur] != NULL && compteur < taille) {  // on va aller chercher la fin de la liste
        compteur += 1;
    }
    liste[compteur] = elementSupplementaire;  // on rajoute l'element à la fin
}


void eraseListePiece(int taille, Piece* liste[taille], Piece* cible){
    int compteur = 0;  // on met en place un compteur pour se reperer dans la liste
    while (compteur < taille  && liste[compteur] != cible) {  // on recherche l'element dans la liste
        compteur += 1;
    }
    free(liste[compteur]);  // on enleve
    liste[compteur] = NULL;
    compteur += 1;  // on va aller regarder les elements suivants
    while(liste[compteur] != NULL && compteur < taille) {  // jusque la fin de la liste
        liste[compteur-1] = liste[compteur];  // on decalle les elements
        compteur += 1;
    }
}
