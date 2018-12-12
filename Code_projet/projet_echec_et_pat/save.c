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
void initSaveGame(Joueur* joueur1, Joueur* joueur2)
{
	FILE* saveFile;
    saveFile=fopen("savefile.save","w");
	fwrite(joueur1->nom, sizeof(char), strlen(joueur1->nom),saveFile);
	fprintf(saveFile, "\n");
	fwrite(joueur2->nom, sizeof(char), strlen(joueur2->nom),saveFile);
	fprintf(saveFile, "\n");
	fclose(saveFile);
}

/**
 * sauvegarde les deplacement des pions dans le fichier format : OldX OldY NewX NewY
 * @param  saveFile pointeur vers le fichier ouvert actuellement
 * @param  commande les mouvements réaliser
 * @return         le fichier a manipuler tous du long de la partie
 */
void saveGame(int commande[2][2])
{
    FILE* saveFile;
    saveFile=fopen("savefile.save","a");
	fprintf(saveFile, "%d%d%d%d",commande[0][0], commande[1][0], commande[0][1], commande[1][1]);
	fclose(saveFile);
}

/**
 * ferme le fichier de sauvegarde et les enregistre dans le fichier
 * @param saveFile pointeur vers le fichier ouvert actuellement
 */
void closeSaveGame()
{
    FILE* saveFile;
    saveFile=fopen("savefile.save","a");
	fprintf(saveFile, "%s\n","TIMEUP");
	fclose(saveFile);
}

void loadSaveGame(Joueur* joueur1, Joueur* joueur2)
{
	FILE* saveFile;
    saveFile=fopen("savefile.save","a+");
    
    char *temp1=malloc(sizeof(25));
    char *temp2=malloc(sizeof(25));

    fgets(temp1,25,saveFile);//lis la ligne et la stock dans le pointeur
    fgets(temp2,25,saveFile);

    joueur1->nom=strtok(temp1,"\n");//retire le \n du nom
    joueur2->nom=strtok(temp2,"\n");

    fclose(saveFile);
}

int readMove(Case terrain[TAILLETERRAIN][TAILLETERRAIN])
{
    FILE* saveFile;
    int * mouvement[2][2];
    saveFile=fopen("savefile.save","a+");
    char temp;
    int compteur=0;
    while(compteur<3)
    {
        for (int i = 0; i < 2; ++i)//se deplace a la troisieme ligne
            {
                temp=fgetc(saveFile);
                printf("%c\n", temp);
                while(temp!='\n')
                {
                    temp=fgetc(saveFile);
                    printf("%c\n", temp);
                }
                ++compteur;
            }
        int c=0;
        while(c!=-1)
        {
            mouvement[0][0]=fgetc(saveFile)-'0';//oldX
            mouvement[1][0]=fgetc(saveFile)-'0';//oldY
            mouvement[0][1]=fgetc(saveFile)-'0';//NewX
            mouvement[1][1]=fgetc(saveFile)-'0';//NewY
            printf("%d,%d,  %d,%d\n", mouvement[0][0], mouvement[1][0], mouvement[0][1], mouvement[1][1]);
            deplacementPiece(terrain, mouvement);
            affichageTerrain(terrain);//afficher coup par coup
            c=fgetc(saveFile);
            fseek(saveFile,-1,SEEK_CUR);
            temp=fgetc(saveFile);
            fseek(saveFile,-1,SEEK_CUR);
        }
        ++compteur;
    }
    fclose(saveFile);
}

int readPastMove(int * mouvement[2][2])
{
    FILE* saveFile;
    saveFile=fopen("savefile.save","a+");
    int temp;
    for (int i = 0; i < 3; ++i)//se deplace a la fin de la 3eme ligne troisieme ligne
    {
        temp=fgetc(saveFile);
        //printf("%d\n", temp);
        while((temp!='\n')||(temp!=EOF))
        {
            temp=fgetc(saveFile);
            //printf("%d\n", temp);
            if (temp==EOF)
            {
                break;
            }
        }
    }
    fseek(saveFile,-4,SEEK_CUR);//on recule de 4
    int c;//on inverse les mouvements dans le tableau pour pouvoir facilement l'utiliser pour annuler sont mouvement
    mouvement[0][0]=fgetc(saveFile)-'0';//oldX
    mouvement[1][0]=fgetc(saveFile)-'0';//oldY
    mouvement[0][1]=fgetc(saveFile)-'0';//NewX
    mouvement[1][1]=fgetc(saveFile)-'0';//NewY
    printf("%d,%d,  %d,%d\n", mouvement[0][0], mouvement[1][0], mouvement[0][1], mouvement[1][1]);
    fseek(saveFile,-4,SEEK_CUR);//on recule de 4 pour ecrire par dessus
    fclose(saveFile);
}
