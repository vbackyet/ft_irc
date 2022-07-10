#include "User.hpp"




User::User(int fd, int flag)
{
        this->fd = fd;
        this->is_registered = flag;
}