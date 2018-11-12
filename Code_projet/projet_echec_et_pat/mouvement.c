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
				//printf("calcul des mouvements du pion\n");
				break;
			case 'T':
				pieceActuelle->mouvementPossible = calculMouvementTour(pieceActuelle, terrain);
				//printf("calcul des mouvements de la tour\n");
				break;
			case 'C':
				//printf("calcul des mouvements du cavalier\n");
				pieceActuelle->mouvementPossible = calculMouvementCavalier(pieceActuelle, terrain);
				break;
			case 'F':
				pieceActuelle->mouvementPossible = calculMouvementFou(pieceActuelle, terrain);
				//printf("calcul des mouvements du fou\n");
				break;
			case 'R':
				//printf("calcul des mouvements du roi\n");
				pieceActuelle->mouvementPossible = calculMouvementRoi(pieceActuelle, terrain);
				break;
			case 'D':
				pieceActuelle->mouvementPossible = calculMouvementDame(pieceActuelle, terrain);
				//printf("calcul des mouvements de la dame\n");
				break;
		}
        // afficheListe(pieceActuelle->mouvementPossible);  // affichage pour le control du fonctionnement
		curseur++;
	}
}

/* fonctions pour chaque type de pieces*/

Element* calculMouvementPion(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	// attention, il faut faire la difference de cas en fonction de la couleur de la piece
	/* Initialisation */
	Element* possibilite = NULL;
	int posX = piece->posX;
	int posY = piece->posY;
	int sens;  // si sens=-1, alors les pieces descedent, donc elles sont noires, et inversement avec sens=1
	int posLigneDepart;
	if (piece->possesseur->couleur == 1) {
		sens = 1;  // la piece est blanche
		posLigneDepart = 1;  // position de la ligne ou sont alignes les pions
	}
	else {
		sens = -1;  // la piece est noire
		posLigneDepart = TAILLETERRAIN - 2;
	}

	/* Traitement*/
	/* deplacement normal */
	posY += sens;  // la case suivante
	if (posX >= 0 && posX <= TAILLETERRAIN-1 && posY >= 0 && posY <= TAILLETERRAIN-1) {  // on regarde pour les depassements
		if (terrain[posX][posY].contenu == NULL) {  // si la case est vide
			possibilite = addListe(possibilite, initElement(posX, posY));

			/* deplacement de 2 depuis le depart, ne marche que si la case precedente est vide*/
			posY += sens;  // la case encore après
			if (posX >= 0 && posX <= TAILLETERRAIN-1 && posY >= 0 && posY <= TAILLETERRAIN-1) {  // attention aux depassements
				if (terrain[posX][posY].contenu == NULL && piece->posY == posLigneDepart) {  // si la case est vide et la position bonne
					possibilite = addListe(possibilite, initElement(posX, posY));
				}
			}
		}
	}
	/* prise de pieces en diago */
	posY = piece->posY +1;  // on remet la position en X au bon niveau
	for (int valeur = -1; valeur <= 1; valeur += 2) {  // petite boucle pour economiser un copier-coller
		posX = piece->posX + valeur;  // on regarde les cases a cote
		if (posX >= 0 && posX <= TAILLETERRAIN-1 && posY >= 0 && posY <= TAILLETERRAIN-1) {  // on regarde pour les depassements
			if (terrain[posX][posY].contenu != NULL
			&& terrain[posX][posY].contenu->possesseur->couleur != piece->possesseur->couleur) {
			// si la case est occupe par une unite ennemis
					possibilite = addListe(possibilite, initElement(posX, posY));
			}
		}
	}
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
	/* Initialisation */
	Element* possibilite = NULL;
	int posX;
	int posY;
	/* Traitement */
	// pour une meilleure lisibilite, on va mettre les coeficients a appliquer sur la position du cavalier dans un tableau
	int coef[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};  // couple {{x1,y1},{x2,y2}, ... }
	for (int indice = 0; indice < 8; indice++) {  // on parcours la liste
		posX = piece->posX + coef[indice][0];
		posY = piece->posY + coef[indice][1];
		if (posX >= 0 && posX <= TAILLETERRAIN-1 && posY >= 0 && posY <= TAILLETERRAIN-1) {  // on regarde pour les depassements
			if (terrain[posX][posY].contenu == NULL
            || terrain[posX][posY].contenu->possesseur->couleur != piece->possesseur->couleur) {
            // on regarde s'il y a une piece allie qui gene
				possibilite = addListe(possibilite, initElement(posX, posY));
			}
		}
	}
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
	for (int posX = piece->posX-1; posX <= piece->posX+1; posX++) {  // on va parcourir les environs
		for (int posY = piece->posY-1; posY <= piece->posY+1; posY++) {  // dans les deux dimensions
            if (posX >= 0 && posX <= TAILLETERRAIN-1 && posY >= 0 && posY <= TAILLETERRAIN-1) {  // on evite les depassements
                if (posX != piece->posX || posY != piece->posY) {  // inutile de mettre la case du roi
                    if (terrain[posX][posY].contenu == NULL
                    || terrain[posX][posY].contenu->possesseur->couleur != piece->possesseur->couleur) {
                    // on regarde s'il y a une piece allie qui gene
                	    possibilite = addListe(possibilite, initElement(posX, posY));
                	}
                }
            }
        }
	}
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
