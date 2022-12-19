#include "../Defs.h"

namespace luce {
	using juce::Graphics;

	LUCE_FUNCTION_LIST(Graphics);

	LUCE_NEW_FUNCTION(Graphics) {
		//LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Graphics, pInstance);				/**< Graphics() */
		//return 1;
		return 0;
	}
}