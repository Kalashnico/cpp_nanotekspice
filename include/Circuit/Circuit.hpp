//m
// Created by Nicolas Guerin on 02/02/2018.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <Component/IComponent.hpp>
#include <map>

namespace parsing {

	enum LineType {
		INVALID,
		CHIPSET,
		LINKS
	};

    class Circuit {
	    private:
		    std::string _fileContent;
		    std::vector<std::pair<std::string, LineType>> _lines;
		    std::map<std::string, nts::IComponent *> _map;
		    std::string	_fileName;

	    public:
		    //Constructor & Destructor
		    explicit Circuit(const std::string &file);
		    virtual ~Circuit();

		    //Member Functions
		    void parseFile();
		    void generateGraph();
		    void dump();
		    void compute(const std::string &name, int pin = 1);
		    void compute();
		    void setNodeValue(const std::string &name, size_t pin, nts::Tristate value);
		    void displayOutputs();
		    void cat();
    };
}

#endif //PARSER_HPP
