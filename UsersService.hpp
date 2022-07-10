#pragma once
#include "User.hpp"
#include <vector>



class UsersService
{
    public:
        int registr(User _user, std::string commnd);
        std::vector <User> _users;
        // UsersService();
        // ~UsersService();
        int process_command(User _user, std::string commnd);
    
        int receive_command(int fd, std::string commnd);
        int send_command();
};