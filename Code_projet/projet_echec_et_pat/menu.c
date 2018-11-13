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
                printf("Le gagnant est %s", gagnant->nom);  // affichage victoire
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
                affichageCharger();
                break;
            case 5:
                /*Stats*/
                afficherStats();
                break;
            case 6:
                /*Ouvre le menu crédit*/
                afficherCredits();
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


void affichageCharger()
{
    printf("           *********************\n\
           * REVOIR UNE PARTIE *\n\
           *********************\n\n");

    //Ici il y aura le "nom" des parties
    printf("WORK IN PROGRESS\n\n");
    printf("0 - Retour au menu");
    printf("\n\nChoisissez parmi les parties suivantes :");
    /*int choix = -1;
    switch (choix)
    {
    case 1:
        //Jouer la partie 1
        break;
    case 2:
        //Jouer la partie 2
        break;
    }*/
}

void afficherStats()
{
    printf("           **************\n\
           * STATISQUES *\n\
           **************\n\n");
    printf("WORK IN PROGRESS");

}

void afficherCredits()
{
    printf("           ***********\n\
           * CREDITS *\n\
           ***********\n\n");

    printf("School project, creation of a chess game in C, and with the content in French, I'm sorry about that.\n\
 Copyright (C), 2018,  Thomas Bailleux, Vincent Gauweiler, Antoine Ruiz, from EILCO France.\n\
 This program is free software: you can redistribute it and/or modify\n\
 it under the terms of the GNU General Public License as published by\n\
 the Free Software Foundation, either version 3 of the License, or\n\
 (at your option) any later version.\n\n\
 This program is distributed in the hope that it will be useful,\n\
 but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
 GNU General Public License for more details.\n\n\
 You should have received a copy of the GNU General Public License\n\
 along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n");
    printf("\nTapez 1 pour continuer ");
    char choix = '0';
    while (choix != '1')
    {
        scanf("%c", &choix);
    }
}

void afficherPause()
{
    printf("           *********\n\
           * PAUSE *\n\
           *********\n\n");
    printf("           1 - Reprendre la partie\n\n\
           2 - Revoir les instructions\n\n\
           3 - Sauvegarder et quitter\n\n\
           Votre choix : ");

}

void afficherInstructions()
{
    printf("           ****************\n\
           * INSTRUCTIONS *\n\
           ****************\n\n");
    printf("WORK IN PROGRESS");
    printf("Tapez 1 pour continuer");
    char choix = '0';
    while (choix != '1')
    {
        scanf("%c", &choix);
    }

}

