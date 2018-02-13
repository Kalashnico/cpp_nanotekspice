//
// Created by jdecombe on 06/02/18.
//

#include "Component/DefaultComponent.hpp"

nts::DefaultComponent::DefaultComponent(size_t pinNumber, std::string name)
	: _pinNumber(pinNumber), _name(name)
{
	_pins = new pin::Pin[pinNumber];

	for (unsigned int i = 0; i < this->_pinNumber; i++) {
		this->_pins[i].value = Tristate::UNDEFINED;
		this->_pins[i].owner = this;
		this->_pins[i].pos = i + 1;
	}
}

nts::DefaultComponent::~DefaultComponent()
{
	delete _pins;
}

void nts::DefaultComponent::setLink(std::size_t pin, nts::IComponent &other,
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

pin::Pin *nts::DefaultComponent::getPin(size_t idx)
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

void nts::DefaultComponent::dump() const
{
	std::cout << "Node " << this->_name << ":" << std::endl;
	for (size_t i = 1; i <= _pinNumber; i++) {
		std::cout << "\tPin #" << i << " -> ";
		std::cout << "Value: " <<
			TristateToString(_pins[i - 1].value) << ", ";
		std::cout << "Linked: " << std::boolalpha <<
			_pins[i - 1].isLinked << ", ";
		std::cout << "Type: " << PinTypeToString(_pins[i - 1].type)
			<< std::endl;
	}
}
