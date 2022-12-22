#include "../Defs.h"

namespace luce {
	using juce::MouseEvent;

	LUCE_METHOD_LIST(MouseEvent);
	LUCE_STATIC_METHOD_LIST(MouseEvent);

	LUCE_NEW(MouseEvent) {
		//LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, MouseEvent, pInstance);				/**< MouseEvent() */
		//return 1;
		return 0;
	}
}