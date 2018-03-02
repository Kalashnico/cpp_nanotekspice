//
// Created by Nicolas Guerin on 15/02/2018.
//

#ifndef COMPONENT4002_HPP
#define COMPONENT4002_HPP
#include "AComponent.hpp"

namespace nts {
        class Component4002 : public AComponent {

                public:
                        Component4002(std::string name);
                        ~Component4002() override;

                        Tristate compute(size_t pin) override;
        };
        Component4002 *Create4002(const std::string &name);
}

#endif //COMPONENT4002_HPP
