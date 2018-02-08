//
// Created by Nicolas Guerin on 01/02/2018.
//

<<<<<<< HEAD
#include "Gates.hpp"
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

}

nts::Component4001::~Component4001()
{
}



nts::Tristate nts::Component4001::compute(size_t pin)
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

=======
#include "Component4001.hpp"

nts::Tristate nts::Component4001::compute(size_t pin) {
    return FALSE;
}

void nts::Component4001::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {

}

void nts::Component4001::dump() const {

}
>>>>>>> e833dcbd4c6014a02d0e81e96da17d845aadcdb6
