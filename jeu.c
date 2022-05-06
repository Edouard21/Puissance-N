//
// Created by edouard on 23/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "jeu.h"

void new_game(int *n_j, int *j){

    int nb_joueur = 0;
    int couleur_joueur;    ///choix de la couleur du joueur qui commence
    char j1[6], j2[6];

    do {
        printf("Nouvelle partie:\nCombien de joueurs joueront ? (1 ou 2)\n");
        scanf("%d", &nb_joueur);
    } while (nb_joueur != 1 && nb_joueur != 2);

    do {
        printf("Combien de jetons N devront-etre alignes pour gagner ? (entre 3 et 10)\n");
        scanf("%d", n_j);
    } while (*n_j < 3 || *n_j > 10);


    couleur_joueur = rand() % 2;

    if (couleur_joueur == 1) {
        strcpy(j1, "Rouge");
        strcpy(j2, "Jaune");
    } else {
        strcpy(j1, "Jaune");
        strcpy(j2, "Rouge");
        *j = 1;
    }

    if (nb_joueur == 1) {
        printf("\n//\tLe joueur 1 aura la couleur %s.\t//\n//\tL'ordinateur aura la couleur %s.\t//\n\nLe joueur 1 commence.\n", j1, j2);
    } else if (nb_joueur == 2) {
        if (*j == 0){
            printf("\n//\tLe joueur 1 aura la couleur %s et le jeton 'X'.\t//\n//\tLe joueur 2 aura la couleur %s et le jeton 'O'.\t//\n\nLe joueur 1 commence.\n", j1, j2);

        }else{
            printf("\n//\tLe joueur 1 aura la couleur %s et le jeton 'O'.\t//\n//\tLe joueur 2 aura la couleur %s et le jeton 'X'.\t//\n\nLe joueur 1 commence.\n", j1, j2);
        }
    }

}

void show_grid(Grid *g1, int n_j){
    g1->hauteur = n_j + 2;
    g1->largeur = n_j + 2;

    g1->grille = (char**) malloc(sizeof(int*) * g1->largeur);

    printf("\n(numero des colonnes)\n");
    for(int a = 0; a< g1->largeur; a++) {
        printf("%d. ",a+1);
    }

    printf("\n");
    for(int i = 0; i < g1->largeur; i++) {

        g1->grille[i] = (char*) malloc(sizeof(int) * g1->hauteur);

        printf("\n");

        for(int j = 0; j< g1->hauteur; j++) {

            strcpy(&g1->grille[i][j], "_");
            printf("%c  ", g1->grille[i][j]);
        }
    }

    printf("\n\n");
}


int add_token(Grid* g1, int c, char jt){

    int a=0;

    if(g1->grille[c][0] == '_'){   ///vérification colonne pleine
        while(a < g1->hauteur && g1->grille[c][a] == '_'){
            a++;
        }
        g1->grille[c][a-1] = jt;
        return 1;
    }else{
        printf("La colonne choisi est pleine.\n");
        return 0;
    }
}

int remove_token(Grid *g1, int c){

    int a=0;
       ///vérification colonne pleine ou vide
        while(a < g1->hauteur && g1->grille[c][a] == '_'){
            a++;
        }
        if(a < g1->hauteur){
        g1->grille[c][a] = '_';
        return 1;
         }else{
             printf("La colonne choisi est vide.\n");
             return 0;
         }
     }

void show_new_grid(Grid *g1){

         printf("\n");
         for(int i = 0; i< g1->hauteur; i++) {
             printf("%d. ",i+1);
         }

         printf("\n");
         for(int z = 0; z < g1->hauteur; z++) {
             printf("\n");
             for(int e = 0; e< g1->largeur; e++) {
                 printf("%c  ", g1->grille[e][z]);
             }
         }

         printf("\n\n");

}

int check_direction(Grid *g1,int ligne,int colonne,int dir_x,int dir_y,char token) {
    int compteur=0;


    if(dir_x==0 && dir_y==0){
    return 0;
    }

    while(ligne<g1->hauteur && ligne>=0 && colonne>=0 && colonne<g1->largeur && g1->grille[ligne][colonne]== token && compteur<g1->hauteur-2 ){
        compteur++;
        ligne= ligne+ 1*dir_y;
        colonne= colonne+1*dir_x;
    }

    if(compteur==g1->hauteur-2){
        return 1;
    }else{
        return 0;
    }


}

int check_winner(Grid *grille, char token, int j){

    for(int k=0; k < grille->largeur; k++) {
        for(int l= 0; l < grille->hauteur; l++){
            if(grille->grille[k][l] != '_'){
                for (int i = -1; i <= 1; i++) {
                    for (int b = -1; b <= 1; b++) {
                        if(check_direction(grille, k, l, i, b, grille->grille[k][l]) == 1 && grille->grille[k][l] == token){
                            if(j-1 % 2 == 0){
                                printf("//\tLe joueur 1 avec le jeton %c a gagne.\t//\n", token);
                            }else{
                                printf("//\tLe joueur 2 avec le jeton %c a gagne.\t//\n", token);
                            }

                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
