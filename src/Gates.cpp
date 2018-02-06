//
// Created by jdecombe on 01/02/18.
//

#include "Gates.hpp"
#include "Component/IComponent.hpp"

nts::Tristate and_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return (a == nts::TRUE && b == nts::TRUE) ? nts::TRUE : nts::FALSE;
}

nts::Tristate or_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return (a == nts::TRUE || b == nts::TRUE) ? nts::TRUE : nts::FALSE;
}

nts::Tristate nand_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return (!(a == nts::TRUE && b == nts::TRUE)) ? nts::TRUE : nts::FALSE;
}

nts::Tristate nor_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return (!(a == nts::TRUE || b == nts::TRUE)) ? nts::TRUE : nts::FALSE;
}

nts::Tristate xor_gate(nts::Tristate a, nts::Tristate b)
{
	if (a == nts::UNDEFINED || b == nts::UNDEFINED)
		return nts::UNDEFINED;
	return (a == nts::TRUE != b == nts::TRUE) ? nts::TRUE : nts::FALSE;
}

nts::Tristate inverter_gate(nts::Tristate &state)
{
	if (state == nts::UNDEFINED)
		return nts::UNDEFINED;
	state = (state == nts::TRUE) ? nts::FALSE : nts::TRUE;
	return state;
}

