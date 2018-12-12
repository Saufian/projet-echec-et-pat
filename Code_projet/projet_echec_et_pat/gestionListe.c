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

/*gestionListe.c
Definie toute les fonctions en rapport avec la gestion des listes d'element (qui contiennent des positions)
*/

#include "initJeu.h"


Element* initElement(int posX, int posY) {
    /* allouer un element a la premiere entree*/
    Element* elem = NULL;
    elem = malloc(sizeof(Element));
    elem->posX = posX;
    elem->posY = posY;
    elem->precedent = NULL;
    elem->suivant = NULL;
    return elem;
}


Element* addListe(Element* elementListe, Element* elementSupplementaire) {
	/* on verifie si la liste n'est pas vide*/
	if (elementListe == NULL) {
		return elementSupplementaire;  // on renvoie l'element supplementaire qui est le seul a ne pas etre null
	}
	/* On verifie si l'element que l'on rajoute n'est pas nul*/
	if (elementSupplementaire == NULL) {
        return elementListe;
	}
	Element* curseur = elementListe;
	while(curseur->suivant != NULL) {	// on va se positionner sur le dernier element de elementListe
		curseur = curseur->suivant;
	}
	/* ajout de l'element*/
	curseur->suivant = elementSupplementaire;
	elementSupplementaire->precedent = curseur;
	return securiseListe(elementListe);
}


Element* eraseListe(Element* liste) {
	/*on verifie si la liste n'est pas deja nulle*/
	if (liste == NULL) {
		return(liste);  // pas besoin de la changer, elle est deja vide
	}

	/* on se place au debut de la liste avant d'effacer chaque element*/
	Element* curseur = liste;
	while(curseur->precedent != NULL) {
		curseur = curseur->precedent;
	}

	/* on efface maintenant tous les elements les uns apres les autres*/
	while(curseur->suivant != NULL) {
		Element* temp = curseur;  // on garde le pointeur avant de passer à l'element suivant
		curseur = curseur->suivant;
		free(temp);  // on libere l'espace memoire
	}
	// il ne reste plus que le dernier element
	free(curseur);
	return NULL;
}


int trouveElement(Element* liste, int posX, int posY) {
	if (liste == NULL) {
		return 0;  // cas de la liste vide
	}
	Element* curseur = liste;
	while(curseur != NULL && (curseur->posX != posX || curseur->posY != posY)) {  // on parcours la liste
		curseur = curseur->suivant;
	}
	if (curseur == NULL) {  // on a atteint la fin de la liste sans avoir la meme valeur
		return 0;
	}
	return 1;  // on renvoi 1 car l'element contient l'information
}


Element* securiseListe(Element* liste) {
	if (liste == NULL) {  // cas de la liste vide
		return NULL;
	}
	Element* curseur = liste;
	Element* memoire1 = liste;
	Element* memoire2 = liste;
	// on revient en debut de liste
	while (curseur) {
		memoire2 = memoire1;
		memoire1 = curseur;
		curseur = curseur->precedent;
	}
	memoire1->precedent = NULL;
	if (memoire1 == memoire2) {  // cas dans lequel on se trouve deja au debut
        memoire1->suivant = memoire2->suivant;  // on va laisser la valeur initiale
	}
	else {
        memoire1->suivant = memoire2;  // on remplace par la valeur precedente
	}

	// meme chose avec le dernier element
	curseur = liste;
	memoire1 = liste;
	memoire2 = liste;
	while (curseur) {
        memoire2 = memoire1;
		memoire1 = curseur;
		curseur = curseur->suivant;
	}
	memoire1->suivant = NULL;
    if (memoire1 == memoire2) {  // cas dans lequel on se trouve deja au debut
        memoire1->precedent = memoire2->precedent;  // on va laisser la valeur initiale
	}
	else {
        memoire1->precedent = memoire2;  // on remplace par la valeur precedente
	}
	return liste;
}


void afficheListe(Element* liste) {
	/*on verifie si la liste n'est pas nulle*/
	if (liste == NULL) {
		printf("liste vide\n");
	}
    else {
        /* initialisation : retour en debut de liste*/
        Element* curseur = liste;
        while(curseur->precedent != NULL) {
            curseur = curseur->precedent;
        }
        /* On parcours tous les elements*/
        while(curseur->suivant != NULL) {
            printf("valeurs contenu dans la liste : \nX : %d\nY : %d\n", curseur->posX, curseur->posY);
            curseur = curseur->suivant;
        }
        printf("valeurs contenu dans la liste : \nX : %d\nY : %d\n", curseur->posX, curseur->posY);
    }
	printf("\n");
}
