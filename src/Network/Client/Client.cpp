//
// Created by Nicolas Guerin on 28/02/2018.
//

#include "../Server/include/Server/Client.hpp"

Client::Client(int portNumber, char *ip) : _portNumber(portNumber), _isExit(false), _ip(ip)
{
        _sockClient = socket(AF_INET , SOCK_STREAM , 0);

        if (_sockClient == -1)
        {
                std::cerr << "Could not create socket." << std::endl;
        }
        std::cout << "Socket created." << std::endl;

        _server_addr.sin_addr.s_addr = inet_addr(_ip);
        _server_addr.sin_family = AF_INET;
        _server_addr.sin_port = htons(_portNumber);
}

Client::~Client()
{

}

void    Client::runClient()
{
        if (connect(_sockClient , (struct sockaddr *)&_server_addr , sizeof(_server_addr)) < 0)
        {
                std::cerr << "Connect failed." << std::endl;
                exit(1);
        }

        std::cout << "Connected." << std::endl;

        while(_isExit != true)
        {
                std::cout << "Enter message: ";
                std::cin >> _message;

                if(send(_sockClient , _message , strlen(_message) , 0) < 0)
                {
                        std::cerr << "Send failed." << std::endl;
                        break;
                }

                if(recv(_sockClient , _reply , BUFSIZ , 0) < 0)
                {
                        std::cerr << "Recv failed." << std::endl;
                        break;
                }

                std::cout << "Server reply: " << _reply << std::endl;
                if (strcmp(_message, "exit") == 0)
                        _isExit = true;
                std::flush(std::cout);
        }
        close(_sockClient);
}


int     main(int ac, char **av) {
        static_cast<void>(ac);
        Client client(atoi(av[1]), av[2]);
        client.runClient();

        return (0);
}