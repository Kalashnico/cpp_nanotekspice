//
// Created by jdecombe on 15/02/18.
//

#ifndef COMPONENTFALSE_HPP
#define COMPONENTFALSE_HPP

#include "AComponent.hpp"

namespace nts {

	class ComponentFalse : public AComponent {

		public:
			explicit ComponentFalse(std::string name);

			~ComponentFalse() override;

			Tristate compute(size_t pin) override;
	};
	ComponentFalse *CreateFalse(const std::string &name);

}

#endif //COMPONENTFALSE_HPP
