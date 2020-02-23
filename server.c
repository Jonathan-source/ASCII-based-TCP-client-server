/*===========================================================================================================
									A simple TCP server on Linux, using C-programming.
============================================================================================================*/

#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>		
#include <arpa/inet.h>
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>	

void perror(char const * msg);

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serverAddr;

	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t clientLen;

	char sendBuff[256];
    char recvBuff[256];
	
    if(argc != 2) 
	{
		printf("\nManual: %s <Server Port> \n", argv[0]);
		return -1;
	}
	int SERVER_PORT = atoi(argv[1]);

//============== 1. Create a socket using socket(). ================================

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("[Server]: socket was not created.");
	else
		printf("[Server]: socket was created.\n");
	
//============== 2. Bind the socket to a socket address using bind(). =============
	
	printf("[Server]: setting up server...\n");	

	memset(&serverAddr, 0, sizeof(serverAddr));  									// Zero out structure.

	// Socket address information needed for binding.
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);										// Convert to network byte order.
	serverAddr.sin_addr.s_addr = INADDR_ANY; 										// "0.0.0.0". 

	if(bind(sockfd, (struct sockaddr * ) &serverAddr, sizeof(serverAddr)) < 0)
		perror("[Server]: socket was not bound to a socket address. Server setup failed.");
	else
		printf("[Server]: socket was bound to a socket address. Server setup complete.\n");

//============== 3. Listen for connections using listen(). ========================
	
	if(listen(sockfd, SOMAXCONN) < 0)	
		perror("[Server]: listen was not performed.");
	else
		printf("[Server]: waiting for connection on port: %i...\n", SERVER_PORT);

//============== 4. Accept a connection using accept(). ===========================

	clientLen = sizeof(clientAddr);
		
	if((connfd = accept(sockfd, (struct sockaddr *) &clientAddr, &clientLen)) < 0)
		perror("[Server]: could not connect with the client.");
	else
		printf("[Server]: client %s connected, waiting for request...\n\n", inet_ntoa(clientAddr.sin_addr));		// prints in IP-format.

//============== 5. Send and receive data using send() and recv(). ================

	// Receive data.
	memset(recvBuff, '\0', sizeof(recvBuff));
	if(recv(connfd, recvBuff, sizeof(recvBuff), 0) < 0)
		perror("[Server]: could not read from socket.");
	else
		printf("[%s]: %s\n", inet_ntoa(clientAddr.sin_addr), recvBuff);

	// Send data.
	memset(sendBuff, '\0', sizeof(sendBuff));
	if(send(connfd, "OK!", 3, 0) < 0)
		perror("[Server]: could not write to socket.");


	return 0;
}
