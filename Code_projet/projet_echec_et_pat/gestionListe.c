/*gestionListe.c
Definie toute les fonctions en rapport avec la gestion des listes
*/

#include "initJeu.h"


Element* initElement(int posX, int posY) {
    /* allouer un element a la premiere entree*/
    Element* elem = NULL;
    elem = malloc(sizeof(Element));
    (*elem).posX = posX;
    (*elem).posY = posY;
    (*elem).precedent = NULL;
    (*elem).suivant = NULL;
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
	while(curseur->suivant != NULL) {	//on va se positionner sur le dernier element de la liste
		curseur = curseur->suivant;
	}
	/* ajout de l'element*/
	curseur->suivant = elementSupplementaire;
	elementSupplementaire->precedent = curseur;
	return elementListe;
}

Element* eraseListe(Element* liste) {
	/*on verifie si la liste n'est pas deja nulle*/
	if (liste == NULL) {
		return(liste);  // pas besion de la changer, elle est deja vide
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

void afficheListe(Element* liste) {
	printf("\n");
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
}
