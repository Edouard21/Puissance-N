#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "jeu.h"

int main() {

    srand(time(NULL));

    int debut = 0;
    int nb_jetons = 0;  ///nombre de jetons à aligner pour gagner
    Grid g1;
    int action=0;
    int choix_action=0;
    int c;
    char jt;
    int j = 0;

    printf("Bienvenue dans notre jeu: PuissanceN !\n");

    do{
        printf("Que voulez-vous faire ? (tapez le chiffre correspondant a l'action voulu)\n\t1- Demarrer une nouvelle partie\n\t2- Charger une partie existante\n\t3- Quitter\n");
        scanf("%d", &debut);
    }while(debut != 1 && debut != 2 && debut != 3);

    if (debut == 3){

        return 0;

    }else if (debut == 1) {

        new_game(&nb_jetons, &j);

        show_grid(&g1, nb_jetons);

        for (int i = 0; i < g1.largeur; i++) {
            while (choix_action == 0) {
                for (int k = 0; k < g1.hauteur; k++) {
                    if (strcmp(&g1.grille[i][k], "_") == 1) {
                        choix_action = 1;
                    }
                }
            }
        }

        do {
            if (choix_action == 1) {
                do {
                    printf("Choisissez une action:\n\t1- Ajouter un jeton\n\t3- Sauvegarder et quitter\n");
                    scanf("%d", &action);
                } while (action != 1 && action != 3);
            } else {
                do {
                    printf("Choisissez une action:\n\t1- Ajouter un jeton\n\t2- Retirer un jeton\n\t3- Sauvegarder et quitter\n");
                    scanf("%d", &action);
                } while (action != 1 && action != 2 && action != 3);
            }

            choix_action = 0;

            if (action == 1) {

                do {
                    do {
                        printf("Dans quelle colonne voulez-vous placer votre jeton ? (entre 1 et %d)\n", g1.largeur);
                        scanf("%d", &c);
                        c = c - 1;
                    } while (c > g1.largeur || c < 0);    ///vérifie que l'utilisateur entre bien une valeur acceptable

                    if (j % 2 == 0) {    ///Savoir qui à joué
                        jt = 'X';
                    } else {
                        jt = 'O';
                    }

                } while (add_token(&g1, c, jt) == 0);    ///recommence tant que l'utilisateur choisi une colonne pleine

                show_new_grid(&g1);

                j++;

            }else if (action == 2){

                do {
                    do {
                        printf("Dans quelle colonne voulez-vous retirer un jeton ? (entre 1 et %d)\n", g1.largeur);
                        scanf("%d", &c);
                        c = c - 1;
                    } while (c > g1.largeur || c < 0);    ///vérifie que l'utilisateur entre bien une valeur acceptable

                } while (remove_token(&g1, c) != 1);    ///recommence tant que l'utilisateur choisi une colonne pleine

                show_new_grid(&g1);

                j++;
            }
        } while (action != 3 && check_winner(&g1, jt, j) != 1);
    }


    for(int i = 0; i<g1.largeur; i++) {

        free(g1.grille[i]);
        g1.grille[i] = NULL;
    }

    free(g1.grille);
    g1.grille = NULL;

    return 0;
}
