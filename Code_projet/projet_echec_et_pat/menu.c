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

/* menu.c
va contenir les fonction relatives aux menus (principale et options)
*/

#include "initJeu.h"


void affichageMenu(Case terrain[TAILLETERRAIN][TAILLETERRAIN], Joueur* joueur1, Joueur* joueur2)
{
    int choix = -1;
    while(choix != 7)  {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
        *****************************\n\
        * Menu Echec Simulator 2018 *\n\
        *****************************\n\n\n\
            1 - Mode 2 joueurs\n\n\
            2 - Mode 1 joueur (VS Ordi)\n\n\
            3 - Continuer une partie\n\n\
            4 - Revoir une partie\n\n\
            5 - Statistiques\n\n\
            6 - Credits\n\n\
            7 - Quitter\n\n\n\
        Votre choix ?  ");

        /*Quitte le menu si un choix valide est fait (a moins que l'on ne le quitte avec l'un des return)*/

        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                /*Mode 2 joueur*/
                printf("Bonne partie\n");
                Joueur* gagnant;
                gagnant = partieDeuxJoueurs(terrain, joueur1, joueur2);  // renvoi le gagnant de la partie
                // affichage victoire
                break;
            case 2:
                /*Mode 1 joueurs contre l'ordi*/
                printf("Work in progress\n");
                break;
            case 3:
                /*Continue la partie*/
                printf("Work in progress\n");
                break;
            case 4:
                /*Ouvre le menu pour revoir une partie*/
                printf("Work in progress\n");
                break;
            case 5:
                /*Stats*/
                printf("Work in progress");
                break;
            case 6:
                /*Ouvre le menu crédit*/
                printf("Work in progress");
                break;
            case 7:
                /*Quitte*/
                printf("Au revoir et a bientot\n");
                break;
            default:
                /*Si l'utilisateur rentre autre chose*/
                printf("\n\nVotre choix precedent ne correspond pas, veuillez recommencer.\n");
                break;
        }
    }
}
