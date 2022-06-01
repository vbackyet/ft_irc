
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

#define DEFAULT_PORT 8002
#define ERROR_S "SERVER ERROR.."
#define BUFFER_SIZE 1024



//  struct pollfd
// {
// 	int fd;
// 	int events;
// };


int main(int argc, char* argv[])
{
	int   len, rc, on = 1;
	int main_fd;
	int server;
	// pollfd fds[200];
	struct pollfd fds[200];
	int    nfds = 1;
	int new_sd = 0;
	char buffer[BUFFER_SIZE];


	struct sockaddr_in server_address;
  /*************************************************************/
  /* Create an AF_INET6 stream socket to receive incoming      */
  /* connections on                                            */
  /*************************************************************/
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
		/***********************************************************/
		/* Call poll() and wait 3 minutes for it to complete.      */
		/***********************************************************/
    	std::cout <<"Waiting on poll()...\n";
    	rc = poll(fds, current_size, 10);
		/***********************************************************/
		/* Check to see if the poll call failed.                   */
		/***********************************************************/
		if (rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		/***********************************************************/
			/* Check to see if the 3 minute time out expired.          */
			/***********************************************************/
			// if (rc == 0)
			// {
			// printf("  poll() timed out.  End program.\n");
			// break;
			// }
		std::cout << "Puk:" <<current_size << "\n";
		int num_fds = current_size;
		for (int i = 0; i < num_fds; i++)
		{
			/*********************************************************/
			/* Loop through to find the descriptors that returned    */
			/* POLLIN and determine whether it's the listening       */
			/* or the active connection.                             */
		/*********************************************************/
					if(fds[i].revents == 0)
						continue;


							/*********************************************************/
			/* If revents is not POLLIN, it's an unexpected result,  */
			/* log and end the server.                               */
			/*********************************************************/
				if(fds[i].revents != POLLIN)
				{
					// printf("  Error! revents = %d\n", fds[i].revents);
					// end_server = TRUE;
					break;
				}
			if (fds[i].fd == main_fd)
			{
				/*******************************************************/
				/* Listening descriptor is readable.                   */
				/*******************************************************/

				/*******************************************************/
				/* Accept all incoming connections that are            */
				/* queued up on the listening socket before we         */
				/* loop back and call poll again.                      */
				/*******************************************************/
				 while (new_sd != -1)
				{
				/*****************************************************/
				/* Accept each incoming connection. If               */
				/* accept fails with EWOULDBLOCK, then we            */
				/* have accepted all of them. Any other              */
				/* failure on accept will cause us to end the        */
				/* server.                                           */
				/*****************************************************/
				std::cout << "here 22" << std::endl;
				new_sd = accept(main_fd, NULL, NULL);
				std::cout << "new sd: " << new_sd << std::endl;
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

				/*****************************************************/
				/* Add the new incoming connection to the            */
				/* pollfd structure                                  */
				/*****************************************************/
				std::cout << "  New incoming connection " << std::endl;
				// printf("  New incoming connection - %d\n", new_sd);
				fds[num_fds].fd = new_sd;
				fds[num_fds].events = POLLIN;
				current_size++;
				std::cout << "here " << std::endl;
				/*****************************************************/
				/* Loop back up and accept another incoming          */
				/* connection                                        */
				/*****************************************************/
				}
				std::cout << "here 2" << std::endl;
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

					/*****************************************************/
					/* Check to see if the connection has been           */
					/* closed by the client                              */
					/*****************************************************/
					if (rc == 0)
					{
						// printf("  Connection closed\n");
						// close_conn = TRUE;

						break;
				
					}
						std::cout << buffer << std::endl;
						// usleep(10000000);
					/*****************************************************/
					/* Data was received                                 */
					/*****************************************************/
					// printf("  %d bytes received\n", len);

					/*****************************************************/
					/* Echo the data back to the client                  */
					/*****************************************************/
					rc = send(fds[i].fd, buffer, strlen(buffer), 0);
					if (rc < 0)
					{
						// perror("  send() failed");
						// close_conn = TRUE;
						break;
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
	}
}
