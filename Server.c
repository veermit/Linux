/*Server socket program*/


/*
Application Layer 	-} User process
Transport Layer 	-} Protocol stack
Network Layer		-} Protocol stack
DAtaLink Layer		-}
*/



/*Header files include*/
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define SERVER_PORT 8080 
#define MAX_BUFF   1024

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread;
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[MAX_BUFF] = {0}; 
	char *hello = "Hello from server"; 
	
	/*Creating socket file descriptor */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	/*Upon successful completion, socket() shall return a 
	non-negative integer, the socket file descriptor. 
	Otherwise, a value of -1 shall be returned and errno 
	set to indicate the error.*/
	
	/*Forcefully attaching socket to the SERVER_PORT 8080 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}
	
	/*Upon successful completion, setsockopt() shall return 0. 
	Otherwise, -1 shall be returned and errno set to indicate the error.*/

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( SERVER_PORT ); 
	
	// Forcefully attaching socket to the SERVER_PORT 8080 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}

	/*Upon successful completion, bind() shall return 0; otherwise, 
	-1 shall be returned and errno set to indicate the error.*/

	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

	/*Upon successful completions, listen() shall return 0; otherwise, 
	-1 shall be returned and errno set to indicate the error.*/

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 

	/*If successful, accept() returns a non-negative integer, 
	which is a descriptor of the accepted socket. Upon return, 
	addrlen contains the actual length in bytes of the address returned. 
	On failure, it returns a value of -1 and sets errno to one of the following values: EBADF.*/
	
	valread = read( new_socket , buffer, MAX_BUFF);

	/*The read() function reads data previously written to a file. 
	If any portion of a regular file prior to the end-of-file has 
	not been written, read() shall return bytes with value 0. For example, 
	lseek() allows the file offset to be set beyond the end of existing data in the file.*/

	printf("%s\n",buffer ); 

	send(new_socket , hello , strlen(hello) , 0 ); 
	
	/*Return value. If no error occurs, send returns the total number of bytes sent, 
	which can be less than the number requested to be sent in the len parameter. 
	Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can 
	be retrieved by calling WSAGetLastError.*/
	
	printf("Hello message sent\n"); 
	
	return 0; 
}  
