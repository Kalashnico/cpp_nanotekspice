//
// Created by jdecombe on 19/02/18.
//

#ifndef CPP_NANOTEKSPICE_COMPONENT4023_HPP
#define CPP_NANOTEKSPICE_COMPONENT4023_HPP

#include "AComponent.hpp"

namespace nts {
	class Component4023 : public nts::AComponent {
		public:
			Component4023(std::string name);

			nts::Tristate compute(size_t pin) override;

			~Component4023() override;

			void calcOutputs(const size_t &pin);
	};
	Component4023 *Create4023(const std::string &name);
}

#endif //CPP_NANOTEKSPICE_COMPONENT4023_HPP
