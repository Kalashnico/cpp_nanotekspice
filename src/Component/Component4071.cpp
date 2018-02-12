//
// Created by Nicolas Guerin on 09/02/2018.
//

#include "Gates.hpp"
#include "Component/Component4071.hpp"

nts::Component4071::Component4071(std::string name) : DefaultComponent(14, name)
{
	this->pins[0].type = pin::INPUT;
	this->pins[1].type = pin::INPUT;
	this->pins[2].type = pin::OUTPUT;

	this->pins[3].type = pin::OUTPUT;
	this->pins[4].type = pin::INPUT;
	this->pins[5].type = pin::INPUT;

	this->pins[6].type = pin::UNUSED;

	this->pins[7].type = pin::INPUT;
	this->pins[8].type = pin::INPUT;
	this->pins[9].type = pin::OUTPUT;

	this->pins[10].type = pin::OUTPUT;
	this->pins[11].type = pin::INPUT;
	this->pins[12].type = pin::INPUT;

	this->pins[13].type = pin::UNUSED;
}

nts::Component4071::~Component4071()
{
}

nts::Tristate nts::Component4071::compute(size_t pin)
{
	pin -= 1;
	if (pins[pin].type == pin::OUTPUT) {
		pins[pin].value = or_gate(this->compute(pin),
			this->compute(pin - 1));
	} else if (pins[pin].type == pin::INPUT) {
		pins[pin].value = pins[pin].otherPin->owner->compute(
			pins[pin].otherPin->pos);
	} else
		pins[pin].value = Tristate::UNDEFINED;
	return pins[pin].value;
}

nts::Component4071 *nts::Create4071(const std::string &name)
{
	return new nts::Component4071(name);
}
