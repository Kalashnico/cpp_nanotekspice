//
// Created by Nicolas Guerin on 09/02/2018.
//

#ifndef COMPONENT4081_HPP
#define COMPONENT4081_HPP

#include "DefaultComponent.hpp"

namespace nts {

    class Component4081 : public DefaultComponent {

    public:
        Component4081(std::string name);
        ~Component4081() override;

        Tristate compute(size_t pin) override;
    };
}


#endif //COMPONENT4081_HPP
