//
// Created by jdecombe on 07/02/18.
//

#ifndef CPP_NANOTEKSPICE_COMPONENTINPUT_HPP
#define CPP_NANOTEKSPICE_COMPONENTINPUT_HPP

#include "Component/DefaultComponent.hpp"

namespace nts {

	class ComponentInput : public DefaultComponent {

		public:
			ComponentInput(std::string name, nts::Tristate value);
			~ComponentInput();
			Tristate compute(size_t pin = 1) override;
	};
	ComponentInput *CreateInput(const std::string &name);

}


#endif //CPP_NANOTEKSPICE_COMPONENTINPUT_HPP
