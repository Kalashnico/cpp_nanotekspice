//
// Created by Nicolas Guerin on 28/02/2018.
//

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int     main(void)
{
        int client;
        int server;
        int portNb = 4444;
        bool isExit = false;
        char buffer[BUFSIZ];

        char *ip = const_cast<char *>("127.0.0.1");
        struct sockaddr_in server_addr;

        client = socket(AF_INET, SOCK_STREAM, 0);
        if (client < 0) {
                std::cout << "Error creating socket." << std::endl;
                exit(1);
        }

        std::cout << "Client socket created..." << std::endl;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(portNb);

        if (connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
                std::cout << "Connecting to server." << std::endl;
        }
        recv(client, buffer, BUFSIZ, 0);
        std::cout << "Connection confirmed." << std::endl;

        std::cout << "Enter # to end the connection" << std::endl;

        do {
                std::cout << "Client: ";
                do {
                        std::cin >> buffer;
                        send(client, buffer, BUFSIZ, 0);
                        if (*buffer == '#') {
                                send(client, buffer, BUFSIZ, 0);
                                *buffer = '*';
                                isExit = true;
                        }
                } while (*buffer != '*');

                std::cout << "Server: ";

                do {
                        recv(client, buffer, BUFSIZ, 0);
                        std::cout << buffer <<  " ";
                        if (*buffer == '#') {
                                *buffer = '*';
                                isExit = true;
                        }
                } while (*buffer != '*');
                std::cout << std::endl;
        } while (!isExit);

        std::cout << "Connection terminated..." << std::endl;
        close(client);
        return 0;
}