/*===========================================================================================================
				A simple TCP server on port number 9002.
============================================================================================================*/

#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>		
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>	

#define SERVER_PORT 9002

void perror(char const * msg);

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serverAddr;

	int connfd;
	struct sockaddr_in clientAddr;

	socklen_t clientLen;
	char buffer[256];
	
//============== 1. Create a socket using socket(). ================================

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
		perror("socket was not created.");
	
//============== 2. Bind the socket to a socket address using bind(). =============
											
	memset(&serverAddr, 0, sizeof(serverAddr));  							// Zero out structure.

	// Socket address information needed for binding.
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);									// Convert to network standard order.
	serverAddr.sin_addr.s_addr = INADDR_ANY; 									// "0.0.0.0" 

	if(bind(sockfd, (struct sockaddr * ) &serverAddr, sizeof(serverAddr)) < 0)
		perror("socket was not bound to a socket address.");

//============== 3. Listen for connections using listen(). ========================
	
	// Mark the socket for listening.

	if(listen(sockfd, SOMAXCONN) < 0)	
		perror("listen failed.");
	printf("waiting for a connection on port: %i", SERVER_PORT);

//============== 4. Accept a connection using accept(). ===========================

	clientLen = sizeof(clientAddr);
		
	if((connfd = accept(sockfd, (struct sockaddr *) &clientAddr, &clientLen)) < 0)
		perror("could not connect with the client.");

//============== 5. Send and receive data using send() and recv(). ================

	// Receive / read data.
	memset(buffer, '\n', 256);
	if(recv(connfd, buffer, sizeof(buffer), 0) < 0)
		perror("could not read from socket.");
	printf("\n%s", buffer);

	// Send string to the server.
	if(send(connfd, "Success", 7, 0) < 0)
		perror("could not write to socket.");


	// Close socket.
	
	return 0;
}
