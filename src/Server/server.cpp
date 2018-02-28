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
        struct sockaddr_in server_addr;
        socklen_t     size;

        client = socket(AF_INET, SOCK_STREAM, 0);
        if (client < 0) {
                std::cout << "Error establishing connection." << std::endl;
                exit(1);
        }

        std::cout << "Server socket connection created..." << std::endl;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(portNb);

        if (bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                std::cout << "Error binding socket." << std::endl;
                perror("toto");
                exit(1);
        }

        size = sizeof(server_addr);
        std::cout << "Looking for client..." << std::endl;

        listen(client, 1);

        server = accept(client, (struct sockaddr*)&server_addr, &size);

        if (server < 0) {
                std::cout << "Error on accepting client" << std::endl;
                exit(1);
        }

        while (server > 0) {
                strcpy(buffer, "Server connected...\n");
                send(server, buffer, BUFSIZ, 0);

                std::cout << "Connected with client..." << std::endl;
                std::cout << "Enter # to end the connection" << std::endl;

                std::cout << "Client: ";
                do {
                        recv(server, buffer, BUFSIZ, 0);
                        std::cout << buffer;
                        if (*buffer == '#'){
                                *buffer = '*';
                                isExit = true;
                        }
                } while (*buffer != '*');

                do {
                        std::cout << "\nServer: ";
                        do {
                                std::cin >> buffer;
                                send(server, buffer, BUFSIZ, 0);
                                if (*buffer == '#') {
                                        send(server, buffer, BUFSIZ, 0);
                                        *buffer = '*';
                                        isExit = true;
                                }
                        } while (*buffer != '*');

                        std::cout << "Client: ";
                        do {
                                recv(server, buffer, BUFSIZ, 0);
                                std::cout << buffer << " ";
                                if (*buffer == '#') {
                                        *buffer = '*';
                                        isExit = true;
                                }
                        } while (*buffer != '*');
                } while (!isExit);

                std::cout <<  "Connection terminated..." << std::endl;
                isExit = false;
                exit(1);
        }
        close(client);
        return 0;
}