#include <iostream>
#include <sstream>
#include "Component/NanoPrompt.hpp"
#include "Component/Component4001.hpp"
#include "Circuit/Circuit.hpp"

void parseInput(char **av, parsing::Circuit &parser)
{
	std::size_t cursor = 2;
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

int main(int ac, char **av)
{
	if (ac == 1)
		return 84;
	try {
		parsing::Circuit parser(av[1]);
		parser.parseFile();
		parser.generateGraph();
		parseInput(av, parser);
		parser.compute();
	    	parser.displayOutputs();
		NanoPrompt nano(parser);
		nano.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	} catch (...) {
		std::cerr << "Caught unknown exception." << std::endl;
	}
	return 0;
}
