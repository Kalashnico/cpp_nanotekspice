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

class Server {
        private:
                int _client;
                int _server;
                int _portNumber;
                bool _isExit;
                char _buffer[BUFSIZ];
                struct sockaddr_in _server_addr;
                socklen_t     _size;

        public:
                explicit Server(int portNumber);
                virtual ~Server();

                void startServer();
};


#endif //SERVER_HPP
