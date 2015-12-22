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

int main(int argc, char *argv[])
{
	int port = 5002;
	char* host = "localhost", *buf, errcode;
	int sockfd = connect_to_server(host, port, &errcode);
	switch(errcode){
		case 1: fprintf(stderr, "ERROR opening socket"); exit(errcode);
		case 2: fprintf(stderr, "ERROR, no such host\n"); exit(errcode);
		case 3: fprintf(stderr, "ERROR connecting"); exit(errcode);
	}
	printf("You connected to %s:%d\n", host, port);
	buf = create_labyrinth(15,15);
	if (write(sockfd, buf, strlen(buf)) < 0) { 
		fprintf(stderr, "ERROR writing to socket"); 
		exit(1); 
	}
	bzero(buf, BUFFER_LENGTH);
	if (read(sockfd, buf, BUFFER_LENGTH-1) < 0) { 
		fprintf(stderr, "ERROR reading from socket");
		exit(1);
	}
	printf("%s\n", buf);
	close(sockfd);
	return 0;
}
