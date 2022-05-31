
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define DEFAULT_PORT 8005
#define ERROR_S "SERVER ERROR.."
#define BUFFER_SIZE 1024



int main(int argc, char* argv[])
{
	int client;
	int server;



	struct sockaddr_in server_address;

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
	while(true)
	{
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
