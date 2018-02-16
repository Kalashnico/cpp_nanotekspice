//
// Created by Nicolas Guerin on 01/02/2018.
//

#ifndef PIN_HPP
#define PIN_HPP

#include "Component/IComponent.hpp"

namespace nts {

	class IComponent;

	enum class Tristate : int {
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
		nts::IComponent *owner;
		size_t pos;
		bool isDirty;
		Pin()
			: isLinked(false), type(UNUSED),
			value(nts::Tristate::UNDEFINED), otherPin(nullptr),
			owner(nullptr), pos(0), isDirty(true)
		{}
    };
}

#endif //PIN_HPP