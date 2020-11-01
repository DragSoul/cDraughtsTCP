#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "dame.h"


int main(int argc, char *argv[])
{
    int sockfd, connfd, plateau[TAILLE_PLATEAU*TAILLE_PLATEAU]; 
    char msg_cli[100];
    Pion p;
    struct sockaddr_in servaddr; 
  
    if(argc != 3)
    {
        printf("utilisation   : ./client [adresse] [port]\n");
        return 0;
    }

    // creation du file descriptor de socket 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        perror("rate"); 
        exit(-1); 
    } 
        
    // remplissage des info du serveur 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(atoi(argv[2])); 
    inet_aton(argv[1], &servaddr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 

    while(1){
        recv(sockfd, &plateau, sizeof(plateau), 0);
        afficher_plateau(plateau);
        recv(sockfd, &msg_cli, sizeof(msg_cli), 0);
        printf("%s\n", msg_cli);
        printf("x : ");
        scanf("%d", &p.x);
        printf("y : ");
        scanf("%d", &p.y);
        /*recevoir le plateau (faire une structure ?)*/
        write(sockfd, (const char*)&p, sizeof(p)); 
    }
    close(sockfd);
    return 0; 
}