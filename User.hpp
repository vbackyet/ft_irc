#pragma once
#include <string>
class User
{

    public:
        User(int fd, int flag);
        int fd;
        int is_registered;
        std::string username;
        std::string nickname;
        std::string realname;

};