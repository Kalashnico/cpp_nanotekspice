//
// Created by Nicolas Guerin on 02/02/2018.
//

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <Component/ComponentInput.hpp>
#include <Component/ComponentOutput.hpp>
#include <Component/Component4001.hpp>
#include "parsing/Parser.hpp"

namespace parsing {
    /**
     * Constructor & Destructor
     */

        Parser::Parser(const std::string &fileName)
        {
            std::ifstream file(fileName);
            std::stringstream buffer;

            if (file.good()) {
                buffer << file.rdbuf();
            }
            else
                throw std::invalid_argument("Error: " + fileName
			+ ": File doesn't exist");
            file.close();
            this->fileContent = buffer.str();
        }

	Parser::~Parser() = default;

	void Parser::parseFile()
	{
		std::stringstream ss(this->fileContent);
		std::string tmp;
		LineType lineType = INVALID;

		while (std::getline(ss, tmp, '\n')) {
			if (tmp[0] != '#' && !tmp.empty()) {
				if (std::strcmp(tmp.c_str(), ".chipsets:") == 0) {
					lineType = CHIPSET;
					continue;
				}
				if (std::strcmp(tmp.c_str(), ".links:") == 0) {
					lineType = LINKS;
					continue;
				}
				if (lineType == INVALID)
					throw new std::invalid_argument("Invalid File");
				this->lines.emplace_back(tmp, lineType);
			}
		}
	}

	void Parser::dump()
	{
		map["a"]->dump();
		map["b"]->dump();
		map["s"]->dump();
		map["gate"]->dump();
	}

	static std::vector<std::string> str_to_word_tab(std::string str)
	{
		std::istringstream iss(str);
		std::vector<std::string> vec;

		while (iss) {
			std::string word;
			iss >> word;
			if (!word.empty())
				vec.push_back(word);
		}
		return vec;
	}

	static void addMapChipset(std::map<std::string, nts::IComponent *> &map
		, const std::string &line)
	{

		auto words = str_to_word_tab(line);
		if (words.size() != 2)
			throw std::invalid_argument("Error: \"" + line + "\": Bad Line Format");

		nts::IComponent *component = nullptr;

		if (words[0] == "input")
			component = new nts::ComponentInput(words[1], nts::Tristate::UNDEFINED);
		else if (words[0] == "output")
			component = new nts::ComponentOutput(words[1]);
		else if (words[0] == "4001")
			component = new nts::Component4001(words[1]);
		else
			throw std::invalid_argument("Error: " + words[0] + ": Unknown chipset");
		if (map.count(words[1]) > 0)
			throw std::invalid_argument("Key already contained");
		map[words[1]] = component;
	}

	static void linkMapChipset(std::map<std::string, nts::IComponent *>
		&map, const std::string &line)
	{
		auto words = str_to_word_tab(line);
		if (words.size() != 2)
			throw std::invalid_argument("Error: " + line + ": Bad Line Format");

		nts::IComponent *tmp;
		int pin;
		for (int i = 0; i < 2; i++) {
			std::string seg_cp;
			std::string seg_pin;
			std::stringstream ss(words[i]);
			std::getline(ss, seg_cp, ':');
			std::getline(ss, seg_pin, ':');
			if (i == 0) {
				tmp = map[seg_cp];
				pin = std::atoi(seg_pin.c_str());
			} else {
				tmp->setLink(pin, *map[seg_cp],
				std::atoi(seg_pin.c_str()));
			}
		}
	}

	void Parser::generateGraph()
	{
		for (const auto &line : this->lines) {
			if (line.second == CHIPSET)
				addMapChipset(this->map, line.first);
			else
				linkMapChipset(this->map, line.first);
		}
	}

	void Parser::compute(const std::string &name, int pin)
	{
		if (this->map.count(name) == 0)
			throw std::invalid_argument(name + ": This chipset doesn't exist.");
		this->map[name]->compute(pin);
	}

	void Parser::setNodeValue(const std::string &name, size_t pin, nts::Tristate value)
	{
		if (this->map.count(name) == 0)
			throw std::invalid_argument(name + ": This chipset doesn't exist.");
		this->map[name]->getPin(pin)->value = value;
	}
}