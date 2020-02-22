/*===========================================================================================================
				A simple TCP server on port number 9002.
============================================================================================================*/

#include <stdio.h>				
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

	socklen_t addrSize;
	char buffer[256];
	
//============== 1. Create a socket using socket(). ================================

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
		perror("socket was not created.");
	
//============== 2. Bind the socket to a socket address using bind(). =============
											
	memset(&serverAddr, '\0', sizeof(serverAddr));  							// Zero out structure.

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
	sprintf("waiting for a connection on port: %i", SERVER_PORT);

//============== 4. Accept a connection using accept(). ===========================

	addrSize = sizeof(clientAddr);
		
	connfd = accept((sockfd, (sockaddr*) &clientAddr), &addrSize);
	if(connfd < 0)
		perror("could not connect with the client.");

//============== 5. Send and receive data using send() and recv(). ================

	// Receive / read data.
	memset(buffer, 256);
	if(recv(sockfd, buffer, 256) < 0)
		perror("could not read from socket.");
	printf("%s", buffer);

	// Send string to the server.
	if(send(sockfd, "Success", 7) < 0)
		perror("could not write to socket.");


	// Close socket.
	close(sockfd);
	return 0;
}
