//
// Created by Nicolas Guerin on 28/02/2018.
//

#include "../../include/Server/Server.hpp"

Server::Server(int portNumber) : _isExit(false), _portNumber(portNumber)
{

}

Server::~Server()
{

}


void Server::startServer()
{
        _client = socket(AF_INET, SOCK_STREAM, 0);
        if (_client < 0) {
                std::cout << "Error establishing connection." << std::endl;
                exit(1);
        }

        std::cout << "Server socket connection created..." << std::endl;

        _server_addr.sin_family = AF_INET;
        _server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        _server_addr.sin_port = htons(_portNumber);

        _size = sizeof(_server_addr);

        if (bind(_client, (struct sockaddr*)&_server_addr, _size) < 0) {
                std::cout << "Error binding socket." << std::endl;
                exit(1);
        }

        std::cout << "Looking for client..." << std::endl;

        listen(_client, 1);

        _server = accept(_client, (struct sockaddr*)&_server_addr, &_size);

        if (_server < 0) {
                std::cout << "Error on accepting client" << std::endl;
                exit(1);
        }

        while (_server > 0) {
                strcpy(_buffer, "Server connected...\n");
                send(_server, _buffer, BUFSIZ, 0);

                std::cout << "Connected with client..." << std::endl;
                std::cout << "Enter # to end the connection" << std::endl;

                std::cout << "Client: ";
                do {
                        recv(_server, _buffer, BUFSIZ, 0);
                        std::cout << _buffer;
                        if (*_buffer == '#'){
                                *_buffer = '*';
                                _isExit = true;
                        }
                } while (*_buffer != '*');

                do {
                        std::cout << "\nServer: ";
                        do {
                                std::cin >> _buffer;
                                send(_server, _buffer, BUFSIZ, 0);
                                if (*_buffer == '#') {
                                        send(_server, _buffer, BUFSIZ, 0);
                                        *_buffer = '*';
                                        _isExit = true;
                                }
                        } while (*_buffer != '*');

                        std::cout << "Client: ";
                        do {
                                recv(_server, _buffer, BUFSIZ, 0);
                                std::cout << _buffer << " ";
                                if (*_buffer == '#') {
                                        *_buffer = '*';
                                        _isExit = true;
                                }
                        } while (*_buffer != '*');
                } while (!_isExit);

                std::cout <<  "Connection terminated..." << std::endl;
                _isExit = false;
                exit(1);
        }
        close(_client);
}

int main(void) {
        Server server(4444);
        server.startServer();
        return 0;
}