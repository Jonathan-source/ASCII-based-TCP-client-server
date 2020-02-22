/*===========================================================================================================
				A simple TCP server on port number 9002.
============================================================================================================*/

#include <stdio.h>				
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>	

void perror(char const * msg);

int main(int argc, char *argv[])
{
	int sockfd;
	int portno;
	int clientsocket;
	char buffer[256];
	sockaddr_in server;
	sockaddr_in client;
	socklen_t clientSize;
	
//============== 1. Create a socket using socket(). ================================

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
		perror("socket was not created.");
	
//============== 2. Bind the socket to a socket address using bind(). =============

	portno = 9002													
	memset(&server, sizeof(server));  							// Zero out structure.

	// Socket address information needed for binding.
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);							
	server.sin_addr.s_addr = INADDR_ANY; 						// "0.0.0.0" 

	if(bind(sockfd, (struct sockaddr * ) &server, sizeof(server)) < 0)
		perror("socket was not bound to a socket address.");

//============== 3. Listen for connections using listen(). ========================
	
	// Mark the socket for listening.

	if(listen(sockfd, SOMAXCONN) < 0)	
		perror("listen failed.");

//============== 4. Accept a connection using accept(). ===========================

	clientSize = sizeof(client);
		
	if(accept(sockfd, (sockaddr*) &client), &clientSize);
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
