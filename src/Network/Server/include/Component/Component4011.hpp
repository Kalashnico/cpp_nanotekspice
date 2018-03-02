//
// Created by Nicolas Guerin on 09/02/2018.
//

#ifndef COMPONENT4011_HPP
#define COMPONENT4011_HPP

#include "AComponent.hpp"

namespace nts {

	class Component4011 : public AComponent {

		public:
			Component4011(std::string name);

			~Component4011() override;

			Tristate compute(size_t pin) override;
	};

	Component4011 *Create4011(const std::string &name);
}

#endif //COMPONENT4011_HPP
