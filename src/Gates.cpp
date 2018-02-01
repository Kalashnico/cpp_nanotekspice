//
// Created by jdecombe on 01/02/18.
//

#include "Gates.hpp"

bool and_gate(bool a, bool b)
{
	return a && b;
}

bool or_gate(bool a, bool b)
{
	return a || b;
}

bool nand_gate(bool a, bool b)
{
	return !(a && b);
}

bool nor_gate(bool a, bool b)
{
	return !(a || b);
}

bool flip_flop(bool &state)
{
	state = !state;
	return state;
}

bool xor_gate(bool a, bool b)
{
	return a != b;
}

bool inverter_gate(bool &state)
{
	state = !state;
	return state;
}

