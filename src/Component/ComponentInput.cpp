//
// Created by jdecombe on 07/02/18.
//

#include "Component/ComponentInput.hpp"

nts::ComponentInput::ComponentInput(std::string name, nts::Tristate value)
	: AComponent(1, name)
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
	if (_pins[0].value == Tristate::UNDEFINED)
		throw std::invalid_argument(_name + ": Input pin can't be uninitialized.");
	return _pins[0].value;
}

nts::ComponentInput *nts::CreateInput(const std::string &name)
{
	return new nts::ComponentInput(name, nts::Tristate::UNDEFINED);
}
