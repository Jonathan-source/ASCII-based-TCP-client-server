/*===========================================================================================================
	This is a simple server in the internet domain using TCP, the port number is passed as an argument.
============================================================================================================/*

#include <stdio.h>			
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>		 

int main(int argc, char *argv[])
{
	int sockfd;
	int portno;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	
    //============== 1. Create a socket using socket(). ==============================

    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		std::cout << "[Error]: Socket not created.";
		return EXIT_FAILURE;
	}
	
	//============== 2. Bind the socket to a socket address using bind(). ============

	portno = atoi(argv[1]);											// Store the port number
	bzero((char*) &server_addr, sizeof(server_addr));  				// Clear the server address before using it.

	// Socket address information needed for binding.
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);							
	server_addr.sin_addr.s_addr = INADDR_ANY; 						// "0.0.0.0" 
	
	if(bind(sockfd, (struct sockaddr * ) &server_addr, sizeof(server_addr)) < 0)
	{
		std::cout "[Error]: Failed to bind socket to a socket address.";
		return EXIT_FAILURE;
	} 


    //============== 3. Listen for connections using listen(). =======================



    //============== 4. Accept a connection using accept(). ==========================



    //============== 5. Send and receive data using send() and recv(). ===============


	EXIT_SUCCESS;
}
