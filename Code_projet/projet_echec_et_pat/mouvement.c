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

/* mouvement.c
Contient les fonctions pour calculer les mouvements possibles de chaque pieces
*/

#include "initJeu.h"


/**
 * Mise en place du calcul des mouvements des pieces du joueur principal, en fonction des deplacements des pieces ennemis.
 * Le calcul des mouvements des roi depend des mouvements des autres pieces, on realise donc les mouvements des roi dans un second temps
 * @param  principal  Pointeur du joueur dont on veut voir les mouvements calcule
 * @param  adversaire  Pointeur du joueur qui va restreindre les mouvements du roi du joueur principal
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  rien
 */
void calculMouvement (Joueur* principal, Joueur* adversaire, Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	Piece* roiActuel = switchMouvement(principal->listePiece, terrain);
	Piece* roiAdverse = switchMouvement(adversaire->listePiece, terrain);
	// calcul du mouvement des rois
	if (roiActuel != NULL && roiAdverse != NULL) {  // on blinde le prog pour eviter les erreurs
        roiAdverse->mouvementPossible = eraseListe(roiActuel->mouvementPossible);
        roiActuel->mouvementPossible = eraseListe(roiActuel->mouvementPossible);
        roiAdverse->mouvementPossible = calculMouvementRoi(roiAdverse, principal->listePiece, terrain);
        roiActuel->mouvementPossible = calculMouvementRoi(roiActuel, adversaire->listePiece, terrain);
    }
    else {  // cas dans lequel il manque un roi (chose impossible aux echecs)
        printf("Il manque un roi, erreur.");
    }
}


/**
 * Separation des cas en fonction des types des pieces
 * @param  listePieceJoueur[NMBPIECEPARJOUEUR]  liste des pieces d'un joueur pour lesquelles on va calculer les deplacements possible
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  un pointeur vers le roi contenu dans la liste, dont on doit calculer les mouvements plus tard
 */
Piece* switchMouvement(Piece * listePieceJoueur[NMBPIECEPARJOUEUR], Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	/* on va parcourir toutes les pieces presentes dans la liste, puis calculer leurs mouvements
	 * les deux tableaux en argument de la fonction sont de taille NMBPIECEPARJOUEUR et TAILLETERRAIN
	 * La fonction renvoie la piece de roi (pour pouvoir s'en occuper plus tard)
	 */
	Piece* retour = NULL;  // definition de la variable que l'on va renvoyer (le roi)

	int curseur = 0;
	while (listePieceJoueur[curseur] != NULL && curseur < NMBPIECEPARJOUEUR) {  // on evite les depassement
		// et le calcul pour les elements nuls
        /* initialisation*/
        Piece* pieceActuelle = listePieceJoueur[curseur];
        pieceActuelle->mouvementPossible = eraseListe(pieceActuelle->mouvementPossible);  // on vide la liste

		/* traitement*/
		switch(pieceActuelle->type)
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
				// printf("calcul des mouvements du roi decalle\n");
				retour = pieceActuelle;
				//pieceActuelle->mouvementPossible = calculMouvementRoi(pieceActuelle, terrain);  // on va s'occuper du roi separement
				break;
			case 'D':
				pieceActuelle->mouvementPossible = calculMouvementDame(pieceActuelle, terrain);
				//printf("calcul des mouvements de la dame\n");
				break;
		}
        // afficheListe(pieceActuelle->mouvementPossible);  // affichage pour le control du fonctionnement
		curseur++;
	}
	return retour;
}

/* fonctions pour chaque type de pieces*/


/**
 * calcul des mouvements des pieces de type 'P', donc des pieces de pions
 * @param  piece  Piece pour laquelle on va calculer le mouvement (permet de recuperer la position)
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece
 */
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
	posY = piece->posY +(1*sens);  // on remet la position en Y au bon niveau
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


/**
 * calcul des mouvements des pieces de type 'T', donc des pieces de tours
 * @param  piece  piece pour laquelle on va calculer le mouvement (permet de recuperer la position)
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece
 */
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


/**
 * calcul des mouvements des pieces de type 'C', donc des pieces de cavaliers
 * @param  piece  piece pour laquelle on va calculer le mouvement (permet de recuperer la position)
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece
 */
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


/**
 * calcul des mouvements des pieces de type 'F', donc des pieces de fou
 * @param  piece  piece pour laquelle on va calculer le mouvement (permet de recuperer la position)
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece
 */
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


/**
 * calcul des mouvements des pieces de type 'D', donc des pieces de dames
 * @param  piece  piece pour laquelle on va calculer le mouvement (permet de recuperer la position)
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece
 */
Element* calculMouvementDame(Piece * piece, Case terrain[TAILLETERRAIN][TAILLETERRAIN]){
	/* Initialisation */
	Element* possibilite = NULL;

	/* traitement
	 * le deplacement de la dame correspond a celui du fou et de la tour */
	possibilite = addListe(calculMouvementTour(piece, terrain), calculMouvementFou(piece, terrain));
	return possibilite;
}


/**
 * calcul des mouvements des pieces de type 'R', donc des pieces de rois
 * @param  piece  piece pour laquelle on va calculer le mouvement (permet de recuperer la position)
 * @param  listePieceJoueur[NMBPIECEPARJOUEUR]  la liste des pieces adverses, qui vont restreindre les mouvements des rois
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece
 */
