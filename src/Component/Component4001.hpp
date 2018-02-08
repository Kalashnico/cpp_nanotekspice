//
// Created by Nicolas Guerin on 01/02/2018.
//

#ifndef COMPONENT4001_HPP
#define COMPONENT4001_HPP

#include <map>
#include <array>
#include "IComponent.hpp"
#include "../Pin.hpp"

namespace nts {
    class Component4001 : public IComponent {
    private:
        std::array<pin::Pin, 12> _pins;

    public:
        nts::Tristate compute(std::size_t pin = 1) final;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) final;
        void dump() const final;
    };
}


#endif //COMPONENT4001_HPP
