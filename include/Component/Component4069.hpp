//
// Created by Nicolas Guerin on 09/02/2018.
//

#ifndef COMPONENT4069_HPP
#define COMPONENT4069_HPP

#include "DefaultComponent.hpp"

namespace nts {

    class Component4069 : public DefaultComponent {

    public:
        Component4069(std::string name);
        ~Component4069() override;

        Tristate compute(size_t pin) override;
    };
}

#endif //COMPONENT4069_HPP
