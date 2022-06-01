
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

#define DEFAULT_PORT 8003
#define ERROR_S "SERVER ERROR.."
#define BUFFER_SIZE 1024



//  struct pollfd
// {
// 	int fd;
// 	int events;
// };


int main(int argc, char* argv[])
{
	int  len, rc, on = 1;
	int main_fd;
	int server;
	// pollfd fds[200];
	struct pollfd fds[200];
	int    nfds = 1;
	int new_sd = 0;
	char buffer[BUFFER_SIZE];


	struct sockaddr_in server_address;
	main_fd = socket(AF_INET, SOCK_STREAM, 0); // создаю сокет
	if (main_fd < 0)
	{
		std::cout << "Oshibka" << std::endl;
		exit(0);	
	}
	std::cout << "Socket successfully created" <<std::endl;
	rc = ioctl(main_fd, FIONBIO, (char *)&on);
	server_address.sin_port = htons(DEFAULT_PORT);
	// The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	int ret = bind(main_fd, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address));
	if (ret < 0)	
	{
		std::cout << "Error bind : сокет уже используется" <<std::endl;
		return -1;
	}
	socklen_t size = sizeof(server_address);
	std::cout << "SERVER: " << "listening clients...." <<std::endl;

	listen(main_fd, 1);

	/*************************************************************/
	/* Initialize the pollfd structure                           */
	/*************************************************************/
	memset(fds, 0 , sizeof(fds));
	/*************************************************************/
 	/* Set up the initial listening socket                        */
 	/*************************************************************/
	fds[0].fd = main_fd;
  	fds[0].events = POLLIN;
	int current_size = 1;
	while(true)
	{
    	rc = poll(fds, current_size, 10);
		if (rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		std::cout << "Puk:" <<current_size << "\n";
		int num_fds = current_size;
		for (int i = 0; i < num_fds; i++)
		{
			if (fds[i].fd == main_fd)
			{
				while (new_sd != -1)
				{
					std::cout << "here 22" << std::endl;
					// while(1);
					new_sd = accept(main_fd, NULL, NULL);
					std::cout << "new sd: " << new_sd << std::endl;
					sleep(5);
					if (new_sd < 0)
					{
						std::cout << "   accept() failed " << std::endl;
						if (errno != EWOULDBLOCK)
						{
							std::cout << "   accept() failed " << std::endl;
						perror("  accept() failed");
						// end_server = TRUE;
						}
						break;
					}
				std::cout << "  New incoming connection " << std::endl;
				usleep(5000000);
				// printf("  New incoming connection - %d\n", new_sd);
				fds[num_fds].fd = new_sd;
				fds[num_fds].events = POLLIN;
				current_size++;
				std::cout << "here " << std::endl;
				}
			}
			else
			{
				while(true)
				{
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
						perror("  recv() failed");
						//   close_conn = TRUE;
						}
						break;
					}
					if (rc == 0)
					{

						break;
				
					}
						std::cout << buffer << std::endl;
					rc = send(fds[i].fd, buffer, strlen(buffer), 0);
					if (rc < 0)
					{
						break;
					}
					}
			}


		}
	}
}




		// server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
		// if (server < 0)
		// {
		// 	std::cout << ERROR_S << "Cant accept the client!" << std::endl;
		// }

		// char buffer[BUFFER_SIZE];
		// bool isExit = false;
		// // while(server > 0)
		// // {
		// 	strcpy(buffer, "=> Server connected!\n");
		// 	std::cout << ERROR_S << "Server connect" << std::endl;
		// 	std::cout << buffer << std::endl;
		// 	send(server, buffer, strlen(buffer), 0);

		// 	std::cout << "Client:" << std::endl;
		// 	recv(server, buffer, strlen(buffer), 0);
		// 	std::cout << buffer << std::endl;
		// // }