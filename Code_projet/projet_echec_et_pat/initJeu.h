/* School project, creation of a chess game in C, and with the content in French, I'm sorry about that.
 * Copyright (C), 2018,  Thomas Bailleux, Vincent Gauweiler, Antoine Ruiz, from EILCO France.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef INITJEU_H_INCLUDED
#define INITJEU_H_INCLUDED

/* Mettre toutes les librairies que l'on va utiliser ici*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Mettre tout les #define ici*/
#define TAILLETERRAIN 8  // un carré de 8 sur 8
#define NMBPIECEPARJOUEUR 16  // nombre initial de piece pour chaque joueur


/* Mettre les variables globales ici
(si ce n'est pas possible de faire autrement, comme en mettant une constante)*/


/* Mettre les declaration des structures ici*/

typedef struct Element {  // structure pour réaliser une liste contenant les cases qui pourront etre atteintes
    int posX;  // coordonnées en x  (de 0 a 7 inclus)
    int posY;  // coordonnées en y
    struct Element* precedent;  // contient l'adresse de l'element precedent
    struct Element* suivant;  // contient l'adresse de l'element suivant
} Element;

typedef struct Joueur {
    char* nom;  // je peux difficilement etre plus clair
    int couleur;  // couleur des pieces qu'il joue lors de la partie
    /* 0 pour noir
        1 pour blanc*/
    struct Piece* listePiece[NMBPIECEPARJOUEUR];  // contient la listes des pieces du joueur
} Joueur;

typedef struct Piece {
    char type;  // type de la piece
    /* P -> pions
     *T -> tour
     *C -> cavalier
     *F -> fou
     *R -> roi
     *D -> dame*/
    int posX;  // toujours utile
    int posY;
    Joueur* possesseur;  // determine la couleur de la piece, et qui peut la bouger
    Element* mouvementPossible;  // on stocke les differents endroits où la piece peut aller
} Piece;

typedef struct Case {
    int couleur;  // 0, 1 -> correspond a la couleur de la case ( 0 = noir, 1 = blanc)
    /* 0 pour une case noire
     * 1 pour une case blanche */
    int surbrillance;  // 0 pour desactif, 1 pour actij
    int posX;  // c'est toujours interressant d'avoir la position
    int posY;
    Piece* contenu;  // pointeur vers la piece qui se trouve dessus, NULL sinon
} Case;



/*Rappeler toutes les fonctions que l'on utilise ici dans tous les documents*/

/* partie pour l'initialisation du terrain */
void initJeu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2);
// met en place les éléments du jeu (terrain, pieces, liste de pieces, etc)
void initTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
// rempli le terrain de cases blanches et noires
Joueur* initJoueur(char* nom, int couleur);
// rempli les infos relatives aux joueurs
Case initCase(int couleur, int posX, int posY);  // initialisation des cases (on met le contenu NULL)
Piece* initPiece(char type, int posX, int posY, Joueur* possesseur);
// créé les pièces (type, couleur, position de base), puis utilise calculsMouvement
void initListePiece(int taille, Piece* liste[taille]);  // pour initialiser les listes de pieces
void addListePiece(int taille, Piece* liste[taille],Piece* elementSupplementaire);  // on ajoute en fin de liste
void eraseListePiece(int taille, Piece* liste[taille], Piece* cible);  // suppression de l'element


/* partie affichage */
void affichageMenu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2);  // affichage du menu de départ
void affichageCharger();
void afficherStats();
void afficherCredits();
void afficherPause();
void afficherInstructions();


/* partie calcul */
void calculsVictoire();  // à chaque tour, pour les deux roi (verifie si l'action est réalisable)
void calculMouvement(Piece * listePieceJoueur[NMBPIECEPARJOUEUR], Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
// à chaque fois que l'on change la disposition des pieces
Element* calculMouvementPion(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
Element* calculMouvementTour(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
Element* calculMouvementCavalier(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
Element* calculMouvementFou(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
Element* calculMouvementDame(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
Element* calculMouvementRoi(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]);
Element* calculMouvementLineaire(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN], int sensX, int sensY);
// fonction pour calculer specifiquement les mouvement lineaire qui ne sont arrete que par la fin du plateau et les autre pieces


/* partie gestion de liste */
Element* initElement(int posX, int posY);  // Initialisation des elements
Element* addListe(Element* elementListe, Element* elementSupplementaire);  // ajoute un ou plusieurs element a une liste
Element* eraseListe(Element* liste);  // supprimer une liste, et liberer l'espace memoire alloué
int trouveElement(Element* liste, int posX, int posY);  // renvoi 1 si les pos peuvent etre trouve dans la liste d'element, renvoi 0 sinon
void afficheListe(Element* liste);  // pour visualiser les listes (debug)


/* Partie jeu */
Joueur* partieDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2);
// fonction principale lançant le jeu pour deux joueurs, et renvoi le joueur gagnant
void affichageTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]);  // affiche l'etat du terrain.
void gestionSurbrillance(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Element* liste);
// on donne en argument la liste des positions voulue. Vide la surbrillance des autres cases
void scanDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueurActuel, int commande[2][2]);
/* scan les entrees des participants, et modifie un tableau[2][2] contenant la position de la piece a bouger,
 * et la position a laquelle le joueur veut la mettre. La fonction verifie si le mouvement est possible
 * (en regardant les positions possibles de la piece choisi, affiche en surbrillance les choix possible (qui correspondent
 * aux positions possibles de la piece selectionné, puis renvoi les informations rentrees par l'utilisateur dans commande si le mouvement
 * est possible)). */
void deplacementPiece(Case terrain[TAILLETERRAIN][TAILLETERRAIN], int mouvement[2][2]);
// change de position la piece marque par mouvement, et gere le cas de la prise d'une piece ennemis
Joueur* testVictoire(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2);
// verifit l'etat du roi de chaque coté, et renvoi le gagnant le cas echeant (renvoi NULL sinon).


/*Fonction de gestion de sauvegarde*/
FILE * initSaveGame(Joueur* joueur1, Joueur* joueur2);
FILE * saveGame(FILE * saveFile, int commande[2][2]);
void closeSaveGame(FILE * saveFile);

#endif // INITJEU_H_INCLUDED
