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
	FILE * saveFile=initSaveGame(joueur1,joueur2);//On initialise le fichier de sauvgarde todo:lui donner un nom different par partie pour stocker différente partie
	/* fonction principale pour le jeux a 2 joueurs*/
	Joueur* gagnant = NULL;
	Joueur* joueurActuel = joueur1;
	int mouvement[2][2];
	/* calcul des positions pour le joueur 1*/
	calculMouvement(joueur1->listePiece, terrain);
	calculMouvement(joueur2->listePiece, terrain);

	while(gagnant == NULL) {
		scanDeuxJoueurs(terrain, joueurActuel, mouvement);
		saveGame(saveFile,mouvement);//je sauvegarde le déplacement OldX OldY NewX NewY
		printf("%d,%d,  %d,%d", mouvement[0][0], mouvement[1][0], mouvement[0][1], mouvement[1][1]);
		deplacementPiece(terrain, mouvement);
		calculMouvement(joueur1->listePiece, terrain);  // on recalcul les mouvements des pieces pour
		calculMouvement(joueur2->listePiece, terrain);  // que ce soit a jour pour le test de victoire
		affichageTerrain(terrain);  // on affiche le terrain avec la modification de la position
		//gagnant = testVictoire(terrain, joueur1, joueur2);
		if (joueurActuel == joueur1) joueurActuel = joueur2;
		else joueurActuel = joueur1;
		closeSaveGame(saveFile); //gagnant ne fonctionnent pas encore je dois fermer le fichier plus tôt
	}
	//closeSaveGame(saveFile); // sera actif quand il y aura un gagnant
	return gagnant;
}


void affichageTerrain(Case terrain[TAILLETERRAIN][TAILLETERRAIN]) {
	/* Initialisation */
	int curseurY, curseurX, compteur;
	compteur = TAILLETERRAIN*TAILLETERRAIN + TAILLETERRAIN;  // on met en place la variable qui sert a afficher le numero de la ligne
	/* Vidage de l'ecran */
	for(int i = 0; i < 40; i++) {
        printf("\n");  // On affiche du blanc
	}
	/* Affichage */
	printf("\n\n   A      B      C      D      E      F      G      H \n" );  // affi
	for (curseurY = 0; curseurY < TAILLETERRAIN; curseurY++) {  //Parcours des lignes
		printf(" _____  _____  _____  _____  _____  _____  _____  _____ \n" );  // affichage de la partie superieure des cases
		printf("|     ||     ||     ||     ||     ||     ||     ||     |\n" );
		for (curseurX = 0; curseurX < TAILLETERRAIN; curseurX++) {  // on parcours les colonnes
			compteur--;
			if ( compteur % TAILLETERRAIN == 0 && terrain[curseurX][TAILLETERRAIN-1 - curseurY].contenu != NULL) {
				//Test Pour case non vide sur la derniere colonne
				printf("|  %c  |  %d  ",terrain[curseurX][TAILLETERRAIN-1 - curseurY].contenu->type, compteur / TAILLETERRAIN);
			}
			else if ( compteur % TAILLETERRAIN == 0 && terrain[curseurX][TAILLETERRAIN-1 - curseurY].contenu == NULL) {
				// Test pour case vide sur la derniere colonne
				if (terrain[curseurX][TAILLETERRAIN-1 - curseurY].surbrillance == 1) {
					printf("|  *  |  %d  ", compteur / TAILLETERRAIN);
				}
				 else printf("|     |  %d  ", compteur / TAILLETERRAIN);
			}
			else if (terrain[curseurX][TAILLETERRAIN-1 - curseurY].contenu == NULL) {  // Test case vide quelconque
				if (terrain[curseurX][TAILLETERRAIN-1 - curseurY].surbrillance == 1) {  // test de surbrillance
					printf("|  *  |");
				}
				 else printf("|     |");  // affichage case vide
			}
			else {
				printf("|  %c  |", terrain[curseurX][TAILLETERRAIN-1 - curseurY].contenu->type);
			}
		}
		printf("\n|_____||_____||_____||_____||_____||_____||_____||_____|\n" );  // affichage de la partie inferieure des cases
	}
	printf("\n   A      B      C      D      E      F      G      H \n" );  // legende et affichage de la derniere ligne.
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
	if (liste != NULL) {  // On fait attention au cas ou la liste est vide
		Element* curseur = liste;
		while (curseur != NULL) {  // on parcours la liste
			terrain[curseur->posX][curseur->posY].surbrillance = 1;  // on met la case choisie en surbrillance
			curseur = curseur->suivant;
		}
	}
}

