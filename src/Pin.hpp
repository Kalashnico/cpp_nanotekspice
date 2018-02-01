//
// Created by Nicolas Guerin on 01/02/2018.
//

#ifndef PIN_HPP
#define PIN_HPP

#include "Component/IComponent.hpp"

namespace pin {
    enum Type {
        INPUT,
        OUTPUT
    };

    struct Pin {
        Type type;
        nts::Tristate value;
        Pin &otherPin;
    };
}

#endif //PIN_HPP