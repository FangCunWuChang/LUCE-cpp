#include "DocumentWindow.h"

namespace luce {
	namespace utils {
		DocumentWindow::DocumentWindow(
			const juce::String& name, juce::Colour backgroundColour,
			int requiredButtons, bool addToDesktop)
			: juce::DocumentWindow(name, backgroundColour, requiredButtons, addToDesktop)
			{}

		void DocumentWindow::closeButtonPressed() {
			if (!LUCE_GET_STATE()) {
				juce::JUCEApplication::getInstance()->systemRequestedQuit();
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "closeButtonPressed");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				juce::JUCEApplication::getInstance()->systemRequestedQuit();
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_pcall(LUCE_GET_STATE(), 1, 0, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void DocumentWindow::minimiseButtonPressed() {
			if (!LUCE_GET_STATE()) {
				this->juce::DocumentWindow::minimiseButtonPressed();
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "minimiseButtonPressed");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::DocumentWindow::minimiseButtonPressed();
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_pcall(LUCE_GET_STATE(), 1, 0, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}
		
		void DocumentWindow::maximiseButtonPressed() {
			if (!LUCE_GET_STATE()) {
				this->juce::DocumentWindow::maximiseButtonPressed();
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "maximiseButtonPressed");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::DocumentWindow::maximiseButtonPressed();
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_pcall(LUCE_GET_STATE(), 1, 0, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}
	}
}
