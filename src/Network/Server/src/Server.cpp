//
// Created by Nicolas Guerin on 28/02/2018.
//

#include <Circuit/Circuit.hpp>
#include <../include/NanoPrompt.hpp>
#include <sstream>
#include "../include/Server/Server.hpp"
#include "../include/NanoPrompt.hpp"


Server::Server(int portNumber) : _portNumber(portNumber)
{
        _sockServer = socket(AF_INET , SOCK_STREAM , 0);
        if (_sockServer == -1)
        {
                std::cerr << "Could not create socket" << std::endl;
        }
        std::cout << "Socket created" << std::endl;

        _server_addr.sin_family = AF_INET;
        _server_addr.sin_addr.s_addr = INADDR_ANY;
        _server_addr.sin_port = htons(_portNumber);

}

Server::~Server()
{

}

void parseInput(char **av, parsing::Circuit &parser)
{
        std::size_t cursor = 3;
        std::string input;
        std::string nb;

        while (av[cursor] != nullptr) {
                std::stringstream ss(av[cursor]);
                std::getline(ss, input, '=');
                std::getline(ss, nb, '=');
                parser.setNodeValue(input, 1,
                                    std::atoi(nb.c_str()) == 1 ? nts::Tristate::TRUE :
                                    nts::Tristate::FALSE);
                ++cursor;
        }
};

void Server::runServer(char **av)
{
        ssize_t readSize;

        if(bind(_sockServer,(struct sockaddr *)&_server_addr , sizeof(_server_addr)) < 0)
        {
                std::cerr << "bind failed. Error" << std::endl;
                exit(1);
        }
        std::cout << "bind done" << std::endl;

        listen(_sockServer , 2);

        std::cout << "Waiting for incoming connections...";
        _size = sizeof(struct sockaddr_in);

        _sockClient = accept(_sockServer, (struct sockaddr *)&_client_addr, (socklen_t*)&_size);
        if (_sockClient < 0)
        {
                std::cerr << "accept failed" << std::endl;
                exit(1);
        }

        std::cout << "Connection accepted" << std::endl;

        try {
                parsing::Circuit parser(av[2]);
                parser.parseFile();
                parser.generateGraph();
                parseInput(av, parser);
                parser.compute();
                parser.setCircuitDirty();
                parser.displayOutputs();
                NanoPrompt nano(parser);

        while((readSize = recv(_sockClient , _message , BUFSIZ , 0)) > 0 )
        {
                std::cout << "received: " << _message << std::endl;
                std::string message(_message);
                nano.run(message);
                write(_sockClient , reply , strlen(reply) + 1);
                memset(_message, 0, BUFSIZ);
                memset(reply, 0, BUFSIZ);
        }

        if(readSize == 0)
        {
                std::cout << "Client disconnected" << std::endl;
        }
        else if(readSize == -1)
        {
                std::cerr << "recv failed" << std::endl;
        }
        } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                exit(84);
        } catch (...) {
                std::cerr << "Caught unknown exception." << std::endl;
        }
}