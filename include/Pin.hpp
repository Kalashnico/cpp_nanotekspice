//
// Created by Nicolas Guerin on 01/02/2018.
//

#ifndef PIN_HPP
#define PIN_HPP

#include "Component/IComponent.hpp"

namespace nts {

	enum Tristate {
		UNDEFINED = (-true),
		TRUE = true,
		FALSE = false
	};
}

namespace pin {

	enum Type {
	    INPUT,
	    OUTPUT,
	    UNUSED
	};

	struct Pin {
		bool isLinked;
                Type type;
                nts::Tristate value;
                Pin *otherPin;
		Pin() : isLinked(false), type(UNUSED), value(nts::UNDEFINED), otherPin(NULL) {}
    };
}

#endif //PIN_HPP