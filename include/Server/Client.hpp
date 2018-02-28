//
// Created by Nicolas Guerin on 28/02/2018.
//

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

class Client {
        private:
                int _client;
                int _portNumber;
                bool _isExit;
                char _buffer[BUFSIZ];
                struct sockaddr_in _server_addr;

        public:
                explicit Client(int portNumber);
                virtual ~Client();

                void    startClient();
};


#endif //CLIENT_HPP
