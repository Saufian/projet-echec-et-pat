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

/* Jeu.compteur
contient les fonctions pour animer une partie*/

#include "initJeu.h"

Joueur* partieDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2) {
	//Rajouter un test si fichier existe partie charger pour le lancer en mode ajout récupérer les donnée et repositioner le pointeur dans le fichier
	/* fonction principale pour le jeux a 2 joueurs*/
	Joueur* gagnant = NULL;
	Joueur* joueurActuel = joueur1;
	Joueur* joueurAdverse = joueur2;
	int mouvement[2][2];
	/* calcul des positions pour le joueur 1*/
	calculMouvement(joueur1, joueur2, terrain);  // premier calcul des mouvements des pieces

	while (gagnant == NULL) {
		scanDeuxJoueurs(terrain, joueurActuel, joueurAdverse, mouvement);
		saveGame(mouvement);//je sauvegarde le déplacement OldX OldY NewX NewY
		printf("La piece en %d,%d va en %d,%d", mouvement[0][0], mouvement[1][0], mouvement[0][1], mouvement[1][1]);
		deplacementPiece(terrain, mouvement);
		calculMouvement(joueurActuel, joueurAdverse, terrain);  // on recalcul les mouvements des pieces

		/* changement de joueur */
		if (joueurActuel == joueur1) {
			joueurActuel = joueur2;
			joueurAdverse = joueur1;
		}
		else {
			joueurActuel = joueur1;
			joueurAdverse = joueur2;
		}
		calculMouvement(joueurActuel, joueurAdverse, terrain);  // on recalcul les mouvements des pieces
		gagnant = testVictoire(terrain, joueurActuel, joueurAdverse);
		//closeSaveGame(saveFile); //gagnant ne fonctionnent pas encore je dois fermer le fichier plus tôt
	}
	//closeSaveGame(saveFile); // sera actif quand il y aura un gagnant
	if (gagnant == joueur1 || gagnant == joueur2) {  // Si le gagnant est l'un des joueurs
		return gagnant;
	}
	return initJoueur("pat", 3);  // cas d'un pat, on retourne un joueur dont le nom est pat

}


void affichageTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	/* Initialisation */
	system("cls");
	int curseurY, compteur =TAILLETERRAIN;
	/* Affichage */
	printf("\n\n     A      B      C      D      E      F      G      H \n\n" );  // affi
	for (curseurY = 0; curseurY < TAILLETERRAIN; curseurY++) {  //Parcours des lignes
		afficherLigne(terrain, curseurY, compteur);
		compteur--;
	}
	Color(15, 0);
	printf("\n     A      B      C      D      E      F      G      H \n" );  // legende et affichage de la derniere ligne.
}


void gestionSurbrillance(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Element* liste){
	/*Initialisation, on nettoie toutes les cases du terrain*/
	for (int x = 0; x < TAILLETERRAIN; x++) {  // on parcours le terrain
		for (int y = 0; y < TAILLETERRAIN; y++) {
			if (terrain[x][y].surbrillance == 1) {
				terrain[x][y].surbrillance = 0;  // si le terrain est en surbrillance, on efface ce comportement
			}
		}
	}
	/* Remplissage */
	if (liste != NULL) {  // On fait attention au cas ou la liste est vide
		Element* curseur = liste;
		while (curseur != NULL) {  // on parcours la liste
			terrain[curseur->posX][curseur->posY].surbrillance = 1;  // on met la case choisie en surbrillance
			curseur = curseur->suivant;
		}
	}
}

void scanDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueurActuel, Joueur* joueurAdverse, int commande[2][2]) {
	/* Initialisation des variables */
	int posX;
	int posY;
	char temp;
	int boucle = 0;  // pour permettre au joueur de changer son choix de piece
	Piece* selection;
	Piece* roiActuel;

	/* initialisation des cases du tableau commandes */
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			commande[i][j] = 0;
		}
	}

	/* Initialisation de roiActuel */
	int compteur = 0;
	while (joueurActuel->listePiece[compteur]->type != 'R') {  // il est obligatoire d'avoir un unique roi, on va finir par le trouver
		compteur ++;
	}
	roiActuel = joueurActuel->listePiece[compteur];

	/* Interraction 1 avec le joueur :
	* Demande de la piece a bouger
	*/
	do {  // on va revenir ici si l'utilisateur veut changer de piece selectionne, ou si le roi reste en echec
		boucle = 0;  // on remet boucle a 0 pour ne pas faire de boucles infinies
		/* On va montrer plus tard quelles sont les cases que l'on peut atteindre.
		 * Dans un premier temps, on va remettre la surbrillance des cases a 0, et reafficher le terrain
		 */
		gestionSurbrillance(terrain, NULL);  // on enleve la surbrillance
		affichageTerrain(terrain);

		do {  // on boucle tant que la piece n'est pas de la couleur du joueur
			do {  // on boucle tant que l'entree ne correspond pas a une piece, ou depasse du terrain
                printf("Au tour de %s\n", joueurActuel->nom);  // petit affichage du tour du joueur
				printf("Quelle piece voulez vous bouger ?\n");
				printf("Valeur X de la piece : ");
				scanf("%c%*1[\n]", &temp);
				posX=temp-'a';//TODO rajouter majuscule
				/*if (posX == 0)
                    afficherPause();*/
				printf("Valeur Y de la piece : ");
				scanf("%d%*1[\n]", &posY);
				posY=posY-1;
				if ((posX < 0 || posX >= TAILLETERRAIN || posY < 0 || posY >= TAILLETERRAIN || terrain[posX][posY].contenu == NULL)) {
					printf("Aucune piece ici, recommencez.\n\n");  // test pour l'affichage d'un message d'erreur
				}
				else {
					if (terrain[posX][posY].contenu->possesseur->couleur != joueurActuel->couleur) {  // piece de la mauvaise couleur
						printf("Piece de la mauvaise couleur, recommencez.\n\n");  // test pour l'affichage d'un message d'erreur
					}
				}

			} while (posX < 0 || posX >= TAILLETERRAIN || posY < 0 || posY >= TAILLETERRAIN || terrain[posX][posY].contenu == NULL);
		} while (terrain[posX][posY].contenu->possesseur->couleur != joueurActuel->couleur);
		/* On va stocker dans une variable la piece que le joueur a selectionne,
		 * Et afficher les deplacement realisable par la piece
		 * Puis sauvegarder l'information de la piece a bouger dans la variable 'commande'
		 */
		selection = terrain[posX][posY].contenu;
		gestionSurbrillance(terrain, selection->mouvementPossible);
		affichageTerrain(terrain);
		/* on met les donnees dans commande*/
		commande[0][0] = posX;
		commande[1][0] = posY;

		/* Interraction 2 avec le joueur
		 * On lui demande la nouvelle position de la piece qu'il vient de selectionner
		 */
		do {  // tant que le mouvement de la piece n'est pas realisable, ou que l'entree depasse le terrain
			printf("\nOu voulez vous bouger cette piece ( %c )?  (ou %d,%d pour revenir a la selection de piece)\n",
			 selection->type, TAILLETERRAIN, TAILLETERRAIN);  // TODO: remplacer par la valeur correspondant au retour (surement 0,0)
			printf("Nouvelle valeur en X : ");
			scanf("%c%*1[\n]", &temp);  //TODO: securiser ces entrees
			posX=temp-'a';//TODO rajouter majuscule
			printf("Nouvelle valeur en Y : ");
			scanf("%d%*1[\n]", &posY);
			posY=posY-1;//remetre au valeur afficher
			if (trouveElement(selection->mouvementPossible, posX, posY) == 0 && (posX != TAILLETERRAIN && posY != TAILLETERRAIN)) {
			// situation ou l'on va boucler car l'on depasse le terrain
				printf("Mouvement impossible, veuillez reessayer.\n\n");
			}
			if (posX == TAILLETERRAIN && posY == TAILLETERRAIN) {  // cas ou l'utilisateur veut changer de piece
				boucle = 1;  // on met boucle a 1 pour revenir au debut
			}
		} while(trouveElement(selection->mouvementPossible, posX, posY) == 0 && (posX != TAILLETERRAIN && posY != TAILLETERRAIN));
		if (boucle != 1) {  // si l'on boucle, inutile de faire autre chose
            commande[0][1] = posX;
            commande[1][1] = posY;  // on stocke dans le tableau avant de le renvoyer

            /* On regarde si le roi n'est pas en echec */
            // on test si il y a echec, en bougeant temporairement
            deplacementPiece(terrain, commande);
            calculMouvement(joueurActuel, joueurAdverse, terrain);
            int mouvementInverse[2][2] = {{commande[0][1], commande[0][0]},{commande[1][1], commande[1][0]}};
            if (captureCase(joueurAdverse->listePiece, roiActuel->posX, roiActuel->posY) != NULL) {  // en cas d'echec du roi car une piece ennemis peut l'atteindre
                printf("Impossible, le roi serais en echec.\n");
                boucle = 1;  // on fait refaire la saisie
            }
            deplacementPiece(terrain, mouvementInverse);  // on remet dans la position initiale
            calculMouvement(joueurActuel, joueurAdverse, terrain);
		}
	} while (boucle == 1);  // on reviens en arriere si l'utilisateur veut changer de piece
}


