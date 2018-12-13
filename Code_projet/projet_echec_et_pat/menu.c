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
    char choix = '8';
    while(choix != '0')  {
        if (choix >= '0' && choix <='8')
        {
         printf("\n\n\n\n\
        *****************************\n\
        * Menu Echec Simulator 2018 *\n\
        *****************************\n\n\n\
            1 - Mode 2 joueurs\n\n\
            2 - Mode 1 joueur (VS Ordi)\n\n\
            3 - Continuer une partie\n\n\
            4 - Revoir une partie\n\n\
            5 - Regles\n\n\
            6 - Statistiques\n\n\
            7 - Credits\n\n\
            0 - Quitter\n\n\
        Il est recommande d'agrandir la fenetre avant de lancer une partie\n\n\
        Votre choix ? ");
        }
        /*Quitte le menu si un choix valide est fait (a moins que l'on ne le quitte avec l'un des return)*/

        scanf("%c%*1[\n]",&choix);
        switch(choix)
        {
            case '1':
                /*Mode 2 joueur*/
                afficherRegles();
                afficherInstructions();
                printf("Bonne partie\n");
                initSaveGame(joueur1,joueur2);//On initialise le fichier de sauvgarde todo:lui donner un nom different par partie pour stocker différente partie
                Joueur* gagnant;
                gagnant = partieDeuxJoueurs(terrain, joueur1, joueur2);  // renvoi le gagnant de la partie
                printf("Le gagnant est %s", gagnant->nom);  // affichage victoire
                break;
            case '2':
                /*Mode 1 joueurs contre l'ordi*/
                afficherRegles();
                afficherInstructions();
                printf("Work in progress\n");
                break;
            case '3':
                /*Continue la partie*/
                printf("Work in progress\n");
                printf("on charge la partie\n");
                loadSaveGame(joueur1, joueur2);
                printf("La partie %s vs %s va reprendre\n", joueur1->nom,joueur2->nom );
                readMove(terrain);//on charge le terrain actuelle
                printf("The Game is on !\n");
                gagnant = partieDeuxJoueurs(terrain, joueur1, joueur2);
                break;
            case '4':
                /*Ouvre le menu pour revoir une partie*/
                affichageCharger();
                break;
            case '5':
                //Affiche les regles
                afficherRegles();
                break;
            case '6':
                /*Stats*/
                afficherStats();
                break;
            case '7':
                /*Ouvre le menu crédit*/
                afficherCredits();
                break;
            case '0':
                /*Quitte*/
                system("cls");
                printf("Au revoir et a bientot\n");
                break;
            default:
                /*Si l'utilisateur rentre autre chose*/
                printf("Votre choix precedent ne correspond pas, veuillez recommencer.\n");
                break;
        }
    }
}


void affichageCharger()
{
    system("cls");
    printf("           *********************\n\
           * REVOIR UNE PARTIE *\n\
           *********************\n\n");

    //Ici il y aura le "nom" des parties
    printf("WORK IN PROGRESS\n\n");
    printf("0 - Retour au menu");
    printf("\n\nChoisissez parmi les parties suivantes :");
    char choix = '$';
    /*switch (choix)
    {
    case 1:
        //Jouer la partie 1
        break;
    case 2:
        //Jouer la partie 2
        break;
    }*/
    while (choix != '0')
    {
        scanf("%c%*1[\n]", &choix);
    }
    system("cls");
}

void afficherStats()
{
    system("cls");
    printf("           **************\n\
           * STATISQUES *\n\
           **************\n\n");
    printf("WORK IN PROGRESS");
    printf("\n\nTapez 1 pour sortir");
    char choix = '0';
    while (choix != '1')
    {
        scanf("%c%*1[\n]", &choix);
    }
    system("cls");
}

void afficherCredits()
{
    system("cls");
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
        scanf("%c%*1[\n]", &choix);
    }
    system("cls");
}

void afficherPause()
{
    system("cls");
    printf("           *********\n\
           * PAUSE *\n\
           *********\n\n");
    printf("           1 - Reprendre la partie\n\n\
           2 - Revoir les instructions\n\n\
           3 - Revoir les regles\n\n\
           0 - Sauvegarder et quitter\n\n\
           Votre choix : ");
    char choix ='$';
    while(choix != '1')
    {
      scanf("%c%*1[\n]", &choix);
      switch(choix)
      {
        case '1' : {printf("La partie reprend");break;}
        case '2' : {afficherInstructions(); break;}
        case '3' : {afficherRegles();break;}
        default : {printf("Choix indisponible");break;}
      }
    }
    system("cls");
}

void afficherInstructions()
{
    system("cls");
    printf("           ****************\n\
           * INSTRUCTIONS *\n\
           ****************\n\n");
    printf("WORK IN PROGRESS");
    printf("\n\nTapez 1 pour continuer");
    char choix = '0';
    while (choix != '1')
    {
        scanf("%c%*1[\n]", &choix);
    }
    system("cls");
}

