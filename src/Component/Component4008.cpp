//
// Created by Nicolas Guerin on 19/02/2018.
//

#include <Gates.hpp>
#include "Component/Component4008.hpp"

nts::Component4008::Component4008(std::string name)
        : AComponent(14, name)
{
        this->_pins[0].type = pin::INPUT; //A4
        this->_pins[1].type = pin::INPUT;
        this->_pins[2].type = pin::INPUT;
        this->_pins[3].type = pin::INPUT;
        this->_pins[4].type = pin::INPUT;
        this->_pins[5].type = pin::INPUT;
        this->_pins[6].type = pin::INPUT;

        this->_pins[7].type = pin::UNUSED;

        //Carry In
        this->_pins[8].type = pin::INPUT;

        this->_pins[9].type = pin::OUTPUT;
        this->_pins[10].type = pin::OUTPUT;
        this->_pins[11].type = pin::OUTPUT;
        this->_pins[12].type = pin::OUTPUT;

        //Carry Out
        this->_pins[13].type = pin::OUTPUT;

        this->_pins[14].type = pin::INPUT; //B4

        this->_pins[15].type = pin::UNUSED;

}

nts::Component4008::~Component4008()
{
}



nts::Tristate nts::Component4008::compute(size_t pin)
{
        pin -= 1;
        if (!_pins[pin].isDirty)
                return _pins[pin].value;
        _pins[pin].isDirty = false;
        if (_pins[pin].type == pin::OUTPUT) {
                nts::Tristate tmp = nts::Tristate::UNDEFINED;

                tmp = or_gate(this->_pins[5].value, this->_pins[6].value);
                nts::Tristate sum1 = or_gate(tmp, this->_pins[8].value);

                tmp = or_gate(this->_pins[3].value, this->_pins[4].value);
                nts::Tristate sum2 = or_gate(tmp, sum1);

                tmp = or_gate(this->_pins[1].value, this->_pins[2].value);
                nts::Tristate sum3 = or_gate(tmp, sum2);

                tmp = or_gate(this->_pins[0].value, this->_pins[14].value);
                nts::Tristate sum4 = or_gate(tmp, sum3);

                switch(pin) {
                        case 9:
                                _pins[pin].value = sum1;
                                break;

                        case 10:
                                _pins[pin].value = sum2;
                                break;
                        case 11:
                                _pins[pin].value = sum3;
                                break;
                        case 12:
                                _pins[pin].value = sum4;
                                break;
                        case 13:
                                _pins[pin].value = sum4;
                }
        }
        else if (_pins[pin].type == pin::INPUT) {
                _pins[pin].value = _pins[pin].otherPin->owner->compute(
                        _pins[pin].otherPin->pos);
        }
        else
                _pins[pin].value = Tristate::UNDEFINED;
        return _pins[pin].value;
}

nts::Component4008 *nts::Create4008(const std::string &name)
{
        return new nts::Component4008(name);
}

