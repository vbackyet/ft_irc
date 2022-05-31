
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

#define DEFAULT_PORT 8005
#define ERROR_S "SERVER ERROR.."
#define BUFFER_SIZE 1024



//  struct pollfd
// {
// 	int fd;
// 	int events;
// };


int main(int argc, char* argv[])
{
	int    len, rc, on = 1;
	int client;
	int server;
	// pollfd fds[200];
	struct pollfd fds[200];
	int    nfds = 1;


	struct sockaddr_in server_address;
  /*************************************************************/
  /* Create an AF_INET6 stream socket to receive incoming      */
  /* connections on                                            */
  /*************************************************************/
	client = socket(AF_INET, SOCK_STREAM, 0); // создаю сокет
	if (client < 0)
	{
		std::cout << "Oshibka" << std::endl;
		exit(0);	
	}
	std::cout << "Socket successfully created" <<std::endl;
	server_address.sin_port = htons(DEFAULT_PORT);
	// The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address));
	if (ret < 0)	
	{
		std::cout << "Error bind : сокет уже используется" <<std::endl;
		return -1;
	}
	socklen_t size = sizeof(server_address);
	std::cout << "SERVER: " << "listening clients...." <<std::endl;

	listen(client, 1);

	/*************************************************************/
	/* Initialize the pollfd structure                           */
	/*************************************************************/
	memset(fds, 0 , sizeof(fds));
	/*************************************************************/
 	/* Set up the initial listening socket                        */
 	/*************************************************************/
	fds[0].fd = client;
  	fds[0].events = POLLIN;
	while(true)
	{
		/***********************************************************/
		/* Call poll() and wait 3 minutes for it to complete.      */
		/***********************************************************/
    	std::cout <<"Waiting on poll()...\n";
    	rc = poll(fds, 1, 100);
		/***********************************************************/
		/* Check to see if the poll call failed.                   */
		/***********************************************************/
		if (rc < 0)
		{
		perror("  poll() failed");
		break;
		}

		server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
		if (server < 0)
		{
			std::cout << ERROR_S << "Cant accept the client!" << std::endl;
		}
		char buffer[BUFFER_SIZE];
		bool isExit = false;
		// while(server > 0)
		// {
			strcpy(buffer, "=> Server connected!\n");
			std::cout << ERROR_S << "Server connect" << std::endl;
			std::cout << buffer << std::endl;
			send(server, buffer, strlen(buffer), 0);

			std::cout << "Client:" << std::endl;
			recv(server, buffer, strlen(buffer), 0);
			std::cout << buffer << std::endl;
		// }
	}
}
