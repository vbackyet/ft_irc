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
// #include "../service/Service.hpp"
#include "Postman.hpp"
#define DEFAULT_PORT 8888
#define ERROR_S "SERVER ERROR.."
#define BUFFER_SIZE 1024
#define EXIT_FAILURE 1

class Server {

	private:
	public:
		// const std::string&					_port;
		int									_socket;
		std::vector<pollfd>					_polls;

        Postman                             _postman;
        int argc;
        char** argv;

		int  len, rc, on = 1;
		int main_fd;
		int server;
		// pollfd fds[200];
		std::vector <pollfd> fds;
		// struct pollfd fds[200];
		int    nfds = 1;
		int new_sd = 0;
		char buffer[BUFFER_SIZE];
	struct sockaddr_in server_address;

	// struct sockaddr_in server_address;

	
		Server(int argc, char** argv);
		~Server();
        int main();
        void remove(pollfd *iter);
        void sendback(int fd);
        void receive(int fd);
		void process_users(pollfd *iter);
	// 	void	start();
	// 	void	stop();

	// protected:
	// 	void	init();
	// 	void	createSocket();
	// 	void	add();
	// 	void	remove(std::vector<pollfd>::iterator);
	// 	void 	receive(int);
	// 	void 	sendback(int);
	// 	bool 	processed(int);
};