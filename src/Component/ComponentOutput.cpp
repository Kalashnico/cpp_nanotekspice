//
// Created by jdecombe on 07/02/18.
//

#include "Component/ComponentOutput.hpp"

nts::ComponentOutput::ComponentOutput(std::string name)
	: DefaultComponent(1, name)
{
	pins[0].type = pin::INPUT;
}

nts::ComponentOutput::~ComponentOutput()
{
}

nts::Tristate nts::ComponentOutput::compute(size_t pin)
{
	(void)pin;
	if (pins[0].otherPin) {
		pins[0].value = pins[0].otherPin->owner->compute(
			pins[0].otherPin->pos);
		std::cout << this->name << "=";
		switch (pins[0].value) {
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
	return pins[0].value;
}

nts::ComponentOutput *nts::CreateOutput(const std::string &name)
{
	return new nts::ComponentOutput(name);
}
