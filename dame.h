#ifndef H_DAME
#define H_DAME

#include<stdio.h>
#include<stdlib.h>

#define PION_BLANC 2
#define DAME_BLANC 4
#define PION_NOIR 1
#define DAME_NOIR 3
#define CASE_VIDE 0
#define TAILLE_PLATEAU 10
#define JOUEUR_BLANC 0
#define JOUEUR_NOIR 1

typedef struct pion
{
    int x;
    int y;
}Pion;

typedef enum{false, true}Booleen;

void init_game(int plateau[]);
Pion choisir_pion();
Booleen verif_coup(int plateau[], Pion p, Pion p_dest);
void jouer_coup(int plateau[], int joueur);
Booleen game_over(int plateau[]);
void afficher_plateau(int plateau[]);


static int nb_noir = 20;
static int nb_blanc = 20;


#endif
