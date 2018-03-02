//
// Created by jdecombe on 15/02/18.
//

#include "Component/ComponentTrue.hpp"

nts::ComponentTrue::ComponentTrue(std::string name)
	: AComponent(1, name)
{
	this->_pins[0].type = pin::OUTPUT;
}

nts::Tristate nts::ComponentTrue::compute(size_t pin)
{
	(void)pin;
	return nts::Tristate::TRUE;
}

nts::ComponentTrue::~ComponentTrue()
{
}

nts::ComponentTrue *nts::CreateTrue(const std::string &name)
{
	return new ComponentTrue(name);
}
