#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
    int sockfd, len, connfd, n;
    char buffer[100];

    struct sockaddr_in servaddr, cliaddr;

    if(argc != 2)
    {
        printf("utilisation : ./server [port]\n");
        return 0;
    }

    //création de socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        perror("HE ! RATE !"); 
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

    //accepte le client
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 

    while(strncmp(buffer,"quit",4) != 0)
    {
        //copie le msg du client dans buffer
        n = recv(connfd, buffer, sizeof(buffer), 0);
        //buffer[n] = '\0';
        printf("From client: %s\n", buffer);
    }
    close(sockfd);
    return 0;
}