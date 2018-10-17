#ifndef INITJEU_H_INCLUDED
#define INITJEU_H_INCLUDED

/* Mettre toutes les librairies que l'on va utiliser ici*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Mettre tout les #define ici*/
#define TAILLETERRAIN 8  // un carr� de 8 sur 8


/* Mettre les variables globales ici
(si ce n'est pas possible de faire autrement, comme en mettant une constante)*/


/* Mettre les declaration des structures ici*/

typedef struct Element {  // structure pour r�aliser une liste contenant les cases qui pourront etre atteintes
    int posX;  // coordonn�es en x  (de 1 a 8 inclus)
    int posY;  // coordonn�es en y
    struct Element* precedent;  // contient l'adresse de l'element precedent
    struct Element* suivant;  // contient l'adresse de l'element suivant
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
    Element mouvementPossible;  // on stocke les differents endroits o� la piece peut aller
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


/*Rappeler toutes les fonctions que l'on utilise ici depuis tous les documents*/

// partie pour l'initialisation du terrain
void initJeu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2);
// met en place les �l�ments du jeu (terrain, pieces, liste de pieces, etc)
void initTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
// rempli le terrain de cases blanches et noires
Joueur* initJoueur(char* nom, int couleur);
// rempli les infos relatives aux joueurs
Case initCase(int couleur, int posX, int posY);  // initialisation des cases (on met le contenu NULL)
Piece* initPiece(char type, int posX, int posY, Joueur possesseur);
// cr�� les pi�ces (type, couleur, position de base), puis utilise calculsMouvement

// partie affichage
void affichageMenu();  // affichage du menu de d�part
void affichageJeu(); // affichage du terrain, des pions

// partie calcul
void calculsVictoire();  // � chaque tour, pour les deux roi (verifie si l'action est r�alisable)
void calculsMouvement();  // � chaque fois que l'on change la disposition des pieces

//partie gestion de liste
Element* initElement(int posX, int posY);  // Initialisation des elements
Element* addListe(Element* elementListe, Element* elementSupplementaire);  // ajoute un element a une liste
void eraseListe(Element* liste);  // supprimer une liste, et liberer l'espace memoire allou�
void afficheListe(Element* liste);  // pour visualiser les listes (debug)

#endif // INITJEU_H_INCLUDED
