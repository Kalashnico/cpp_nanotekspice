//
// Created by jdecombe on 06/02/18.
//

#include "Component/DefaultComponent.hpp"

nts::DefaultComponent::DefaultComponent(size_t pinNumber, std::string name)
	: pinNumber(pinNumber), name(name)
{
	pins = new pin::Pin[pinNumber];
}

nts::DefaultComponent::~DefaultComponent()
{
	delete pins;
}

void nts::DefaultComponent::setLink(std::size_t pin, nts::IComponent &other,
	std::size_t otherPin)
{
	if (pin > pinNumber)
		return;
	if (pins[pin - 1].type == pin::UNUSED ||
		other.getPin(otherPin)->type == pin::UNUSED)
		return;

	if (pins[pin - 1].type != other.getPin(otherPin)->type) {
		pins[pin - 1].isLinked = true;
		other.getPin(otherPin)->isLinked = true;
		if (pins[pin - 1].type == pin::INPUT)
			pins[pin - 1].otherPin = other.getPin(otherPin);
		else
			other.getPin(otherPin)->otherPin = &pins[pin - 1];
	}
}

pin::Pin *nts::DefaultComponent::getPin(size_t idx)
{
	if (idx > pinNumber)
		return NULL;
	return &pins[idx - 1];
}

static std::string TristateToString(nts::Tristate value)
{
	std::string str;

	switch (value) {
	case nts::TRUE:
		str = "TRUE";
		break;
	case nts::FALSE:
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
	std::cout << "Node " << this->name << ":" << std::endl;
	for (size_t i = 1; i <= pinNumber; i++) {
		std::cout << "\tPin #" << i << " -> ";
		std::cout << "Value: " <<
			TristateToString(pins[i - 1].value) << ", ";
		std::cout << "Linked: " << std::boolalpha <<
			pins[i - 1].isLinked << ", ";
		std::cout << "Type: " << PinTypeToString(pins[i - 1].type)
			<< std::endl;
	}
}
