#pragma once

#include <iostream>
#include <sys/poll.h>
#include <vector>
#include <map>
// #include "../service/Service.hpp"
#include "Postman.hpp"


class Server {

	private:
		const std::string&					_port;
		int									_socket;
		std::vector<pollfd>					_polls;

        Postman                             _postman;
        int argc;
        char* argv[];

	public:
		Server(std::string const&, std::string const&);
		~Server();
        int main(int argc, char* argv[]);
        void remove(pollfd *iter);
        void sendback(int fd);
        void receive(int fd);
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