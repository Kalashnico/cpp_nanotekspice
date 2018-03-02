//
// Created by jdecombe on 07/02/18.
//

#include "Component/ComponentOutput.hpp"
#include "../../include/Server/Server.hpp"

nts::ComponentOutput::ComponentOutput(std::string name)
	: AComponent(1, name)
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
	} else {
		strcpy(reply, _name.c_str());
		strcat(reply, ": Not linked");
		throw std::invalid_argument(this->_name + ": Not linked");
	}
	return _pins[0].value;
}

void nts::ComponentOutput::Display()
{
	strcat(reply, _name.c_str());
	strcat(reply, "=");
	std::cout << this->_name << "=";
	switch (_pins[0].value) {
		case nts::Tristate::TRUE:
			strcat(reply,"1");
			std::cout << "1" << std::endl;
			break;
		case nts::Tristate::FALSE:
			strcat(reply,"0");
			break;
		default:
			strcat(reply,"U");
	}
}

nts::ComponentOutput *nts::CreateOutput(const std::string &name)
{
	return new nts::ComponentOutput(name);
}
