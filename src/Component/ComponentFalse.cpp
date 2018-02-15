//
// Created by jdecombe on 15/02/18.
//

#include "Component/ComponentFalse.hpp"

nts::ComponentFalse::ComponentFalse(std::string name)
	: AComponent(1, name)
{
	this->_pins[0].type = pin::OUTPUT;
}

nts::Tristate nts::ComponentFalse::compute(size_t pin)
{
	(void)pin;
	return nts::Tristate::FALSE;
}

nts::ComponentFalse::~ComponentFalse()
{
}

nts::ComponentFalse *nts::CreateFalse(const std::string &name)
{
	return new ComponentFalse(name);
}
