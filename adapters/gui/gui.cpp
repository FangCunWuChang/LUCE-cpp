#include "gui.h"

namespace luce {
	using utils::DocumentWindow;
	using utils::Component;
	using juce::MouseEvent;
	using juce::MouseWheelDetails;

	int loadGUI(lua_State* L) {
		LUCE_REG(L, DocumentWindow);
		LUCE_REG(L, Component);
		LUCE_REG(L, MouseEvent);
		LUCE_REG(L, MouseWheelDetails);

		return 0;
	}
}