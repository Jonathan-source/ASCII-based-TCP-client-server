/*===========================================================================================================
		This is a simple server in the internet domain using TCP, the port number is passed as an argument.
============================================================================================================/*

#include <stdio.h>			// input output.
#include <sys/types.h> 		// a set of data types used in system calles.
#include <sys/socket.h>		// needed for sockets. 
#include <netinet/in.h>		// 

int main(int argc, char *argv[])
{
	
    //============== 1. Create a socket using socket(). ==============================

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		std::cout << "[Error]: Socket not created.";
		return EXIT_FAILURE;
	}

	//============== 2. Bind the socket to a socket address using bind(). ============

	// Socket address information needed for binding.
	sockaddr_in server_addr, client_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 0;								// Problems: May I pick "any" port number? Do I need to convert using htons?

    //============== 3. Listen for connections using listen(). =======================



    //============== 4. Accept a connection using accept(). ==========================



    //============== 5. Send and receive data using send() and recv(). ===============


	EXIT_SUCCESS;
}