void scanDeuxJoueurs(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueurActuel, int commande[2][2]) {
	/* Initialisation des variables */
	int posX;
	int posY;
	int boucle = 0;  // pour permettre au joueur de changer son choix de piece
	Piece* selection;

	/* initialisation des cases du tableau commandes */
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			commande[i][j] = 0;
		}
	}
	/* Interraction 1 avec le joueur
	 * Demande de la piece a bouger
	 */
	do {  // on recommence le choix tant que le joueur le veut
		boucle = 0;  // on remet boucle a 0 pour ne pas faire de boucles infinies

		/* On affiche le terrain en enlevant les cases qui auraient pu etre selectionne avant */
		gestionSurbrillance(terrain, NULL);  // on enleve la surbrillance
		affichageTerrain(terrain);
		do {
			do {
				printf("Quelle piece voulez vous bouger ?\n");
				printf("Valeur X de la piece : ");
				scanf("%d", &posX);
				printf("Valeur Y de la piece : ");
				scanf("%d", &posY);
				if ((posX < 0 || posX >= TAILLETERRAIN || posY < 0 || posY >= TAILLETERRAIN || terrain[posX][posY].contenu == NULL)) {
					printf("Aucune piece ici, recommencez.\n\n");
				}
				else {
					if (terrain[posX][posY].contenu->possesseur->couleur != joueurActuel->couleur) {  // piece de la mauvaise couleur
						printf("Piece de la mauvaise couleur, recommencez.\n\n");
					}
				}

			} while (posX < 0 || posX >= TAILLETERRAIN || posY < 0 || posY >= TAILLETERRAIN || terrain[posX][posY].contenu == NULL);
		} while (terrain[posX][posY].contenu->possesseur->couleur != joueurActuel->couleur);
		selection = terrain[posX][posY].contenu;
		gestionSurbrillance(terrain, selection->mouvementPossible);
		affichageTerrain(terrain);
		/* on met les donnees dans commande*/
		commande[0][0] = posX;
		commande[1][0] = posY;

		/* Interraction 2 avec le joueur
		 * On lui demande la nouvelle position de la piece
		 */
		do {
			printf("\nOu voulez vous bouger cette piece ( %c )?  (ou %d,%d pour revenir a la selection de piece)\n",
			 selection->type, TAILLETERRAIN, TAILLETERRAIN);
			printf("Nouvelle valeur en X : ");
			scanf("%d", &posX);
			printf("Nouvelle valeur en Y : ");
			scanf("%d", &posY);
			if (trouveElement(selection->mouvementPossible, posX, posY) == 0 && (posX != TAILLETERRAIN && posY != TAILLETERRAIN)) {
			// situation ou l'on va boucler
				printf("Mouvement impossible, veuillez reessayer.\n\n");
			}
			if (posX == TAILLETERRAIN && posY == TAILLETERRAIN) {  // cas ou l'utilisateur veut changer de piece
				boucle = 1;  // on met boucle a 1 pour revenir au debut
			}
		} while(trouveElement(selection->mouvementPossible, posX, posY) == 0 && (posX != TAILLETERRAIN && posY != TAILLETERRAIN));
	} while (boucle == 1);  // on renvoi si l'utilisateur veut changer de piece
	commande[0][1] = posX;
	commande[1][1] = posY;  // on stock dans le tableau avant de le renvoyer
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


/* TODO
Joueur* testVictoire(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2);

*/
