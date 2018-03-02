//
// Created by Nicolas Guerin on 09/02/2018.
//

#include "Gates.hpp"
#include "Component/Component4081.hpp"

nts::Component4081::Component4081(std::string name)
        : AComponent(14, name)
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

nts::Component4081::~Component4081()
{
}

nts::Tristate nts::Component4081::compute(size_t pin)
{
    pin -= 1;
    if (!_pins[pin].isDirty)
        return _pins[pin].value;
    _pins[pin].isDirty = false;
    if (_pins[pin].type == pin::OUTPUT) {
        if (pin == 2 || pin == 9)
            _pins[pin].value = and_gate(this->compute(pin),
                    this->compute(pin - 1));
        else
            _pins[pin].value = and_gate(this->compute(pin + 2),
                    this->compute(pin + 3));
    } else if (_pins[pin].type == pin::INPUT) {
        _pins[pin].value = _pins[pin].otherPin->owner->compute(
                _pins[pin].otherPin->pos);
    } else
        _pins[pin].value = Tristate::UNDEFINED;
    return _pins[pin].value;
}

nts::Component4081 *nts::Create4081(const std::string &name)
{
	return new Component4081(name);
}
