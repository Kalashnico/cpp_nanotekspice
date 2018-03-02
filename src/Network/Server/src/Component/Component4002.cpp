//
// Created by Nicolas Guerin on 15/02/2018.
//

#include <Gates.hpp>
#include "Component/Component4002.hpp"

nts::Component4002::Component4002(std::string name)
        : AComponent(14, name)
{
        this->_pins[0].type = pin::OUTPUT;
        this->_pins[1].type = pin::INPUT;
        this->_pins[2].type = pin::INPUT;
        this->_pins[3].type = pin::INPUT;
        this->_pins[4].type = pin::INPUT;

        this->_pins[5].type = pin::UNUSED;
        this->_pins[6].type = pin::UNUSED;
        this->_pins[7].type = pin::UNUSED;

        this->_pins[8].type = pin::INPUT;
        this->_pins[9].type = pin::INPUT;
        this->_pins[10].type = pin::INPUT;
        this->_pins[11].type = pin::INPUT;
        this->_pins[12].type = pin::OUTPUT;

        this->_pins[13].type = pin::UNUSED;
}

nts::Component4002::~Component4002()
{
}


nts::Tristate nts::Component4002::compute(size_t pin)
{
        pin -= 1;
        if (!_pins[pin].isDirty)
                return _pins[pin].value;
        _pins[pin].isDirty = false;
        if (_pins[pin].type == pin::OUTPUT) {
                if (pin == 0){
                        nts::Tristate tmp1 = nor_gate(this->compute(2), this->compute(3));
                        nts::Tristate tmp2 = nor_gate(this->compute(4), this->compute(5));
                        _pins[pin].value = nor_gate(tmp1, tmp2);
                }
                else {
                        nts::Tristate tmp1 = nor_gate(this->compute(12), this->compute(11));
                        nts::Tristate tmp2 = nor_gate(this->compute(10), this->compute(9));
                        _pins[pin].value = nor_gate(tmp1, tmp2);
                }
        } else if (_pins[pin].type == pin::INPUT) {
                _pins[pin].value = _pins[pin].otherPin->owner->compute(
                        _pins[pin].otherPin->pos);
        } else
                _pins[pin].value = Tristate::UNDEFINED;
        return _pins[pin].value;
}

nts::Component4002 *nts::Create4002(const std::string &name)
{
        return new nts::Component4002(name);
}