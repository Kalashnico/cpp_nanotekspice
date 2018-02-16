//
// Created by jdecombe on 01/02/18.
//

#include "Gates.hpp"
#include "Component/IComponent.hpp"

nts::Tristate and_gate(nts::Tristate a, nts::Tristate b)
{
	return (a == nts::Tristate::TRUE && b == nts::Tristate::TRUE) ?
		nts::Tristate::TRUE : nts::Tristate::FALSE;
}

nts::Tristate or_gate(nts::Tristate a, nts::Tristate b)
{
	return (a == nts::Tristate::TRUE || b == nts::Tristate::TRUE) ?
		nts::Tristate::TRUE : nts::Tristate::FALSE;
}

nts::Tristate nand_gate(nts::Tristate a, nts::Tristate b)
{
	return (!(a == nts::Tristate::TRUE && b == nts::Tristate::TRUE)) ?
		nts::Tristate::TRUE : nts::Tristate::FALSE;
}

nts::Tristate nor_gate(nts::Tristate a, nts::Tristate b)
{
	return (!(a == nts::Tristate::TRUE || b == nts::Tristate::TRUE)) ?
		nts::Tristate::TRUE : nts::Tristate::FALSE;
}

nts::Tristate xor_gate(nts::Tristate a, nts::Tristate b)
{
	return (a != b) ? nts::Tristate::TRUE : nts::Tristate::FALSE;
}

nts::Tristate inverter_gate(nts::Tristate state)
{
	return (state == nts::Tristate::TRUE) ? nts::Tristate::FALSE : nts::Tristate::TRUE;
}

