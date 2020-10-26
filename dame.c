#include "dame.h"

/* créer un plateau de jeu avec les pions bien placés*/
void init_game(int plateau[]){

    //créer les cases vides
    for (int i = 0; i < TAILLE_PLATEAU; i++)
    {
        for (int j = 0; j < TAILLE_PLATEAU; j++)
        {
            plateau[i*TAILLE_PLATEAU + j] = CASE_VIDE;
        }
    }
    
    //créer les pions noires
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


/* demande à l'utilisateur de choisir une case */
Pion choisir_case()
{
    Pion p;
    printf("coordonnée X : ");
    scanf("%d", &p.x);
    while(p.x < 0 || p.x > TAILLE_PLATEAU)
    {
        printf("\nveuillez rentrer des coordonnées valides");
        scanf("%d", &p.x);
    }
    printf("coordonnée Y : ");
    scanf("%d", &p.y);
    while(p.y < 0 || p.y > TAILLE_PLATEAU)
    {
        printf("\nveuillez entrer des coordonnées valides");
        scanf("%d", &p.y);
    }
    return p;
}

/* vérifie que le coup est règlementaire */
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

/* à appeler avant chaque choix du joueur pour s'assurer qu'il fait le meilleur coup */
void verif_coup_obligatoire(int plateau[], int joueur)
{
    
}

/* simule un tour d'action d'un joueur */
void jouer_coup(int plateau[], int joueur)
{
    Booleen verif = true;
    Pion p, p_dest;
    while(verif)
    {
        printf("chosir le pion à jouer.\n");
        p = choisir_case();
        printf("x = %d, y = %d\n", p.x, p.y);
        while(plateau[p.x*TAILLE_PLATEAU + p.y]%2 != joueur || plateau[p.x*TAILLE_PLATEAU + p.y] == CASE_VIDE)
        {
            printf("\nVous devez choisir un pion qui vous appartient.\n");
            p = choisir_case();
            printf("x = %d, y = %d\n", p.x, p.y);
        }

        printf("chosir la destination.\n");
        p_dest = choisir_case();
        while (plateau[p_dest.x*TAILLE_PLATEAU + p_dest.y] != CASE_VIDE)
        {
            printf("choisir une destination valide\n");
            p_dest = choisir_case();
        }
        if(!verif_coup(plateau, p, p_dest)) verif = false;
    }
    plateau[p_dest.x*TAILLE_PLATEAU + p_dest.y] = plateau[p.x*TAILLE_PLATEAU + p.y];
    plateau[p.x*TAILLE_PLATEAU + p.y] = CASE_VIDE;
}

/* vérifie que le jeu est terminé */
Booleen game_over(int plateau[])
{
    if(nb_blanc <= 0 || nb_noir <= 0)
        return true;
    return false;
}


/* affiche l'état du plateau de jeu */
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
    printf("\n");
}


/* vous avez pas besoin que je vous dise ce que fait cette fonction si ?*/
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