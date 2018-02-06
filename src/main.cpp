#include <iostream>
#include "Component/Component4001.hpp"

int main() {
	nts::Component4001 c1("c1");
	nts::Component4001 c2("c2");
	c1.setLink(1, c2, 3);
	c1.dump();
	c2.dump();
	if (c1.getPin(1)->otherPin != NULL)
		std::cout << "Hello, World!" << std::endl;
	return 0;
}