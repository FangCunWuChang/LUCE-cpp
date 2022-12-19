#include "../Defs.h"

namespace luce {
	using juce::MouseEvent;

	LUCE_FUNCTION_LIST(MouseEvent);

	LUCE_NEW_FUNCTION(MouseEvent) {
		//LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, MouseEvent, pInstance);				/**< MouseEvent() */
		//return 1;
		return 0;
	}
}