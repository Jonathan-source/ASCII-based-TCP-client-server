/*===========================================================================================================
								A simple TCP server on port number 9002.
============================================================================================================/*

#include <stdio.h>			
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>		 

int main(int argc, char *argv[])
{
	int sockfd;
	int portno;
	int clientsocket;
	char buffer[256];
	sockaddr_in server;
	sockaddr_in client;
	socklen_t clientSize;
	
    //============== 1. Create a socket using socket(). ==============================

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		std::cout << "[Error]: Socket not created.";
		return EXIT_FAILURE;
	}
	
	//============== 2. Bind the socket to a socket address using bind(). ============

	portno = 9002													// Set port number
	bzero((char*) &server, sizeof(server));  						// Clear the server address before using it.

	// Socket address information needed for binding.
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);							
	server.sin_addr.s_addr = INADDR_ANY; 							// "0.0.0.0" 

	if(bind(sockfd, (struct sockaddr * ) &server, sizeof(server)) < 0)
	{
		std::cout "[Error]: Failed to bind socket to a socket address.";
		return EXIT_FAILURE;
	} 


    //============== 3. Listen for connections using listen(). =======================
	
	// Mark the socket for listening.
	if(listen(sockfd, SOMAXCONN) < 0)								// Backlog is the maximum number of queued connections, 
	{																// you want on a socket. SOMAXCONN is the max number.
		std::cout "[Error]: Listen failed.";
	}


    //============== 4. Accept a connection using accept(). ==========================
	clientSize = sizeof(client);
		
	if(accept(sockfd, (sockaddr*) &client), &clientSize))
	{
		std::cout << "[Error]: Could not connect with the client."
		return EXIT_FAILURE;
	}

	// Close the listenning socket.



	//============== 5. Send and receive data using send() and recv(). ===============



	// Close socket.

	EXIT_SUCCESS;
}
