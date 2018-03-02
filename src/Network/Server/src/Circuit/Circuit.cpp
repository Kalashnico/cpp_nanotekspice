//
// Created by Nicolas Guerin on 02/02/2018.
//

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <Component/ComponentFalse.hpp>
#include <Component/ComponentTrue.hpp>
#include <Component/ComponentClock.hpp>
#include <Component/Component4023.hpp>
#include "Component/ComponentInput.hpp"
#include "Component/ComponentOutput.hpp"
#include "Component/Component4001.hpp"
#include "Component/Component4011.hpp"
#include "Component/Component4030.hpp"
#include "Component/Component4069.hpp"
#include "Component/Component4071.hpp"
#include "Component/Component4081.hpp"
#include "ComponentGenerator.hpp"
#include "Circuit/Circuit.hpp"
#include "../../include/Server/Server.hpp"

namespace parsing {
	/**
	 * Constructor & Destructor
	 */

	Circuit::Circuit(const std::string &fileName)
	{
		_fileName = fileName;
		std::ifstream file(fileName);
		std::stringstream buffer;

		if (file.good()) {
			buffer << file.rdbuf();
		} else
			throw std::invalid_argument(
				"Error: " + fileName + ": File doesn't exist");
		file.close();
		this->_fileContent = buffer.str();
	}

	Circuit::~Circuit() = default;

	void Circuit::parseFile()
	{
		std::stringstream ss(this->_fileContent);
		std::string tmp;
		LineType lineType = INVALID;

		while (std::getline(ss, tmp, '\n')) {
			if (tmp[0] != '#' && !tmp.empty()) {
				if (std::strcmp(tmp.c_str(), ".chipsets:") ==
					0) {
					lineType = CHIPSET;
					continue;
				}
				if (std::strcmp(tmp.c_str(), ".links:") == 0) {
					lineType = LINKS;
					continue;
				}
				if (lineType == INVALID)
					throw std::invalid_argument(
						"Line out of Chipset/Links scope");
				this->_lines.emplace_back(tmp, lineType);
			}
		}
	}

	void Circuit::dump()
	{
		for (auto elt : _map) {
			elt.second->dump();
		}
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


	static void addMapChipset(std::map<std::string, nts::IComponent *> &map,
		const std::string &line)
	{
		auto words = str_to_word_tab(line);
		if (words.size() != 2)
			throw std::invalid_argument(
				"Error: \"" + line + "\": Bad Line Format");

		if (map.count(words[1]) > 0)
			throw std::invalid_argument("Key already contained");
		nts::IComponent *component =
			createComponent(words[0], words[1]);
		map[words[1]] = component;
	}

	static void linkMapChipset(
		std::map<std::string, nts::IComponent *> &map,
		const std::string &line)
	{
		auto words = str_to_word_tab(line);
		if (words.size() != 2)
			throw std::invalid_argument(
				"Error: " + line + ": Bad Line Format");

		nts::IComponent *tmp;
		int pin;
		for (int i = 0; i < 2; i++) {
			std::string seg_cp;
			std::string seg_pin;
			std::stringstream ss(words[i]);
			std::getline(ss, seg_cp, ':');
			std::getline(ss, seg_pin, ':');
			if (map.count(seg_cp) == 0)
				throw std::invalid_argument(
					seg_cp + ": unknown component");
			if (i == 0) {
				pin = std::atoi(seg_pin.c_str());
				tmp = map[seg_cp];
			} else {
				tmp->setLink(pin, *map[seg_cp],
					std::atoi(seg_pin.c_str()));
			}
		}
	}

	void Circuit::generateGraph()
	{
		for (const auto &line : this->_lines) {
			if (line.second == CHIPSET)
				addMapChipset(this->_map, line.first);
			else
				linkMapChipset(this->_map, line.first);
		}
	}

	void Circuit::compute(const std::string &name, int pin)
	{
		if (this->_map.count(name) == 0)
			throw std::invalid_argument(
				name + ": This chipset doesn't exist.");
		this->_map[name]->compute(pin);
	}

	void Circuit::compute()
	{
		for (auto elt : _map) {
			auto output = dynamic_cast<nts::ComponentOutput *>(elt.second);
			if (output)
				elt.second->compute();
		}
	}

	void Circuit::setNodeValue(const std::string &name, size_t pin,
		nts::Tristate value
	)
	{
		if (this->_map.count(name) == 0)
			throw std::invalid_argument(
				name + ": This chipset doesn't exist.");
		auto chipset_cp = this->_map[name];
		if (!chipset_cp)
			throw ;

		if (dynamic_cast<nts::ComponentInput*>(chipset_cp) == nullptr && dynamic_cast<nts::ComponentClock*>(chipset_cp) == nullptr)
                        throw std::invalid_argument(name +
				": Can't modify this Chipset.");
		auto pin_cp = chipset_cp->getPin(pin);
		if (!pin_cp)
			throw std::invalid_argument(
				"Pin requested out of range");
		pin_cp->value = value;
	}

	void Circuit::displayOutputs()
	{
		for (auto elt : _map) {
			auto output = dynamic_cast<nts::ComponentOutput *>(elt.second);
			if (output)
				output->Display();
		}
	}

	void Circuit::cat()
	{
                std::ifstream f(_fileName);

                std::ostringstream out;

                if (f.is_open()) {
                        out << f.rdbuf();
                        strcat(reply, out.str().c_str());
                        strcat(reply, "\n");
                }
	}

	void Circuit::setCircuitDirty()
	{
		for (auto elt : _map) {
			elt.second->setPinDirty();
		}
	}
}