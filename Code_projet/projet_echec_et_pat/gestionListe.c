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
	Element* curseur = elementListe;
	while(curseur->suivant != NULL) {	//on va se positionner sur le dernier element de la liste
		curseur = curseur->suivant;
	}
	/* ajout de l'element*/
	curseur->suivant = elementSupplementaire;
	elementSupplementaire->precedent = curseur;
	return elementListe;
}

void eraseListe(Element* liste) {
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
}

void afficheListe(Element* liste) {
	/* initialisation : retour en debut de liste*/
	Element* curseur = liste;
	while(curseur->precedent != NULL) {
		curseur = curseur->precedent;
	}

	/* On parcours tous les elements*/
	while(curseur->suivant != NULL) {
		printf("valeurs contenu dans la liste : \nX : %d\nY : %d\n", curseur->posX, curseur->posY);
		Element* temp = curseur;  // on garde le pointeur avant de passer à l'element suivant
		curseur = curseur->suivant;
	}
	printf("valeurs contenu dans la liste : \nX : %d\nY : %d\n", curseur->posX, curseur->posY);
}