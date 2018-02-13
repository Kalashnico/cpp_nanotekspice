//
// Created by jdecombe on 07/02/18.
//

#include "Component/ComponentInput.hpp"

nts::ComponentInput::ComponentInput(std::string name, nts::Tristate value)
	: DefaultComponent(1, name)
{
	_pins[0].type = pin::OUTPUT;
	_pins[0].value = value;
}

nts::ComponentInput::~ComponentInput()
{
}

nts::Tristate nts::ComponentInput::compute(size_t pin)
{
	(void)pin;
	return _pins[0].value;
}

nts::ComponentInput *nts::CreateInput(const std::string &name)
{
	return new nts::ComponentInput(name, nts::Tristate::UNDEFINED);
}
