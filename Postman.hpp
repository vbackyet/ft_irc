#pragma once 
class Postman
{

    private:



    public:
        char *msg;
        int fd;
        int  sendRequest(int fd, char *msg);
        // int  sendRequestBack(int fd, char *msg);

};
