//
// Created by jdecombe on 07/02/18.
//

#ifndef CPP_NANOTEKSPICE_COMPONENTOUTPUT_HPP
#define CPP_NANOTEKSPICE_COMPONENTOUTPUT_HPP

#include "Component/AComponent.hpp"

namespace nts {

	class ComponentOutput : public AComponent {

		public:
			ComponentOutput(std::string name);

			~ComponentOutput();

			Tristate compute(size_t pin = 1) override;

			void Display();
	};

	ComponentOutput *CreateOutput(const std::string &name);
}

#endif //CPP_NANOTEKSPICE_COMPONENTOUTPUT_HPP
