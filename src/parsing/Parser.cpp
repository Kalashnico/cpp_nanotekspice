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
#include "Component/ComponentInput.hpp"
#include "Component/ComponentOutput.hpp"
#include "Component/Component4001.hpp"
#include "Component/Component4011.hpp"
#include "Component/Component4030.hpp"
#include "Component/Component4069.hpp"
#include "Component/Component4071.hpp"
#include "Component/Component4081.hpp"
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
		} else
			throw std::invalid_argument(
				"Error: " + fileName + ": File doesn't exist");
		file.close();
		this->_fileContent = buffer.str();
	}

	Parser::~Parser() = default;

	void Parser::parseFile()
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

	void Parser::dump()
	{
		std::find_if(this->_map.begin(), this->_map.end(), [&](std::pair<std::string, nts::IComponent *> pair) {
			pair.second->dump();
			return false;
		});
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

	static std::map<std::string, std::function
		<nts::IComponent *(std::string)>> chipsetReferenceGenerator()
	{
		std::map<std::string,
			std::function<nts::IComponent *(std::string)>> map;

		map["input"] = &nts::CreateInput;
		map["output"] = &nts::CreateOutput;
		map["4001"] = &nts::Create4001;
		map["4011"] = &nts::Create4011;
		map["4030"] = &nts::Create4030;
		map["4069"] = &nts::Create4069;
		map["4071"] = &nts::Create4071;
		map["4081"] = &nts::Create4081;
		return map;
	}

	static void addMapChipset(std::map<std::string, nts::IComponent *> &map,
		const std::string &line
	)
	{
		static auto chipsetRefs = chipsetReferenceGenerator();
		auto words = str_to_word_tab(line);
		if (words.size() != 2)
			throw std::invalid_argument(
				"Error: \"" + line + "\": Bad Line Format");

		nts::IComponent *component = nullptr;

		if (chipsetRefs.count(words[0]) == 0)
			throw std::invalid_argument(
				"Error: " + words[0] + ": Unknown chipset");
		component = chipsetRefs[words[0]](words[1]);
		if (map.count(words[1]) > 0)
			throw std::invalid_argument("Key already contained");
		map[words[1]] = component;
	}

	static void linkMapChipset(
		std::map<std::string, nts::IComponent *> &map,
		const std::string &line
	)
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

	void Parser::generateGraph()
	{
		for (const auto &line : this->_lines) {
			if (line.second == CHIPSET)
				addMapChipset(this->_map, line.first);
			else
				linkMapChipset(this->_map, line.first);
		}
	}

	void Parser::compute(const std::string &name, int pin)
	{
		if (this->_map.count(name) == 0)
			throw std::invalid_argument(
				name + ": This chipset doesn't exist.");
		this->_map[name]->compute(pin);
	}

	void Parser::compute()
	{
		std::find_if(this->_map.begin(), this->_map.end(), [&](std::pair<std::string, nts::IComponent *> pair) {
			auto output = dynamic_cast<nts::ComponentOutput *>(pair.second);
			if (output)
				pair.second->compute();
			return false;
		});
	}

	void Parser::setNodeValue(const std::string &name, size_t pin,
		nts::Tristate value
	)
	{
		if (this->_map.count(name) == 0)
			throw std::invalid_argument(
				name + ": This chipset doesn't exist.");
		auto pin_cp = this->_map[name]->getPin(pin);
		if (!pin_cp)
			throw std::invalid_argument(
				"Pin requested out of range");
		pin_cp->value = value;
	}
}