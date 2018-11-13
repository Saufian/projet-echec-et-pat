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

/*save.c
Partie qui se charge de la sauvegarde
*/
#include "initJeu.h"

/**
 * initialise le fichier save de la partie avec le pseudo des 2 joueur
 * @param  joueur1 Le joueur 1
 * @param  joueur2 Le joueur 2
 * @return         pointeur vers le fichier a manipuler tous du long de la partie
 */
FILE * initSaveGame(Joueur* joueur1, Joueur* joueur2)
{
	FILE* saveFile;
    saveFile=fopen("savefile.save","w");
	fwrite(joueur1->nom, sizeof(char), strlen(joueur1->nom)+1,saveFile);
	fprintf(saveFile, " ");
	fwrite(joueur2->nom, sizeof(char), strlen(joueur2->nom)+1,saveFile);
	fprintf(saveFile, "\n");
	return saveFile;
}

/**
 * sauvegarde les deplacement des pions dans le fichier format : OldX OldY NewX NewY
 * @param  saveFile pointeur vers le fichier ouvert actuellement
 * @param  commande les mouvements réaliser
 * @return         le fichier a manipuler tous du long de la partie
 */
FILE * saveGame(FILE * saveFile, int commande[2][2])
{
	fprintf(saveFile, "%d %d %d %d\n",commande[0][0], commande[1][0], commande[0][1], commande[1][1]);
	return saveFile;
}

/**
 * ferme le fichier de sauvegarde et les enregistre dans le fichier
 * @param saveFile pointeur vers le fichier ouvert actuellement
 */
void closeSaveGame(FILE * saveFile)
{
	fprintf(saveFile, "%s\n","TIMEUP");
	fclose(saveFile);
}
