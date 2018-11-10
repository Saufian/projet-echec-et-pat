/* mouvement.c
Contient les fonctions pour calculer les mouvements possibles de chaque pieces
*/

#include "initJeu.h"


/* on va d'abord separer les cas, en fonction des types de piece*/
void calculMouvement(Piece * listePieceJoueur[NMBPIECEPARJOUEUR], Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	/* on va parcourir toutes les pieces presentes dans la liste, puis calculer leurs mouvements
	les deux tableaux en argument de la fonction sont de taille NMBPIECEPARJOUEUR et TAILLETERRAIN*/
	int curseur = 0;
	while (listePieceJoueur[curseur] != NULL && curseur < NMBPIECEPARJOUEUR) {  // on evite les depassement
		// et le calcul pour les elements nuls
        /* initialisation*/
        Piece* pieceActuelle = listePieceJoueur[curseur];
        pieceActuelle->mouvementPossible = eraseListe(pieceActuelle->mouvementPossible);  // on vide la liste
		char typePion = pieceActuelle->type;  // on stocke le type pour simplifier

		/* traitement*/
		switch(typePion)
		{
			case 'P':
				/* renvoie les positions possible */
				pieceActuelle->mouvementPossible = calculMouvementPion(pieceActuelle, terrain);
				printf("calcul des mouvements du pion\n");
				break;
			case 'T':
				pieceActuelle->mouvementPossible = calculMouvementTour(pieceActuelle, terrain);
				printf("calcul des mouvements de la tour\n");
				break;
			case 'C':
				printf("calcul des mouvements du cavalier\n");
				pieceActuelle->mouvementPossible = calculMouvementCavalier(pieceActuelle, terrain);
				break;
			case 'F':
				pieceActuelle->mouvementPossible = calculMouvementFou(pieceActuelle, terrain);
				printf("calcul des mouvements du fou\n");
				break;
			case 'R':
				printf("calcul des mouvements du roi\n");
				pieceActuelle->mouvementPossible = calculMouvementRoi(pieceActuelle, terrain);
				break;
			case 'D':
				pieceActuelle->mouvementPossible = calculMouvementDame(pieceActuelle, terrain);
				printf("calcul des mouvements de la dame\n");
				break;
		}
        afficheListe(pieceActuelle->mouvementPossible);
		curseur++;
	}
}

/* fonctions pour chaque type de pieces*/

Element* calculMouvementPion(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	// attention, il faut separer les cas en fonction de la couleur de la piece
	Element* possibilite = NULL;
	return possibilite;
}

Element* calculMouvementTour(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	/* Initialisation */
	Element* possibilite = NULL;

	/* traitement*/
	/* On s'occupe dans un premier temps du deplacement horizontal vers le haut du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, 0, 1));
	/* On s'occupe ensuite du deplacement horizontal vers le bas du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, 0, -1));
	/* On s'occupe ensuite du deplacement vertical vers la gauche du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, -1, 0));
	/* On s'occupe ensuite du deplacement vertical vers la droite du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, 1, 0));

	return possibilite;
}

Element* calculMouvementCavalier(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	Element* possibilite = NULL;
	return possibilite;
}

Element* calculMouvementFou(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	/* Initialisation */
	Element* possibilite = NULL;

	/* traitement*/
	/* On s'occupe dans un premier temps du deplacement diagonal vers le haut a gauche du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, -1, 1));
	/* On s'occupe ensuite du deplacement horizontal vers le haut a droite du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, 1, 1));
	/* On s'occupe ensuite du deplacement vertical vers le bas a droite du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, 1, -1));
	/* On s'occupe ensuite du deplacement vertical vers le bas a gauche du plateau */
	possibilite = addListe(possibilite, calculMouvementLineaire(piece, terrain, -1, -1));

	return possibilite;
}

Element* calculMouvementDame(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	/* Initialisation */
	Element* possibilite = NULL;

	/* traitement
	 * le deplacement de la dame correspond a celui du fou et de la tour */
	possibilite = addListe(calculMouvementTour(piece, terrain), calculMouvementFou(piece, terrain));
	return possibilite;
}

Element* calculMouvementRoi(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	Element* possibilite = NULL;
	return possibilite;
}

Element* calculMouvementLineaire(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN], int sensX, int sensY){
	/* Fonction pour calculer les deplacements en ligne (en utilisant sensX et sensY pour diriger)
	 * On s'arrete si l'on arrive sur une case ennemis, si on depasse du plateau, ou s'il y a une piece allie
	*/
	/* initialisation*/
	Element* possibilite = NULL;  // variable pour stocker les resultats
	int curseurX = piece->posX;
	int curseurY = piece->posY;

	curseurX = curseurX + sensX;  // on va passer a l'element suivant, pour ne pas dedoubler la
	curseurY = curseurY + sensY;  // case sur laquelle est la piece

	/*traitement*/
	while (curseurX >= 0 && curseurX <= TAILLETERRAIN-1 && curseurY >= 0 && curseurY <= TAILLETERRAIN-1) {
	// on parcours tout le terrain restant (d'indice 0 à TAILLETERRAIN-1)
		if (terrain[curseurX][curseurY].contenu == NULL) {  // donc s'il n'y a pas de piece sur la case cible
			//on ajoute la case a la liste des deplacements possibles
			possibilite = addListe(possibilite, initElement(curseurX, curseurY));
			curseurX = curseurX + sensX;  // on va passer a l'element suivant
			curseurY = curseurY + sensY;
		}
		else {
            /* cas ou la piece rencontre est de couleur differente de cette piece*/
			if (terrain[curseurX][curseurY].contenu->possesseur->couleur != piece->possesseur->couleur){
                //on doit rajouter cette case, puis s'arreter, on ne peut pas passer a travers de la piece
                possibilite = addListe(possibilite, initElement(curseurX, curseurY));
			}
			/* dans le cas ou c'est une piece de la meme couleur, on quitte directement la boucle*/
			curseurX = TAILLETERRAIN;  // on fais en sorte de quitter la boucle while
		}
	}
	return possibilite;
}
