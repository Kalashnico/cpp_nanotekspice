//
// Created by jdecombe on 06/02/18.
//

#ifndef CPP_NANOTEKSPICE_DEFAULTCOMPONENT_HPP
#define CPP_NANOTEKSPICE_DEFAULTCOMPONENT_HPP

#include <cstring>
#include "IComponent.hpp"

namespace nts {

	class DefaultComponent : public IComponent {
		protected:
			pin::Pin *_pins;
			const size_t _pinNumber;
			const std::string _name;

		public:
			DefaultComponent(size_t pinNumber, std::string name);
			virtual ~DefaultComponent();

			void setLink(std::size_t pin, nts::IComponent &other,
				std::size_t otherPin) override;
			pin::Pin *getPin(size_t idx) override;

			virtual Tristate compute(size_t pin = 1) override = 0;
			virtual void dump() const override;

	};
}

#endif //CPP_NANOTEKSPICE_DEFAULTCOMPONENT_HPP
