//
// Created by Nicolas Guerin on 19/02/2018.
//

#ifndef COMPONENT4008_HPP
#define COMPONENT4008_HPP

#include "AComponent.hpp"

namespace nts {

        class Component4008 : public AComponent {

                public:
                        Component4008(std::string name);
                        ~Component4008() override;

                        Tristate compute(size_t pin) override;
        };

        Component4008 *Create4008(const std::string &name);

}

#endif //COMPONENT4008_HPP
