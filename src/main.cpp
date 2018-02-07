#include <iostream>
#include "Component/Component4001.hpp"
#include "Component/ComponentInput.hpp"

int main() {
	nts::Component4001 c1("c1");
	nts::Component4001 c2("c2");
	nts::ComponentInput in1("input", nts::Tristate::FALSE);
	nts::ComponentInput in2("input", nts::Tristate::FALSE);

	c1.setLink(1, in1, 1);
	c1.setLink(2, in2, 1);
	c1.dump();
	in1.dump();
	in2.dump();
	if (c1.compute(3) == nts::Tristate::TRUE)
		std::cout << "toto" << std::endl;
	return 0;
}