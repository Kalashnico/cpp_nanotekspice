//
// Created by Nicolas Guerin on 28/02/2018.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

extern char reply[BUFSIZ];

class Server {
        private:
                int _sockClient;
                int _sockServer;
                int _portNumber;
                char _message[BUFSIZ];
                struct sockaddr_in _server_addr;
                struct sockaddr_in _client_addr;
                socklen_t     _size;

        public:
                explicit Server(int portNumber);
                virtual ~Server();

                void runServer(char **av);
};


#endif //SERVER_HPP
