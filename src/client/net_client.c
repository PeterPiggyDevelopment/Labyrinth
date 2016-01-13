#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "../include/eller_lab.h"

#define h_addr h_addr_list[0]
#define BUFFER_LENGTH 1024

int connect_to_server(char* hostname, int portno, char* errcode){
	struct sockaddr_in serv_addr;
	struct hostent* server = gethostbyname(hostname);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) { *errcode = 1; }
	if (server == NULL) { *errcode = 2; }
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) { *errcode = 3; }
	return sockfd;
}

char* get_lab(int width, int height){
	char* host = "localhost", errcode, *buf;
	int port = 5002, sockfd = connect_to_server(host, port, &errcode);
	switch(errcode){
		case 1: fprintf(stderr, "ERROR opening socket"); exit(errcode);
		case 2: fprintf(stderr, "ERROR, no such host\n"); exit(errcode);
		case 3: fprintf(stderr, "ERROR connecting"); exit(errcode);
	}
	buf = create_labyrinth(width, height);
	if (write(sockfd, buf, strlen(buf)) < 0) { 
		fprintf(stderr, "ERROR writing to socket"); 
		exit(1); 
	}
	bzero(buf, BUFFER_LENGTH);
	if (read(sockfd, buf, BUFFER_LENGTH-1) < 0) { 
		fprintf(stderr, "ERROR reading from socket");
		exit(1);
	}
	close(sockfd);
    return buf;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        puts("USAGE: client <labyrinth update time(secs)>.");
    else if (argc > 2) {
        puts("USAGE: client <labyrinth update time(secs)>.");
    }
    else{
        int i = 0, width = 10, height = 10;
        while(1){
            char* buf = get_lab(width, height);
            if (strcmp(buf, "no way")){ 
                printf("%s\n", buf);
                sleep(atoi(argv[1]));
                for (i = 0; i <= height+1; i++) printf("\033[A\033[2K");
            }
        }
    }
    return 0;
}
