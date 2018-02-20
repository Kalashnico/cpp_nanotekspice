//
// Created by jdecombe on 19/02/18.
//

#include <Gates.hpp>
#include "Component/Component4023.hpp"

namespace nts {

	Component4023::Component4023(std::string name) : AComponent(14, name)
	{
		this->_pins[2].type = pin::INPUT;
		this->_pins[3].type = pin::INPUT;
		this->_pins[4].type = pin::INPUT;
		this->_pins[5].type = pin::OUTPUT;

		this->_pins[6].type = pin::UNUSED;

		this->_pins[0].type = pin::INPUT;
		this->_pins[1].type = pin::INPUT;
		this->_pins[7].type = pin::INPUT;
		this->_pins[8].type = pin::OUTPUT;

		this->_pins[9].type = pin::OUTPUT;
		this->_pins[10].type = pin::INPUT;
		this->_pins[11].type = pin::INPUT;
		this->_pins[12].type = pin::INPUT;

		this->_pins[13].type = pin::UNUSED;
	}

	Component4023::~Component4023()
	{
	}

	void Component4023::calcOutputs(const size_t &pin)
	{
		if (pin == 6) {
			if (this->compute(3) == Tristate::UNDEFINED ||
				this->compute(4) == Tristate::UNDEFINED ||
				this->compute(5) == Tristate::UNDEFINED)
				_pins[5].value = Tristate::UNDEFINED;
			else if (this->compute(3) == Tristate::FALSE ||
				this->compute(4) == Tristate::FALSE ||
				this->compute(5) == Tristate::FALSE)
				_pins[5].value = Tristate::TRUE;
			else
				_pins[5].value = Tristate::FALSE;
		} else if (pin == 9) {
			if (this->compute(1) == Tristate::UNDEFINED ||
				this->compute(2) == Tristate::UNDEFINED ||
				this->compute(8) == Tristate::UNDEFINED)
				_pins[8].value = Tristate::UNDEFINED;
			else if (this->compute(1) == Tristate::FALSE ||
				this->compute(2) == Tristate::FALSE ||
				this->compute(8) == Tristate::FALSE)
				_pins[8].value = Tristate::TRUE;
			else
				_pins[8].value = Tristate::FALSE;
		} else if (pin == 10) {
			if (this->compute(11) == Tristate::UNDEFINED ||
				this->compute(12) == Tristate::UNDEFINED ||
				this->compute(13) == Tristate::UNDEFINED)
				_pins[9].value = Tristate::UNDEFINED;
			else if (this->compute(11) == Tristate::FALSE ||
				this->compute(12) == Tristate::FALSE ||
				this->compute(13) == Tristate::FALSE)
				_pins[9].value = Tristate::TRUE;
			else
				_pins[9].value = Tristate::FALSE;
		}
	}

	nts::Tristate Component4023::compute(size_t pin)
	{
		if (!_pins[pin - 1].isDirty)
			return _pins[pin - 1].value;
		_pins[pin - 1].isDirty = false;

		if (_pins[pin - 1].type == pin::OUTPUT) {
			this->calcOutputs(pin);
		} else if (_pins[pin - 1].type == pin::INPUT) {
			_pins[pin - 1].value = _pins[pin -
				1].otherPin->owner->compute(
				_pins[pin - 1].otherPin->pos);
		} else
			_pins[pin - 1].value = Tristate::UNDEFINED;
		return _pins[pin - 1].value;
	}

	Component4023 *Create4023(const std::string &name)
	{
		return new nts::Component4023(name);
	}
}