void deplacementPiece(Case terrain[TAILLETERRAIN][TAILLETERRAIN], int mouvement[2][2]) {
	/* Initialisation */
	Case* caseDepart = &terrain[mouvement[0][0]][mouvement[1][0]];  // on veut modifier le contenu de la case
	Case* caseArrive = &terrain[mouvement[0][1]][mouvement[1][1]];
	Piece* pieceDepart = caseDepart->contenu;  // le mouvement existe, donc on est sur qu'il y a une piece sur cette case

	/* Cas ou il y a une piece a l'arrivee, que l'on va devoir supprimer*/
	if (caseArrive->contenu != NULL) {
		Piece* pieceArrive = caseArrive->contenu;
		caseArrive->contenu = NULL;  // on vide la case d'arrive
		/* on va enlever la piece de la liste du joueur qui la controle*/
		eraseListePiece(NMBPIECEPARJOUEUR, pieceArrive->possesseur->listePiece, pieceArrive);
	}

	/* La case d'arrivee est maintenant libre*/
	pieceDepart->posX = mouvement[0][1];  // on met a jours les coordonnees de la piece
	pieceDepart->posY = mouvement[1][1];
	caseArrive->contenu = pieceDepart;  // on met la piece dans la case d'arrive
	caseDepart->contenu = NULL;  // on l'enleve de la case de depart
}

/**
 * verifie les differentes fin possible, test tous les cas pour renvoyer la victoire d'un joueur si nescessaire
 * @param  terrain[TAILLETERRAIN][TAILLETERRAIN]  Le terrain, pour rechercher les pieces proches du roi, et les positions des pieces
 * @param  joueurActuel  Le joueur qui va jouer, pour pouvoir voir son roi
 * @param  joueurAdverse  Le joueur adverse et toutes ses pieces
 * @return  Le joueur qui gagne, ou NULL si personne ne gagne (donc la partie doit continuer)
 */
Joueur* testVictoire(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueurActuel, Joueur* joueurAdverse) {
	/* Initialisation */
	Joueur* gagnant = NULL;
	Piece* roiActuel;
	int curseur = 0;  // recuperation des pointeurs vers le roi
	while (joueurActuel->listePiece[curseur]->type != 'R') {  // on va parcourir jusqu'a trouver le roi actuel
		curseur ++;
	}
	roiActuel = joueurActuel->listePiece[curseur];
	Piece* capture = captureCase(joueurAdverse->listePiece, roiActuel->posX, roiActuel->posY);  // piece qui adverse qui menace le roi


	/* traitement */
	// cas ou le roi ne peut plus bouger et qu'il est en echec
	if (roiActuel->mouvementPossible == NULL && capture != NULL) {  // echec classique, plus de mouvement pour le roi, et une piece qui le menace
		// on va regarder si une piece du joueur actuel peut prendre la piece qui met en echec le roi
		Piece* priseCapture = captureCase(joueurActuel->listePiece, capture->posX, capture->posY);
		if (priseCapture == NULL) {  // cas dans lequel rien ne peut venir prendre la piece menaçant le roi
			gagnant = joueurAdverse;

			// il faudrait regarder s'il n'est pas possible de mettre une piece dans la trajectoire de la menace
		}
	}

	// cas ou il reste juste les deux rois, renvoi un pat
	if (joueurActuel->listePiece[0]->type == 'R' && joueurActuel->listePiece[1] == NULL && joueurAdverse->listePiece[0]->type == 'R' && joueurAdverse->listePiece[1] == NULL) {
		gagnant = initJoueur("pat", 3);  // on creer un nouveau joueur pour representer le pat, avec des parametres neutres
	}

	// cas ou le joueur qui va jouer (joueur actuel) ne peut pas jouer de coup en plus => il lui reste uniquement son roi et des pions qui sont coincé
	curseur = 0;
	int nmbMouvement = 0;
	while (joueurActuel->listePiece[curseur] != NULL && curseur < NMBPIECEPARJOUEUR) {  // on parcours toutes les pieces restantes
		Element* position = joueurActuel->listePiece[curseur]->mouvementPossible;
		while (position != NULL) {  // on parcours toutes les positions realisables par
			nmbMouvement ++;
			position = position->suivant;
		}
		curseur ++;
	}
	if (nmbMouvement == 0) {
		// cas d'un pat
		gagnant = initJoueur("pat", 3);  // on creer un nouveau joueur pour representer le pat, avec des parametres neutres
	}

	return gagnant;
}
