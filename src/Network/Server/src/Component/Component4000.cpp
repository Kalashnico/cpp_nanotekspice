//
// Created by Nicolas Guerin on 15/02/2018.
//

#include <Gates.hpp>
#include "Component/Component4000.hpp"


nts::Component4000::Component4000(std::string name)
        : AComponent(14, name)
{
        this->_pins[0].type = pin::UNUSED;
        this->_pins[1].type = pin::UNUSED;

        this->_pins[2].type = pin::INPUT;
        this->_pins[3].type = pin::INPUT;
        this->_pins[4].type = pin::INPUT;
        this->_pins[5].type = pin::OUTPUT;

        this->_pins[6].type = pin::UNUSED;

        this->_pins[7].type = pin::INPUT;
        this->_pins[8].type = pin::OUTPUT;

        this->_pins[9].type = pin::OUTPUT;
        this->_pins[10].type = pin::INPUT;
        this->_pins[11].type = pin::INPUT;
        this->_pins[12].type = pin::INPUT;

        this->_pins[13].type = pin::UNUSED;
}

nts::Component4000::~Component4000()
{
}


nts::Tristate nts::Component4000::compute(size_t pin)
{
        pin -= 1;
        if (!_pins[pin].isDirty)
                return _pins[pin].value;
	_pins[pin].isDirty = false;
        if (_pins[pin].type == pin::OUTPUT) {
                if (pin == 8) {
                        _pins[pin].value = inverter_gate(_pins[pin - 1].value);
                }
                else if (pin == 5){
                        nts::Tristate tmp = nor_gate(this->compute(pin), this->compute(pin - 1));
                        _pins[pin].value = nor_gate(tmp, this->compute(pin - 2));
                }
                else {
                        nts::Tristate tmp = nor_gate(this->compute(pin + 2), this->compute(pin + 3));
                        _pins[pin].value = nor_gate(tmp, this->compute(pin + 4));
                }
        } else if (_pins[pin].type == pin::INPUT) {
                _pins[pin].value = _pins[pin].otherPin->owner->compute(
                        _pins[pin].otherPin->pos);
        } else
                _pins[pin].value = Tristate::UNDEFINED;
        return _pins[pin].value;
}

nts::Component4000 *nts::Create4000(const std::string &name)
{
        return new nts::Component4000(name);
}