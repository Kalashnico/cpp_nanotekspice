//
// Created by Nicolas Guerin on 15/02/2018.
//

#ifndef COMPONENT4025_HPP
#define COMPONENT4025_HPP

#include "AComponent.hpp"

namespace nts {
        class Component4025 : public AComponent {

                public:
                        Component4025(std::string name);
                        ~Component4025() override;

                        Tristate compute(size_t pin) override;
        };
        Component4025 *Create4025(const std::string &name);
}



#endif //COMPONENT4025_HPP
