//
// Created by Nicolas Guerin on 15/02/2018.
//

#ifndef COMPONENT4000_HPP
#define COMPONENT4000_HPP

#include "AComponent.hpp"

namespace nts {
        class Component4000 : public AComponent {

                public:
                        Component4000(std::string name);
                        ~Component4000() override;

                        Tristate compute(size_t pin) override;
        };
        Component4000 *Create4000(const std::string &name);
}


#endif //COMPONENT4000_HPP
