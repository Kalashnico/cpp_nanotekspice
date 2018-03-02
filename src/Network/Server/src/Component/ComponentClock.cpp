//
// Created by Nicolas Guerin on 13/02/2018.
//

#include "Component/ComponentClock.hpp"

nts::ComponentClock::ComponentClock(std::string name, nts::Tristate value)
        : AComponent(1, name)
{
        _pins[0].type = pin::OUTPUT;
        _pins[0].value = value;
}

nts::ComponentClock::~ComponentClock()
{
}

nts::Tristate nts::ComponentClock::compute(size_t pin)
{
        (void)pin;
        if (!_pins[0].isDirty)
                return _pins[0].value;
        _pins[0].isDirty = false;
        if (_pins[0].value == nts::Tristate::FALSE)
                _pins[0].value = nts::Tristate::TRUE;
        else
                _pins[0].value = nts::Tristate::FALSE;
        return _pins[0].value;
}

nts::ComponentClock *nts::CreateClock(const std::string &name)
{
        return new nts::ComponentClock(name, nts::Tristate::TRUE);
}