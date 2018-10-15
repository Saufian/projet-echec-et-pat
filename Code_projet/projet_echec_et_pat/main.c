/* Debut de ce "fantastique" projet pour faire un jeu d'echec
avec affichage sur le terminal*/


/* Mettre tout les #include ici*/
#include <stdio.h>


/* Mettre tout les #define ici*/
#define TAILLETERRAIN 8  // un carré de 8 sur 8


/* Mettre les variables globales ici
(si ce n'est pas possible de faire autrement)*/


/* Mettre les declaration des structures ici*/

typedef struct Element {
    int n;
    struct Element * ptr_precedent;  // contient l'adresse de l'element precedent
    struct Element * ptr_suivant;  // contient l'adresse de l'element suivant
} Element;

typedef struct Joueur {
    char* nom;  // je peux difficilement etre plus clair
    int couleur;  // couleur des pieces qu'il joue lors de la partie
    /* 0 pour noir
        1 pour blanc*/
} Joueur;

typedef struct Piece {
    char type;  // type de la piece
    /* P -> pions
        T -> tour
        C -> cavalier
        F -> fou
        R -> roi
        D -> dame*/
    int posX;  // toujours utile
    int posY;
    Joueur possesseur;  // determine la couleur de la piece, et qui peut la bouger
    Element mouvementPossible;  // on stocke les differents endroits où la piece peut aller
} Piece;

typedef struct Case {
    int couleur;  // 0, 1 ou 2  -> correspond a la couleur de la case
    /* 0 pour une case noire
        1 pour une case blanche
        2 pour une case en surbrillance */
    int posX;  // c'est toujours interressant d'avoir la position
    int posY;
    Piece* Contenu;  // pointeur vers la piece qui se trouve dessus, NULL sinon
} Case;


/*Rappeler toutes les fonctions que l'on utilise ici*/
void initJeu();  // met en place les éléments du jeu (terrain, pieces, liste de pieces, etc)
void initTerrain();  // rempli le terrain de cases blanches et noires
Piece initPiece();  // créé les pièces (type, couleur, position de base), puis utilise calculsMouvement

void affichageMenu();  // affichage du menu de départ
void affichageJeu();  // affichage du terrain, des pions

void calculsVictoire();  // à chaque tour, pour les deux roi (verifie si l'action est réalisable)
void calculsMouvement();  // à chaque fois que l'on change la disposition des pieces


/* Fonction main*/

int main() {
    /* Initialisation des variables*/
    Case terrain[TAILLETERRAIN][TAILLETERRAIN];
    printf("hello world");
    return 0;
}

