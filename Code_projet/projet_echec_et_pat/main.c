/* Debut de ce "fantastique" projet pour faire un jeu d'echec
avec affichage sur le terminal*/


/* Mettre tout les #include ici*/
#include <stdio.h>
#include "initJeu.h"

/* Mettre tout les #define ici*/
#define TAILLETERRAIN 8  // un carré de 8 sur 8


/* Mettre les variables globales ici
(si ce n'est pas possible de faire autrement)*/



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

