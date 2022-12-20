#include "gui.h"

namespace luce {
	using utils::DocumentWindow;
	using utils::Component;
	using juce::MouseEvent;
	using juce::MouseWheelDetails;
	using juce::Label;

	int loadGUI(lua_State* L) {
		LUCE_REG(L, DocumentWindow);
		LUCE_REG(L, Component);
		LUCE_REG(L, MouseEvent);
		LUCE_REG(L, MouseWheelDetails);
		LUCE_REG(L, Label);

		return 0;
	}
}