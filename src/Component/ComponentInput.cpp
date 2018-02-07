//
// Created by jdecombe on 07/02/18.
//

#include "Component/ComponentInput.hpp"

nts::ComponentInput::ComponentInput(std::string name, nts::Tristate value)
	: DefaultComponent(1, name)
{
	pins[0].type = pin::OUTPUT;
	pins[0].value = value;
}

nts::ComponentInput::~ComponentInput()
{
}

nts::Tristate nts::ComponentInput::compute(size_t pin)
{
	return pins[0].value;
}