void afficherRegles()
{
    system("cls");
    printf("           **********\n\
           * REGLES *\n\
           **********\n\n");
    printf("    Le jeu se pratique sur un plateau compose de 64 cases dont 32 de couleur blanche et 32 de couleur noire. La case inferieure droite, face aux joueurs, doit toujours etre blanche. Notons egalement que la dame se trouve toujours sur la case de sa couleur.\n\n\
    LE BUT DU JEU :\n\
    Le but de ce jeu est de prendre le roi adverse. Lorsque ce but est atteint, le joueur qui y est parvenu gagne immediatement la partie qui prend fin automatiquement.\n\n\
    LE DEROULEMENT DU JEU :\n\
    Au debut de d'une partie, ce sont toujours les blancs qui commencent. Lors d'un tour, le joueur peut effectuer soit un deplacement, soit une prise soit un coup special.\n\n\
    ECHEC :\n\
    Chaque fois que vous pouvez prendre le roi de votre adversaire a votre prochain coup, vous devez le prevenir en annoncant \"echec\". Il doit alors tenter de parer votre echec, lors de son tour de jeu.\n\n\
    ECHEC ET MAT :\n\
    S'il n'y parvient pas, son roi est alors  \"echec et mat\". Vous remportez donc la partie.\n\n\
    PAT :\n\
    Une partie d'echecs peut egalement se terminer sur un match nul. Si lors du tour d'un joueur, celui-ci ne peut deplacer aucune de ses pieces et que son roi n'est pas en echec. On dit alors que la partie se termine par un \" pat \".\n\n\
    LES DEPLACEMENTS DES PIECES :\n\n\
    Le Pion :\n\
    Le pion avance uniquement devant lui d'une seule case. Lors de son premier deplacement, il peut exceptionnellement avancer d'une ou de deux cases. Pour prendre une piece ennemie, il se deplace seulement en diagonale d'une seule case.\n\n\
    La Tour : \n\
    La tour se deplace horizontalement ou verticalement d'autant de cases que vous le souhaitez.\n\n\
    Le Cavalier (ou cheval) :\n\
    Le cavalier saute par dessus les cases qui entourent sa position initiale (meme s'il y a des pieces du meme joueur) pour se poser sur une des cases de couleur opposee la plus proche. Son mouvement represente 2 cases dans un sens puis 1 dans un autre sens.\n\n\
    Le Fou :\n\
    Le fou se deplace diagonalement d'autant de cases que vous le souhaitez.\n\n\
    La Dame (ou reine) :\n\
    La dame se deplace diagonalement, horizontalement et verticalement d'autant de cases que vous le souhaitez. Elle combine les mouvements du Fou et de la Tour.\n\n\
    Le Roi :\n\
    Le roi se deplace sur n'importe quelle case adjacente a sa position initiale.\n\n\
    LES COUPS SPECIAUX :\n\n\
    Le roque :\n\
    Le roque permet de deplacer le roi de 2 cases vers la tour et de positionner la tour en question derriere le roi. Il ne peut plus etre effectue si le roi ou la tour ont deja bouge. Il est momentanement empeche si le roi est echec ou s'il y a des pieces entre le roi et la tour.\n\n\
    La promotion :\n\
    Quand un pion parvient jusqu'a la range la plus proche du joueur adverse, il se transforme en dame, en tour, en fou ou en cavalier. La piece promue est immediatement operationnelle.\n\n\
    La prise en passant :\n\
    Lorsqu'un pion atteint la cinquieme rangee pour les blancs ou la quatrieme pour les noirs, il peut \"prendre en passant\" un pion adverse qui avance de deux pas sur une colonne immediatement voisine.\n\n\
    Les regles seront accessibles a tout moment dans le menu pause pendant la partie.");
    printf("\n\nTapez 1 pour continuer");
    char choix = '0';
    while (choix != '1')
    {
        scanf("%c%*1[\n]", &choix);
    }
    system("cls");
}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


void afficherLigne(Case terrain[TAILLETERRAIN][TAILLETERRAIN], int PosY, int compteur)
{
    int petiteLigne, PosX;
    for (petiteLigne=0; petiteLigne<3; petiteLigne++)
    {
        printf("  ");
        if (petiteLigne==1)
        {
            for (PosX=0; PosX<TAILLETERRAIN; PosX++)
            {
                if (terrain[PosX][TAILLETERRAIN-1 - PosY].contenu != NULL)
                {
                    if (terrain[PosX][TAILLETERRAIN-1 - PosY].couleur == 1)
                    {
                        if (terrain[PosX][TAILLETERRAIN-1 - PosY].contenu->possesseur->couleur == 1)
                            {Color(15, 8); printf("   %c   ",terrain[PosX][TAILLETERRAIN-1 - PosY].contenu->type);Color(15, 0);}
                        else
                            {Color(0, 8); printf("   %c   ",terrain[PosX][TAILLETERRAIN-1 - PosY].contenu->type);Color(15, 0);}

                    }else
                    {
                        if (terrain[PosX][TAILLETERRAIN-1 - PosY].contenu->possesseur->couleur == 1)
                            {Color(15, 4); printf("   %c   ",terrain[PosX][TAILLETERRAIN-1 - PosY].contenu->type);Color(15, 0);}
                        else
                            {Color(0, 4); printf("   %c   ",terrain[PosX][TAILLETERRAIN-1 - PosY].contenu->type);Color(15, 0);}
                    }
                }else
                {
                    if (terrain[PosX][TAILLETERRAIN-1 - PosY].couleur == 1)
                        {Color(0, 8); printf("       ");Color(15, 0);}
                    else
                        {Color(0, 4); printf("       ");Color(15, 0);}
                }
            }
            printf("  %d", compteur);
            compteur--;
            printf("  \n");
        }else
        {
            for (PosX=0; PosX<TAILLETERRAIN; PosX++)
            {
                if (terrain[PosX][TAILLETERRAIN-1 - PosY].couleur == 1)
                    {Color(0, 8); printf("       ");Color(15, 0);}
                else
                    {Color(0, 4); printf("       ");Color(15, 0);}
            }
            printf("  \n");
        }
    }
}
