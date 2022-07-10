#pragma once

#include <iostream>
#include <sys/poll.h>
#include <vector>
#include <map>

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
#include "UsersService.hpp"
// #include "../service/Service.hpp"
#include "Postman.hpp"
// #include "User.hpp"
// #define DEFAULT_PORT 8888
#define ERROR_S "SERVER ERROR.."
#define BUFFER_SIZE 1024
#define EXIT_FAILURE 1

class Server {

	private:
	public:
		// const std::string&					_port;
		Postman my_postman;
		static int									_socket;
		std::vector<pollfd>					_polls;

        Postman                             _postman;
		UsersService						_UsersService;
        int argc;
        char** argv;


		int main_fd;
		int server;
		// pollfd fds[200];
		std::vector <pollfd> fds;
		// std::vector <User> users;
		// struct pollfd fds[200];

		char buffer[BUFFER_SIZE];
		struct sockaddr_in server_address;

	// struct sockaddr_in server_address;

	
		Server(int argc, char* argv[]);
		~Server();
        int main1();
        void remove(pollfd *iter);
        void sendback(int fd);
        void receive(int fd);
		int process_users(pollfd *iter);
};