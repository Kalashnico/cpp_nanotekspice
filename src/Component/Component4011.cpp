//
// Created by Nicolas Guerin on 09/02/2018.
//

#include "Gates.hpp"
#include "Component/Component4011.hpp"

nts::Component4011::Component4011(std::string name)
        : AComponent(14, name)
{
    this->_pins[0].type = pin::INPUT;
    this->_pins[1].type = pin::INPUT;
    this->_pins[2].type = pin::OUTPUT;

    this->_pins[3].type = pin::INPUT;
    this->_pins[4].type = pin::INPUT;
    this->_pins[5].type = pin::OUTPUT;

    this->_pins[6].type = pin::UNUSED;

    this->_pins[7].type = pin::INPUT;
    this->_pins[8].type = pin::INPUT;
    this->_pins[9].type = pin::OUTPUT;

    this->_pins[10].type = pin::INPUT;
    this->_pins[11].type = pin::INPUT;
    this->_pins[12].type = pin::OUTPUT;

    this->_pins[13].type = pin::UNUSED;

}

nts::Component4011::~Component4011()
{
}



nts::Tristate nts::Component4011::compute(size_t pin)
{
    pin -= 1;
    if (!_pins[pin].isDirty)
        return _pins[pin].value;
    _pins[pin].isDirty = false;
    if (_pins[pin].type == pin::OUTPUT) {
        _pins[pin].value = nand_gate(this->compute(pin),
                                  this->compute(pin - 1));
    } else if (_pins[pin].type == pin::INPUT) {
        _pins[pin].value = _pins[pin].otherPin->owner->compute(
                _pins[pin].otherPin->pos);
    } else
        _pins[pin].value = Tristate::UNDEFINED;
    return _pins[pin].value;
}

nts::Component4011 *nts::Create4011(const std::string &name)
{
    return new Component4011(name);
}
