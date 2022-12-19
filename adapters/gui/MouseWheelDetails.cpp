#include "../Defs.h"

namespace luce {
	using juce::MouseWheelDetails;

	LUCE_FUNCTION_LIST(MouseWheelDetails);

	LUCE_NEW_FUNCTION(MouseWheelDetails) {
		//LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, MouseWheelDetails, pInstance);				/**< MouseWheelDetails() */
		//return 1;
		return 0;
	}
}