Element* calculMouvementRoi(Piece * piece, Piece * listePieceJoueur[NMBPIECEPARJOUEUR], Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	/* Initialisation */
	Element* possibilite = NULL;

	/* Mise en evidence des cases que l'adversaire peut occuper */
	int compteur = 0;
	Element* somme = NULL;  // pour stocker la somme de toutes les positions
	while(listePieceJoueur[compteur] != NULL && compteur < NMBPIECEPARJOUEUR) {  // on va parcourir toutes les pieces
		/* on va devoir faire une copie des elements en question avant de pouvoir les utiliser */
		Element* liste = listePieceJoueur[compteur]->mouvementPossible;
		Element* copie = NULL;
		if (listePieceJoueur[compteur]->type != 'P') {  // si ce n'est pas un pion
            while (liste != NULL) {  // on va juste pacourir et copier la liste des positions deja existante
                copie = addListe(copie, initElement(liste->posX, liste->posY));
                liste = liste->suivant;
            }
        }
        else {  // si ce sont des pions, on va juste mettre les deux cases en diago
            int sens = 1;  // si la couleur est blanche
            if (listePieceJoueur[compteur]->possesseur->couleur == 0) {  // si la couleur est noire
                sens = -1;
            }
            Piece* pionTemp = listePieceJoueur[compteur];
            if (pionTemp->posY + sens >= 0 && pionTemp->posY + sens <= TAILLETERRAIN-1
             && pionTemp->posX + 1 >= 0 && pionTemp->posX + 1 <= TAILLETERRAIN-1) {
                copie = addListe(copie, initElement(pionTemp->posX + 1, pionTemp->posY + sens));
            }
            if (pionTemp->posY + sens >= 0 && pionTemp->posY + sens <= TAILLETERRAIN-1
             && pionTemp->posX - 1 >= 0 && pionTemp->posX - 1 <= TAILLETERRAIN-1) {
                copie = addListe(copie, initElement(pionTemp->posX - 1, pionTemp->posY + sens));
            }
        }
		somme = addListe(somme, copie);
		compteur += 1;
	}
	gestionSurbrillance(terrain, somme);  // on va mettre en surbrillance

	/* calcul des mouvements possible, sauf les cases marque et la case actuelle */
	for (int posX = piece->posX-1; posX <= piece->posX+1; posX++) {  // on va parcourir les environs
		for (int posY = piece->posY-1; posY <= piece->posY+1; posY++) {  // dans les deux dimensions
            if (posX >= 0 && posX <= TAILLETERRAIN-1 && posY >= 0 && posY <= TAILLETERRAIN-1) {  // on evite les depassements
                if (posX != piece->posX || posY != piece->posY) {  // inutile de mettre la case du roi
                    if (terrain[posX][posY].surbrillance == 0) {  // on ne peut pas aller là ou la case est deja prise
                        if (terrain[posX][posY].contenu == NULL
                        || terrain[posX][posY].contenu->possesseur->couleur != piece->possesseur->couleur) {
                        // on regarde s'il y a une piece allie qui gene
                            possibilite = addListe(possibilite, initElement(posX, posY));
                        }
                    }
                }
            }
        }
	}
	gestionSurbrillance(terrain, NULL);  // on vide la surbrillance
	return possibilite;
}


/**
 * calcul les mouvements lineaire qui ne s'arretent qu'avec les bords du terrain
 * @param  piece  piece pour laquelle on va calculer le mouvement
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour detecter les pieces sur les cases
 * @param  sensX  la direction dans laquelle on va progresser (direction horizontale)
 * @param  sensY  la direction dans laquelle on va progresser (direction verticale)
 * @return  la liste dynamique des coordonnees des cases qui peuvent etre atteintes par la piece dans ce sens
 */
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


/**
 * renvoi la premiere piece qui peut atteindre une case precise, ou NULL s'il n'existe pas de pieces pouvant atteindre la case
 * @param  listePieceJoueur[NMBPIECEPARJOUEUR]  La liste de toutes les pieces d'un joueur
 * @param  x  La position en x de la case qui nous interresse
 * @param  y  La position en y de la case qui nous interresse
 * @return  la piece qui peut atteindre la case, ou NULL
 */
Piece* captureCase(Piece * listePieceJoueur[NMBPIECEPARJOUEUR], int x, int y) {
	/* Initialisation */
	Piece* soluce = NULL;
	int compteur = 0;

	/* Traitement */
	while (compteur < NMBPIECEPARJOUEUR && listePieceJoueur[compteur] != NULL && soluce == NULL) {
		Element* curseur = listePieceJoueur[compteur]->mouvementPossible;  // on va simplifier l'ecriture
		while (curseur != NULL && soluce == NULL) {
			if (curseur->posX == x && curseur->posY == y) {  // on regarde si les coordonnees correspondent
				/* attention, on ne doit pas prendre les cases devant les pions */
				if (listePieceJoueur[compteur]->type == 'P') {  // test pour detecter les pions
					if (listePieceJoueur[compteur]->posX != x) {  // si le pion n'est pas aligne avec la case
						soluce = listePieceJoueur[compteur];  // on renvoi la piece
					}  // si c'est aligne, on ne fait rien
				}
				else {  // dans le cas ou la piece n'est pas un pion
					soluce = listePieceJoueur[compteur];
				}
			}
			curseur = curseur->suivant;
		}
		compteur ++;
	}
	return soluce;
}
