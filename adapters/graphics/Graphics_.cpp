#include "../Defs.h"

namespace luce {
	using juce::Graphics;

	LUCE_METHOD_LIST(Graphics);
	LUCE_STATIC_METHOD_LIST(Graphics);

	LUCE_NEW(Graphics) {
		//LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Graphics, pInstance);				/**< Graphics() */
		//return 1;
		return 0;
	}
}