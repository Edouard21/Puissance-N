//
// Created by eliot on 23/05/2021.
//

#ifndef REPUISSANCEN_JEU_H
#define REPUISSANCEN_JEU_H

///définition de la taille de la grille
typedef struct{
    char** grille;
    int hauteur;
    int largeur;
}Grid;

///question de démarage d'une partie
void new_game(int *n_j, int *j);

///création de la taille de la grille souhaitée
void show_grid(Grid *g1, int n_j);

///Placement du jeton
int add_token(Grid* g1, int c, char jt);

int remove_token(Grid *g1, int c);

void show_new_grid(Grid *g1);

int check_direction(Grid *grille,int ligne,int colonne,int dir_x,int dir_y,char token);

int check_winner(Grid *grille, char token, int j);

#endif //REPUISSANCEN_JEU_H
