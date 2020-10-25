#include "dame.h"


void init_game(int plateau[]){

    //créer les cases vides
    for (int i = 0; i < TAILLE_PLATEAU; i++)
    {
        for (int j = 0; j < TAILLE_PLATEAU; j++)
        {
            plateau[i*TAILLE_PLATEAU + j] = CASE_VIDE;
        }
    }
    
    //init les pions noires
    for(int i = 0; i < 4; i++)
    {
        for (int j = (i+1)%2; j < TAILLE_PLATEAU; j+=2)
        {
            plateau[i*TAILLE_PLATEAU + j] = PION_NOIR;
        }   
    }

    //créer les pions blancs
    for(int i = TAILLE_PLATEAU-1; i > TAILLE_PLATEAU-5; i--)
    {
        for (int j = (i+1)%2; j < TAILLE_PLATEAU; j+=2)
        {
            plateau[i*TAILLE_PLATEAU + j] = PION_BLANC;
        }
    }
}



Pion choisir_pion()
{
    Pion p;
    printf("\ncoordonnée X : ");
    scanf("%d", &p.x);
    while(p.x < 0 || p.x > 7)
    {
        printf("\nveuillez rentrer des coordonnées valides");
        scanf("%d", &p.x);
    }
    printf("\ncoordonnée Y : ");
    scanf("%d", &p.y);
    while(p.y < 0 || p.y > 7)
    {
        printf("\nveuillez entrer des coordonnées valides");
        scanf("%d", &p.y);
    }
    return p;
}

Booleen verif_coup(int plateau[], Pion p, Pion p_dest)
{
    if(p_dest.x%2 == p_dest.y%2)
    {
        printf("mouvement interdit : ce n'est pas un déplacement diagonal.\n");
        return false;
    }

    //vérifie qu'on ne dépasse pas la limite de déplacement des pions
    if (plateau[p.x*TAILLE_PLATEAU + p.y] == PION_BLANC || plateau[p.x*TAILLE_PLATEAU + p.y] == PION_NOIR)
    {
        //le joueur se déplace de 2 cases sur un coté => veut prendre un pion ennemi
        if(abs(p.y-p_dest.y) == 2)
        {
            //doit vérifier qu'il y a bien un pion ennemi entre le départ et l'arrivée.
        }

        //mettre la transformation en dame ici ?
    }
    
}

void jouer_coup(int plateau[], int joueur)
{
    Booleen verif = true;
    Pion p, p_dest;
    while(verif)
    {
        printf("chosir le pion à jouer.\n");
        p = choisir_pion();
        printf("x = %d, y = %d\n", p.x, p.y);
        while(plateau[p.x*TAILLE_PLATEAU + p.y]%2 != joueur || plateau[p.x*TAILLE_PLATEAU + p.y] == CASE_VIDE)
        {
            printf("\nVous devez choisir un pion qui vous appartient.\n");
            p = choisir_pion();
            printf("x = %d, y = %d\n", p.x, p.y);
        }

        printf("chosir la destination.\n");
        p_dest = choisir_pion();
        while (plateau[p_dest.x*TAILLE_PLATEAU + p_dest.y] != CASE_VIDE)
        {
            printf("choisir une destination valide\n");
            p_dest = choisir_pion();
        }
        if(!verif_coup(plateau, p, p_dest)) verif = false;
    }
    plateau[p_dest.x*TAILLE_PLATEAU + p_dest.y] = plateau[p.x*TAILLE_PLATEAU + p.y];
    plateau[p.x*TAILLE_PLATEAU + p.y] = CASE_VIDE;
}

Booleen game_over(int plateau[])
{
    if(nb_blanc <= 0 || nb_noir <= 0)
        return true;
    return false;
}


void afficher_plateau(int plateau[])
{
    for (int i = 0; i < TAILLE_PLATEAU; i++)
    {
        printf("%d  |", i);
        for (int j = 0; j < TAILLE_PLATEAU; j++)
        {
            printf("%d|", plateau[i*TAILLE_PLATEAU + j]);
        }
        printf("\n");
    }
}

int main()
{   
    int plateau[TAILLE_PLATEAU*TAILLE_PLATEAU];
    
    init_game(plateau);
    afficher_plateau(plateau);
    while (1)
    {
        jouer_coup(plateau, JOUEUR_BLANC);
        afficher_plateau(plateau);
        if(game_over(plateau))
        {
            printf("Blanc gagne !\n");
            break;
        }
        jouer_coup(plateau, JOUEUR_NOIR);
        afficher_plateau(plateau);
        if(game_over(plateau))
        {
            printf("Noir gagne !\n");
            break;
        }
    }
    return 0;
}