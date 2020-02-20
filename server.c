/*===========================================================================================================
				A simple TCP server on port number 9002.
============================================================================================================/*

#include <stdio.h>			
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>	
#include <string>
#include <iostream>	 

 void error(std::string &msg)
 {
	std::cout << "[Error]: " + msg;
	return EXIT_FAILURE;
 }

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
		error("socket was not created.");
	
//============== 2. Bind the socket to a socket address using bind(). =============

	portno = 9002													
	bzero((char*) &server, sizeof(server));  					// Clear the server address before using it.

	// Socket address information needed for binding.
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);							
	server.sin_addr.s_addr = INADDR_ANY; 						// "0.0.0.0" 

	if(bind(sockfd, (struct sockaddr * ) &server, sizeof(server)) < 0)
		error("socket was not bound to a socket address.");

//============== 3. Listen for connections using listen(). ========================
	
	// Mark the socket for listening.

	if(listen(sockfd, SOMAXCONN) < 0)	
		error("listen failed.");

//============== 4. Accept a connection using accept(). ===========================
	clientSize = sizeof(client);
		
	if(accept(sockfd, (sockaddr*) &client), &clientSize))
		error("could not connect with the client.");


	// Close the listenning socket.
	


//============== 5. Send and receive data using send() and recv(). ================



	// Close socket.

	EXIT_SUCCESS;
}
