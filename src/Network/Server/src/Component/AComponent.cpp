//
// Created by jdecombe on 06/02/18.
//

#include <functional>
#include <map>
#include <Component/ComponentInput.hpp>
#include <Component/ComponentOutput.hpp>
#include <Component/Component4001.hpp>
#include <Component/Component4011.hpp>
#include <Component/Component4030.hpp>
#include <Component/Component4069.hpp>
#include <Component/Component4071.hpp>
#include <Component/Component4081.hpp>
#include <Component/ComponentClock.hpp>
#include <Component/ComponentTrue.hpp>
#include <Component/ComponentFalse.hpp>
#include <Component/Component4023.hpp>
#include "Component/AComponent.hpp"
#include "../../include/Server/Server.hpp"

char reply[BUFSIZ];

nts::AComponent::AComponent(size_t pinNumber, std::string name)
	: _pinNumber(pinNumber), _name(name)
{
	_pins = std::unique_ptr<pin::Pin[]>(new pin::Pin[pinNumber]);

	for (unsigned int i = 0; i < this->_pinNumber; i++) {
		this->_pins[i].value = Tristate::UNDEFINED;
		this->_pins[i].owner = this;
		this->_pins[i].pos = i + 1;
	}
}

nts::AComponent::~AComponent()
{
	delete _pins.get();
}

void nts::AComponent::setPinDirty()
{
	for (unsigned int i = 0; i < this->_pinNumber; i++) {
		this->_pins[i].isDirty = true;
	}
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other,
	std::size_t otherPin)
{
	if (pin > _pinNumber)
		return;
	if (_pins[pin - 1].type == pin::UNUSED ||
		other.getPin(otherPin)->type == pin::UNUSED)
		return;

	if (_pins[pin - 1].type != other.getPin(otherPin)->type) {
		_pins[pin - 1].isLinked = true;
		other.getPin(otherPin)->isLinked = true;
		_pins[pin - 1].otherPin = other.getPin(otherPin);
		other.getPin(otherPin)->otherPin = &_pins[pin - 1];
	}
}

pin::Pin *nts::AComponent::getPin(size_t idx)
{
	if (idx > _pinNumber)
		return nullptr;
	return &_pins[idx - 1];
}

static std::string TristateToString(nts::Tristate value)
{
	std::string str;

	switch (value) {
	case nts::Tristate::TRUE:
		str = "TRUE";
		break;
	case nts::Tristate::FALSE:
		str = "FALSE";
		break;
	default:
		str = "UNDEFINED";
		break;
	}
	return str;
}

static std::string PinTypeToString(pin::Type value)
{
	std::string str;

	switch (value) {
	case pin::INPUT:
		str = "INPUT";
		break;
	case pin::OUTPUT:
		str = "OUTPUT";
		break;
	default:
		str = "UNUSED";
		break;
	}
	return str;
}

void nts::AComponent::dump() const
{
	strcat(reply, "Node ");
	strcat(reply, _name.c_str());
	strcat(reply, ":\n");
	for (size_t i = 1; i <= _pinNumber; i++) {
		strcat(reply, "\tPin #");
		strcat(reply, std::to_string(i).c_str());
		strcat(reply, " -> ");
		strcat(reply, "Value: ");
		strcat(reply, TristateToString(_pins[i - 1].value).c_str());
		strcat(reply, ", ");
		strcat(reply, "Linked: ");
		strcat(reply, std::to_string(_pins[i - 1].isLinked).c_str());
		strcat(reply, ", ");
		strcat(reply, "Type: ");
		strcat(reply, PinTypeToString(_pins[i - 1].type).c_str());
		strcat(reply, "\n");
	}
}