#include "Postman.hpp"

// int Postman::sendRequest(int fd, char *msg)
// {
//     this->msg = msg;
//     this->fd = fd;
//     return(0);
// }



int Postman::sendRequest(int fd, char *msg)
{
    this->msg = msg;
    this->fd = fd;
    return(0);
}
