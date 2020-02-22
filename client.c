/*===========================================================================================================
										A simple TCP client in C-programming.
============================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 		
#include <sys/socket.h>		 
#include <netinet/in.h>	

int main(int argc, char* argv[])
{
	int sockfd = 0;
	struct sockaddr_in serverAddr;
	char sendBuff[256];

	if(argc != 2) 
	{
		printf("\nManual: %s <server port number> \n", argv[0]);
		return -1;
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("[Client]: could not create socket.");
	else
		printf("[Client]: socket was created.\n");

	
	memset(&serverAddr, 0, sizeof(serverAddr));

	// Socket address information needed for binding.
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));									// Convert to network standard order.


	if(connect(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
		perror("[Client]: could not connect with the server.");
	else
		printf("[Client]: successfully connected with the server.\n");

	memset(sendBuff, '\0', sizeof(sendBuff));
	sprintf(sendBuff, "This is a text sent by the client");
	send(sockfd, sendBuff, strlen(sendBuff), 0);

	return 0;
}