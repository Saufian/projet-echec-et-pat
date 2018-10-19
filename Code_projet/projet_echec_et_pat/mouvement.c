#include "initJeu.h"

void calculMouvement(Piece * listePieceJoueur,Case * terrain)
{
	if (listePieceJoueur==NULL)/* Si on a atteint la dernière pièces on retourne la 
	listePieceJoueur avec leur nouveaux mouvement*/
	{
		return listePieceJoueur;
	}
	char pion=listePieceJoueur->Piece->type;
	switch(pion)
	{
		case 'P':
		/*
		renvoie les position possible du pion +1 ou +2 si premier deplacement
		 */
		listePieceJoueur->Piece->mouvementPossible->posX=
		listePieceJoueur->Piece->mouvementPossible->posY=
		break;
		case 'T':
		break;
		case 'C':
		break;
		case 'F':
		break;
		case 'R':
		break;
		case 'D':
		break;
	}

}