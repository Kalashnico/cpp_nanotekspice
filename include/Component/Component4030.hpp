//
// Created by Nicolas Guerin on 09/02/2018.
//

#ifndef COMPONENT4030_HPP
#define COMPONENT4030_HPP

#include "DefaultComponent.hpp"

namespace nts {

	class Component4030 : public DefaultComponent {

	public:
		Component4030(std::string name);
		~Component4030() override;

		Tristate compute(size_t pin) override;
	};
	Component4030 *Create4030(const std::string &name);

}

#endif //COMPONENT4030_HPP
