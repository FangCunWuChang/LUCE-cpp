#include "gui.h"

namespace luce {
	using utils::DocumentWindow;
	using utils::Component;
	using juce::MouseEvent;
	using juce::MouseWheelDetails;
	using juce::Label;
	using juce::Desktop;
	using juce::LookAndFeel;
	using juce::ResizableWindow;
	using juce::PopupMenu;
	using juce::AlertWindow;
	using juce::TextButton;
	using juce::ComboBox;

	int loadGUI(lua_State* L) {
		LUCE_REG(L, DocumentWindow);
		LUCE_REG(L, Component);
		LUCE_REG(L, MouseEvent);
		LUCE_REG(L, MouseWheelDetails);
		LUCE_REG(L, Label);
		LUCE_REG(L, Desktop);
		LUCE_REG(L, LookAndFeel);
		LUCE_REG(L, ResizableWindow);
		LUCE_REG(L, PopupMenu);
		LUCE_REG(L, AlertWindow);
		LUCE_REG(L, TextButton);
		LUCE_REG(L, ComboBox);

		return 0;
	}
}