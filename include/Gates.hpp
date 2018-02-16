//
// Created by jdecombe on 01/02/18.
//

#ifndef CPP_NANOTEKSPICE_GATES_HPP
#define CPP_NANOTEKSPICE_GATES_HPP

namespace nts {
	enum class Tristate : int;
}

nts::Tristate and_gate(nts::Tristate a, nts::Tristate b);
nts::Tristate or_gate(nts::Tristate a, nts::Tristate b);
nts::Tristate nand_gate(nts::Tristate a, nts::Tristate b);
nts::Tristate nor_gate(nts::Tristate a, nts::Tristate b);
nts::Tristate xor_gate(nts::Tristate a, nts::Tristate b);
nts::Tristate inverter_gate(nts::Tristate state);

#endif //CPP_NANOTEKSPICE_GATES_HPP
