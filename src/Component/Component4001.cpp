//
// Created by Nicolas Guerin on 01/02/2018.
//

#include "Component/Component4001.hpp"

nts::Component4001::Component4001(std::string name)
	: DefaultComponent(14, name)
{
	this->pins[0].type = pin::INPUT;
	this->pins[1].type = pin::INPUT;
	this->pins[2].type = pin::OUTPUT;

	this->pins[3].type = pin::INPUT;
	this->pins[4].type = pin::INPUT;
	this->pins[5].type = pin::OUTPUT;

	this->pins[6].type = pin::UNUSED;

	this->pins[7].type = pin::INPUT;
	this->pins[8].type = pin::INPUT;
	this->pins[9].type = pin::OUTPUT;

	this->pins[10].type = pin::INPUT;
	this->pins[11].type = pin::INPUT;
	this->pins[12].type = pin::OUTPUT;

	this->pins[13].type = pin::UNUSED;

	for (unsigned int i = 0; i < this->pinNumber; i++) {
		this->pins[i].value = UNDEFINED;
	}
}

nts::Component4001::~Component4001()
{
}

nts::Tristate nts::Component4001::compute(size_t pin)
{
	(void)pin;
	return UNDEFINED;
}

