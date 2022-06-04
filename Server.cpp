
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
#include <vector>
#include "Server.hpp"

#include "Postman.hpp"
#define DEFAULT_PORT 8006
// #define ERROR_S "SERVER ERROR.."
// #define BUFFER_SIZE 1024
// #define EXIT_FAILURE 1


Server::Server(int argc, char* argv[])
{
	this->argc = argc;
	this->argv = argv;
	main1();
}


int Server::main1()
{
	 int  len = 1;
	int  rc = 1;
	int  on = 1;
			int    nfds = 1;
		int new_sd = 0;
	if ((main_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "poll failure" << std::endl;
		exit(EXIT_FAILURE);
	}
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
        std::cout << ret <<std::endl;
		std::cout << "Error bind : сокет уже используется" <<std::endl;
		return -1;
	}
	socklen_t size = sizeof(server_address);
	std::cout << "SERVER: " << "listening clients...." <<std::endl;

	listen(main_fd, 1);
	fds.push_back((pollfd){main_fd, POLLIN, 0});
	int current_size = 1;
	while(true)
	{
		new_sd = 0;
    	rc = poll(fds.data(), current_size, 10);
		if (rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		// std::cout << "Puk:" <<current_size << "\n";
		int num_fds = current_size;
		// std::cout << "numfds: " <<  num_fds <<std::endl;
		for (int i = 0; i < num_fds; i++)
		{
			// sleep(1);
			if (fds[i].fd == main_fd)
			{
				while (new_sd != -1)
				{
					// std::cout << "!!!!!!!!!!!!!!!!!!!" <<  num_fds <<std::endl;
					new_sd = accept(main_fd, NULL, NULL);
					if (new_sd < 0)
					{
						// std::cout << "breaking bad"  <<std::endl;
						break;
					}
					fds.push_back((pollfd){new_sd, POLLIN | POLLOUT | POLLHUP, 0}); // добавляем не главный сервер
					current_size++;
					// std::cout << "here " << std::endl;
				}
			}
			else
			{
				// while(true)
				{
					process_users(&fds[i]);
				}
			}


		}
	}
	return (0);
}

 char* strset(char* str, int c)
 {
     char *t = str;
     while (*str!= 0)
     {
         *str= c;
         str++;

     }
     return t;
 }


void Server::remove(pollfd *iter)
{

}



void Server::sendback(int fd)
{

}


void Server::receive(int fd)
{
	
    char msg[BUFFER_SIZE];
	int rc;

    // bzero(&msg, sizeof(msg));
    // if (recv(fd, &msg, BUFFER_SIZE - 1, 0) < 0) {
    //     std::cerr << "recv() failure" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
	// else {
	// 	std::cerr << "Connected !!! " << std::endl;

	// }
	// std::cout << buffer << std::endl;
	// rc = send(fd, buffer, strlen(buffer), 0);
	// // if (rc < 0)
	// // {
	// // 	break;
	// // }
	
    // my_postman.sendRequest(fd, msg);
	// char buffer[1024];
	while(true)
				{
					bzero(&buffer, sizeof(buffer));
					rc = recv(fd, &buffer, sizeof(buffer) -1 , 0);
					
					// std::cout << buffer << "==" << sizeof(buffer) << std::endl;
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
					// sleep(10);
					rc = send(fd, buffer, strlen(buffer), 0);
					if (rc < 0)
					{
						break;
					}
					}
}


int Server::process_users(pollfd *iter)
{
	// std::cerr <<  iter->revents << std::endl;
	if (iter->revents & POLLHUP) {
		remove(iter);
		// break;
	}
	if (iter->revents & POLLOUT)
		receive(iter->fd);
		// sendback(iter->fd);

	// if (iter->revents & POLLIN)
	// 	receive(iter->fd);
	return(0);
}



