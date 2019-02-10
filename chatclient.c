/*
Project 1
Nsme: chatclient.c
Language of implementation: C
Description: This is the client. It takes a host name, port number of the server specified from the command line
Source code for setting up connection borrowed from C44/Block 4/client.c sample
Name: Calista Wong
Class: CS 372
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	//variable declaration 
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[600]; //buffer for client message sent to server 
	char handle[11]; //handle can be up to 10 characters 
	char message[511]; //handle appended to buffer

	//get the client handle
	printf("Enter your client handle: \n");
	fgets(handle, 256, stdin);
	strtok(handle, "\n"); //strip out the newline

	if (argc < 3) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(0); } // Check usage & args

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[2]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname(argv[1]); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");

	bool quit = false;
	while (quit == false)
	{
		// Get input message from user
		printf("%s> ",handle);
		memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
		fgets(buffer, sizeof(buffer) - 1, stdin); // Get input from the user, trunc to buffer - 1 chars, leaving \0
		buffer[strcspn(buffer, "\n")] = '\0'; // Remove the trailing \n that fgets adds

		//char capacity check 
		if (strlen(buffer) > 500)
			{
				printf("Note: Your message is longer than 500 characters. It will be truncated.\n");
				int len = strlen(buffer);
				buffer[len-(len-500)] = 0; //trim anything after char 500 
			}

		//Determine whether to end the program
		if (strcmp(buffer, "\\quit") == 0) 
			{
				printf("The client has requested to quit. Goodbye!\n");
				quit=true; //user wants to quit
				break;
			}

		//append handle and buffer to message
		memset(message, '\0', sizeof(message)); // Clear out the message array
		strcpy(message, handle);
		strcat(message, "> ");
		strcat(message,buffer);

		// Send message to server
		charsWritten = send(socketFD, message, strlen(message), 0); // Write to the server
		if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
		if (charsWritten < strlen(buffer)) printf("CLIENT: WARNING: Not all data written to socket!\n");

		// Get return message from server
		memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
		charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
		if (charsRead < 0) error("CLIENT: ERROR reading from socket");
		printf("server> %s\n", buffer);
		if (strcmp(buffer,"\\quit")==0)
			{
				printf("The server has requested to quit. Goodbye!\n");
				break;
			}
	}

	close(socketFD); // Close the socket
	return 0;
}
