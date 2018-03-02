//
// Created by Nicolas Guerin on 12/02/2018.
//

#include <iostream>
#include <sstream>
#include "../include/Server/Server.hpp"

int main(int ac, char **av)
{
	if (ac == 1)
		return 84;
	Server server(atoi(av[1]));
	server.runServer(av);
	return 0;
}
