// A simple server in the internet domain using TCP
// The port number is passed as an argument 
// Runs forever, forking a separate 
// process for each connection
// From: http://www.linuxhowtos.org/data/6/server2.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void respond(int); /* function prototype */
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, pid;
    struct sockaddr_in serv_addr, cli_addr;
    struct sockaddr *addr;

    // Incorrect call
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    // Initialise IP Address + Port Number
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    addr = (struct sockaddr *) &serv_addr;

    if (bind(sockfd, addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    
    listen(sockfd,5);
    socklen_t cli_len = sizeof(cli_addr);
    addr = (struct sockaddr *) &cli_addr;

    while (1) {
        newsockfd = accept(sockfd, addr, &cli_len);
        if (newsockfd < 0) {
            error("ERROR on accept");
        }
        pid = fork();
        if (pid < 0) {
            error("ERROR on fork");
        } else if (pid != 0) {
            close(newsockfd);
        } else {  // (pid == 0)
            close(sockfd);
            respond(newsockfd);
            exit(0);
        }
   }
   close(sockfd);
   return 0; /* we never get here */
}

// Handles all communication
// once a connnection has been established.
void respond (int sock)
{
    int n;
    char buffer[256];
    
    bzero(buffer,256);
    n = read(sock,buffer,255);

    if (n < 0)
        error("ERROR reading from socket");

    printf("Here is the message: %s\n",buffer);
    n = write(sock,"I got your message",18);

    if (n < 0)
        error("ERROR writing to socket");
}


// ---------- SERVER VERSION #2 ---------- //


// A simple server in the internet domain using TCP
// The port number is passed as an argument
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
   perror(msg);
   exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc < 2) {
       fprintf(stderr,"ERROR, no port provided\n");
       exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
      error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
       error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0) 
       error("ERROR on accept");

    bzero(buffer,256);
    n = read(newsockfd,buffer,255);

    if (n < 0) 
        error("ERROR reading from socket");

    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);

    if (n < 0)
        error("ERROR writing to socket");
    
    // Close 
    close(newsockfd);
    close(sockfd);

    return 0; 
}