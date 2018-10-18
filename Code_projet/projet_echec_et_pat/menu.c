/* menu.c
va contenir les fonction relatives aux menus (principale et options)
*/

#include "initJeu.h"


void affichageMenu()
{
    printf("Menu Echec Simulator 2018\n\
        1 - Jouez\n\
        2 - Charger\n\
        3 - Options\n\
        4 - Credit\n\
        5 - Quitter\n");
    int choix = -1;
    while((choix!=1) && (choix!=2) && (choix!=3) && (choix!=4) && (choix!=5))/*Quitte le menu si un choix
    valide est fait*/
    {
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                /*Lance le jeu*/
                printf("Je lance le jeu\n");
                break;
            case 2:
                /*Ouvre un menu pour choisir une partie a charger*/
                printf("Allons charger une partie\n");
                break;
            case 3:
                /*Ouvre le menu options*/
                printf("Rien de mieux que de pimper sont jeu\n");
                break;
            case 4:
                /*Ouvre les credit*/
                printf("Vous avez dit qui?\n");
                break;
            case 5:
                /*Quitte le jeu*/
                printf("Au revoir et a bientot\n");
                break;
            default:
                /*Si l'utilisateur rentre autre chose*/
                printf("Ce choix n'existe pas\n");
                break;
        }
        printf("Je suis sortie du switch\n");
        printf("Choix : %d\n",choix);
    }
    printf("Je suis sortie de la boucle\n");
}
