//
// Created by jdecombe on 15/02/18.
//

#ifndef CPP_NANOTEKSPICE_COMPONENTTRUE_HPP
#define CPP_NANOTEKSPICE_COMPONENTTRUE_HPP
#include "AComponent.hpp"

namespace nts {
	class ComponentTrue : public AComponent {

		public:
			explicit ComponentTrue(std::string name);

			~ComponentTrue() override;

			Tristate compute(size_t pin) override;
	};
	ComponentTrue *CreateTrue(const std::string &name);

}

#endif //CPP_NANOTEKSPICE_COMPONENTTRUE_HPP
