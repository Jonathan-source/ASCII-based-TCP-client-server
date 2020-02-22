/*===========================================================================================================
										A simple TCP server in C-programming.
============================================================================================================*/

#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>		
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>	

#define SERVER_PORT 9999

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
	
//============== 1. Create a socket using socket(). ================================

    if(sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0)
		perror("[Server]: socket was not created.");
	else
		printf("[Server]: socket was created.");
	
//============== 2. Bind the socket to a socket address using bind(). =============
											
	memset(&serverAddr, 0, sizeof(serverAddr));  								// Zero out structure.

	// Socket address information needed for binding.
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);									// Convert to network standard order.
	serverAddr.sin_addr.s_addr = INADDR_ANY; 									// "0.0.0.0" 

	if(bind(sockfd, (struct sockaddr * ) &serverAddr, sizeof(serverAddr)) < 0)
		perror("[Server]: socket was not bound to a socket address.");
	else
		printf("[Server]: socket was bound to socket address.");

//============== 3. Listen for connections using listen(). ========================
	
	if(listen(sockfd, SOMAXCONN) < 0)	
		perror("[Server]: listen was not performed.");
	else
		printf("[Server]: waiting for a connection on port: %i", SERVER_PORT);

//============== 4. Accept a connection using accept(). ===========================

	clientLen = sizeof(clientAddr);
		
	if((connfd = accept(sockfd, (struct sockaddr *) &clientAddr, &clientLen)) < 0)
		perror("[Server]: could not connect with the client.");

//============== 5. Send and receive data using send() and recv(). ================

	// Receive data.
	memset(recvBuff, '\n', sizeof(recvBuff));
	if(recv(connfd, recvBuff, sizeof(recvBuff), 0) < 0)
		perror("[Server]: could not read from socket.");
	else
		printf("\n%s", recvBuff);

	// Send data.
	memset(sendBuff, '\n', sizeof(sendBuff));
	if(send(connfd, "[Server]: data received.", 15, 0) < 0)
		perror("[Server]: could not write to socket.");

	// Close socket.
	// ???
	
	return 0;
}
