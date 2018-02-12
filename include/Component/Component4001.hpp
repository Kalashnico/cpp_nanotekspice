//
// Created by Nicolas Guerin on 01/02/2018.
//

#ifndef COMPONENT4001_HPP
#define COMPONENT4001_HPP

#include "DefaultComponent.hpp"

namespace nts {

	class Component4001 : public DefaultComponent {

		public:
			Component4001(std::string name);
			~Component4001() override;

			Tristate compute(size_t pin) override;
	};

	Component4001 *Create4001(const std::string &name);
}


#endif //COMPONENT4001_HPP
