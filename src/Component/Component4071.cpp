//
// Created by Nicolas Guerin on 09/02/2018.
//

#include "Gates.hpp"
#include "Component/Component4071.hpp"

nts::Component4071::Component4071(std::string name) : DefaultComponent(14, name)
{
	this->_pins[0].type = pin::INPUT;
	this->_pins[1].type = pin::INPUT;
	this->_pins[2].type = pin::OUTPUT;

	this->_pins[3].type = pin::OUTPUT;
	this->_pins[4].type = pin::INPUT;
	this->_pins[5].type = pin::INPUT;

	this->_pins[6].type = pin::UNUSED;

	this->_pins[7].type = pin::INPUT;
	this->_pins[8].type = pin::INPUT;
	this->_pins[9].type = pin::OUTPUT;

	this->_pins[10].type = pin::OUTPUT;
	this->_pins[11].type = pin::INPUT;
	this->_pins[12].type = pin::INPUT;

	this->_pins[13].type = pin::UNUSED;
}

nts::Component4071::~Component4071()
{
}

void nts::Component4071::computeNode(size_t pin)
{
 	if (pin == 3 || pin == 10) {
		_pins[pin - 1].value = or_gate(this->compute(pin - 1),
			this->compute(pin - 2));
	} else {
		_pins[pin - 1].value = or_gate(this->compute(pin + 1),
			this->compute(pin + 2));
	}
}

nts::Tristate nts::Component4071::compute(size_t pin)
{
	if (_pins[pin - 1].type == pin::OUTPUT) {
		if (pin < this->_pinNumber)
			computeNode(pin);
	} else if (_pins[pin - 1].type == pin::INPUT) {
		_pins[pin - 1].value = _pins[pin - 1].otherPin->owner->compute(
			_pins[pin - 1].otherPin->pos);
	} else
		_pins[pin - 1].value = Tristate::UNDEFINED;
	return _pins[pin - 1].value;
}

nts::Component4071 *nts::Create4071(const std::string &name)
{
	return new nts::Component4071(name);
}
