#include <iostream>
#include <sstream>
#include "parsing/Token.hpp"
#include "parsing/Parser.hpp"

int main(int ac, char **av)
{


    if (ac == 1)
        return 84;
    try {
        parsing::Parser parser(av[1]);
        parser.parseFile();
        parser.generateGraph();
        parser.setNodeValue("a", 1, nts::Tristate::TRUE);
        parser.setNodeValue("b", 112, nts::Tristate::FALSE);
        parser.compute("s");
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
