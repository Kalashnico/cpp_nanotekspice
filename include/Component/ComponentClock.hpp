//
// Created by Nicolas Guerin on 13/02/2018.
//

#ifndef COMPONENTCLOCK_HPP
#define COMPONENTCLOCK_HPP

#include "AComponent.hpp"

namespace nts {

        class ComponentClock : public AComponent {

                public:
                        ComponentClock(std::string name, nts::Tristate value);
                        ~ComponentClock();
                        Tristate compute(size_t pin = 1) override;
        };
        ComponentClock *CreateClock(const std::string &name);
}


#endif //COMPONENTCLOCK_HPP
