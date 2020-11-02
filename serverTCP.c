#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "dame.h"


int main(int argc, char *argv[])
{
    int sockfd, len, connfd[2], plateau[TAILLE_PLATEAU*TAILLE_PLATEAU];
    Pion p;

    struct sockaddr_in servaddr, cliaddr;

    if(argc != 2)
    {
        printf("utilisation : ./server [port]\n");
        return 0;
    }

    //création de socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        perror("problème lors de la création de la socket"); 
        exit(-1);
    }

    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(atoi(argv[1]));

    //lie la socket à l'adresse IP
    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    { 
        perror("encore rate"); 
        exit(-1); 
    }

    //serveur écoute
    if((listen(sockfd, 1)) != 0)
    { 
        printf("Listen failed...\n"); 
        exit(0); 
    }
    printf("Server listening..\n");

    
    len = sizeof(cliaddr);

    //accepte les clients
    for (int i = 0; i < 2; i++)
    {
        if((connfd[i] = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
        {
            printf("server acccept failed...\n"); 
            exit(0);
        }
        else
            printf("server acccept the client %d\n", i+1);
    }
    
    char buf[100] = "choisi le pion à déplacer";

    init_game(plateau);
    //game loop  
    while(1)
    {
        for (int i = 0; i < 2; i++)
        {
            write(connfd[i], (const char*)&plateau, sizeof(plateau));
            printf("le plateau....\nJoueur %d reflechi...\n", i+1);
            write(connfd[i], (const char*)&buf, sizeof(buf));
            recv(connfd[i], &p, sizeof(p), 0);
            printf("Coordonnées envoyées par le j%d :\n x : %d\ny : %d\n", i+1, p.x, p.y);
        }
    }
    close(sockfd);
    return 0;
}