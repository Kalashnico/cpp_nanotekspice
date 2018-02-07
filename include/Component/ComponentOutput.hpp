//
// Created by jdecombe on 07/02/18.
//

#ifndef CPP_NANOTEKSPICE_COMPONENTOUTPUT_HPP
#define CPP_NANOTEKSPICE_COMPONENTOUTPUT_HPP

#include "Component/DefaultComponent.hpp"

namespace nts {

	class ComponentOutput : public DefaultComponent {

		public:
			ComponentOutput(std::string name);
			~ComponentOutput();
			Tristate compute(size_t pin = 1) override;
	};

}


#endif //CPP_NANOTEKSPICE_COMPONENTOUTPUT_HPP
