/*
** EPITECH PROJECT, 2022
** cpp_nanotekspice
** File description:
** Created by jdecombe,
*/

#include "Component/ComponentOutput.hpp"
#include "Component/Component4001.hpp"
#include "Component/ComponentClock.hpp"
#include "Component/Component4011.hpp"
#include "Component/Component4023.hpp"
#include "Component/Component4030.hpp"
#include "Component/Component4069.hpp"
#include "Component/Component4071.hpp"
#include "Component/Component4081.hpp"
#include "Component/ComponentFalse.hpp"
#include "Component/ComponentTrue.hpp"
#include "Component/ComponentInput.hpp"
#include <functional>
#include <map>
#include <Component/Component4025.hpp>
#include <Component/Component4002.hpp>
#include <Component/Component4000.hpp>

static std::map<std::string, std::function<nts::IComponent *(std::string)>>
	chipsetReferenceGenerator()
{
	std::map<std::string, std::function<nts::IComponent *(std::string
	)>> map;

	map["4000"] = &nts::Create4000;
	map["4001"] = &nts::Create4001;
	map["4002"] = &nts::Create4002;
	map["4011"] = &nts::Create4011;
	map["4023"] = &nts::Create4023;
	map["4025"] = &nts::Create4025;
	map["4030"] = &nts::Create4030;
	map["4069"] = &nts::Create4069;
	map["4071"] = &nts::Create4071;
	map["4081"] = &nts::Create4081;
	map["clock"] = &nts::CreateClock;
	map["false"] = &nts::CreateFalse;
	map["input"] = &nts::CreateInput;
	map["output"] = &nts::CreateOutput;
	map["true"] = &nts::CreateTrue;
	return map;
}

nts::IComponent *createComponent(std::string &type,
	std::string &name)
{
	static auto map = chipsetReferenceGenerator();

	if (map.count(type) == 0)
		throw std::invalid_argument(type + ": Unknown Chipset.");
	return map[type](name);
}