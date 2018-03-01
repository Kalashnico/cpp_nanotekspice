//
// Created by Nicolas Guerin on 28/02/2018.
//

#include "../../include/Server/Client.hpp"

Client::Client(int portNumber) : _portNumber(portNumber), _isExit(false)
{

}

Client::~Client()
{

}

void    Client::startClient()
{
        char *ip = "10.10.253.181";

        _client = socket(AF_INET, SOCK_STREAM, 0);
        if (_client < 0) {
                std::cout << "Error creating socket." << std::endl;
                exit(1);
        }

        std::cout << "Client socket created..." << std::endl;

        _client_addr.sin_family = AF_INET;
        _client_addr.sin_port = htons(_portNumber);

        inet_pton(AF_INET, ip, &_client_addr.sin_addr);

        if (connect(_client , (struct sockaddr*)&_client_addr, sizeof(_client_addr)) == 0) {
                std::cout << "Connecting to server." << std::endl;
        }
        recv(_client, _buffer, BUFSIZ, 0);
        std::cout << "Connection confirmed." << std::endl;

        std::cout << "Enter # to end the connection" << std::endl;

        do {
                std::cout << "Client: ";
                do {
                        std::cin >> _buffer;
                        send(_client, _buffer, BUFSIZ, 0);
                        if (*_buffer == '#') {
                                send(_client, _buffer, BUFSIZ, 0);
                                *_buffer = '*';
                                _isExit = true;
                        }
                } while (*_buffer != '*');

                std::cout << "Server: ";

                do {
                        recv(_client, _buffer, BUFSIZ, 0);
                        std::cout << _buffer;
                        if (*_buffer == '#') {
                                *_buffer = '*';
                                _isExit = true;
                        }
                } while (*_buffer != '*');
                std::cout << std::endl;
        } while (!_isExit);

        std::cout << "Connection terminated..." << std::endl;
        close(_client);
}


int     main(void) {
        Client client(4444);
        client.startClient();

        return (0);
}