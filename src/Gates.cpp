//
// Created by jdecombe on 01/02/18.
//

#include "Gates.hpp"
#include "Component/IComponent.hpp"

bool and_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return a && b;
}

bool or_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return a || b;
}

bool nand_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return !(a && b);
}

bool nor_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return !(a || b);
}

bool xor_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return a != b;
}

bool inverter_gate(nts::Tristate &state)
{
	if (state == nts::UNDEFINED)
		return nts::UNDEFINED;
	state = !state;
	return state;
}

