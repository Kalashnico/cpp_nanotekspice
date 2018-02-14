//
// Created by Nicolas Guerin on 12/02/2018.
//

#include <unistd.h>
#include <signal.h>
#include <Component/DefaultComponent.hpp>
#include <sstream>
#include "Component/NanoPrompt.hpp"

static volatile bool  sig = true;

NanoPrompt::NanoPrompt(const parsing::Parser &parser) : _parser(parser)
{
        _cmd["display"] = &NanoPrompt::display;
        _cmd["assign"] = &NanoPrompt::assign;
        _cmd["simulate"] = &NanoPrompt::simulate;
        _cmd["loop"] = &NanoPrompt::loop;
        _cmd["dump"] = &NanoPrompt::dump;
}

NanoPrompt::~NanoPrompt()
{

}

void NanoPrompt::run()
{
        std::string     str;
        std::cout << "> ";

        while (getline(std::cin, str)) {
                if (strcmp(str.c_str() , "exit") == 0)
                        break ;
                else if(str.find("=") != std::string::npos)
                        (this->*(_cmd["assign"]))(str);
                else if (_cmd.count(str) == 1)
                        (this->*(_cmd[str]))("");
                std::cout << "> ";
        }
}

void NanoPrompt::display(std::string string)
{
        static_cast<void>(string);
        _parser.displayOutputs();
}

void NanoPrompt::assign(std::string string)
{
        std::string input;
        std::string nb;
        std::stringstream ss(string);

        std::getline(ss, input, '=');
        std::getline(ss, nb, '=');
        if (atoi(nb.c_str()) > 1) {
                throw std::invalid_argument("Value requested is out of range.");
        }
        _parser.setNodeValue(input, 1,
                            std::atoi(nb.c_str()) == 1 ? nts::Tristate::TRUE :
                            nts::Tristate::FALSE);
}

void NanoPrompt::simulate(std::string string)
{
        static_cast<void>(string);

        _parser.compute();
}


void    sigHandler(int sg)
{
        static_cast<void>(sg);
        sig = false;
}

void NanoPrompt::loop(std::string string)
{
        signal(SIGINT, sigHandler);

        static_cast<void>(string);
        while (1) {
                simulate(string);
                if (sig == false) {
                        sig = true;
                        break;
                }
        }
}

void NanoPrompt::dump(std::string string)
{
        static_cast<void>(string);
        _parser.dump();
}