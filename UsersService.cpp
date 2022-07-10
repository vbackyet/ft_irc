#include "UsersService.hpp"
// #include "Server.hpp"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <sys/socket.h>


std::vector<std::string> split(const std::string& s, char seperator)
{
   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}


int UsersService::process_command(User _user, std::string commnd)
{
    const void * a = commnd.c_str();
    const char * b = commnd.c_str();
    int rc = send(_user.fd, a , strlen(b), 0);
    if (rc < 0)
    {
        "BREAK"; // в цикле сделатаь брейк
    }
}


int UsersService::registr(User _user, std::string commnd)
{

}





int UsersService::receive_command(int fd, std::string commnd)
{
    std::cout <<  "Pull " << std::endl;
    for (int i = 0; i < _users.size(); i++){
        if(_users[i].fd == fd){
            std::cout <<  "ALready here " << std::endl;
            if (_users[i].is_registered)
            {
                process_command(_users[i],commnd);
            }
            else
            {
                registr(_users[i],commnd);
            }
            return (-1);
        }
    }
    std::string pass_word = split(commnd, ' ')[0];
    std::string password = split(commnd, ' ')[1];
    std:: cout << pass_word << " " << password << std::endl;
    User *new_user= new User(fd, 1);
    _users.push_back(*new_user);
    return -2;
}