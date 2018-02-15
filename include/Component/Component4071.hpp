//
// Created by Nicolas Guerin on 09/02/2018.
//

#ifndef COMPONENT4071_HPP
#define COMPONENT4071_HPP

#include "AComponent.hpp"

namespace nts {

	class Component4071 : public AComponent {

		public:
			Component4071(std::string name);

			~Component4071() override;

			Tristate compute(size_t pin) override;

			void computeNode(size_t pin);
	};
	Component4071 *Create4071(const std::string &name);

}

#endif //COMPONENT4071_HPP
