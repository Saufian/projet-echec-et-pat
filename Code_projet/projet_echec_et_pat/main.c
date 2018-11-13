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

/* Debut du projet scolaire pour faire un jeu d'echec
avec affichage sur le terminal*/


/* Mettre tout les #include pour les headers ici*/

#include "initJeu.h"


/* Fonction main*/

int main() {
    /* Initialisation des variables*/
    Case terrain [TAILLETERRAIN][TAILLETERRAIN];
    Joueur* joueur1;
    joueur1 = initJoueur("joueur1", 1);  // creation du joueur1
    Joueur* joueur2;
    joueur2 = initJoueur("joueur2", 0);  // creation du joueur2
    initJeu(terrain, joueur1, joueur2);  // initialisition du terrain

    /* test du menu*/
    affichageMenu(terrain, joueur1, joueur2);

    return 0;
}
