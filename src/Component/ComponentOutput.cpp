//
// Created by jdecombe on 07/02/18.
//

#include "Component/ComponentOutput.hpp"

nts::ComponentOutput::ComponentOutput(std::string name)
	: DefaultComponent(1, name)
{
	_pins[0].type = pin::INPUT;
}

nts::ComponentOutput::~ComponentOutput()
{
}

nts::Tristate nts::ComponentOutput::compute(size_t pin)
{
	(void)pin;
	if (_pins[0].otherPin) {
		_pins[0].value = _pins[0].otherPin->owner->compute(
			_pins[0].otherPin->pos);
	} else
		throw std::invalid_argument(this->_name + ": Not linked");
	return _pins[0].value;
}

void nts::ComponentOutput::Display()
{
	std::cout << this->_name << "=";
	switch (_pins[0].value) {
		case nts::Tristate::TRUE:
			std::cout << "1" << std::endl;
			break;
		case nts::Tristate::FALSE:
			std::cout << "0" << std::endl;
			break;
		default:
			std::cout << "U" << std::endl;
	}
}

nts::ComponentOutput *nts::CreateOutput(const std::string &name)
{
	return new nts::ComponentOutput(name);
}
