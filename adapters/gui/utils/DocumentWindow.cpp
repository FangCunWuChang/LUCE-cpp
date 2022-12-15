#include "DocumentWindow.h"

namespace luce {
	namespace utils {
		DocumentWindow::DocumentWindow(
			lua_State* appState, const int appAdapterRef,
			const juce::String& name, juce::Colour backgroundColour,
			int requiredButtons, bool addToDesktop)
			: juce::DocumentWindow(name, backgroundColour, requiredButtons, addToDesktop),
			appState(appState), appAdapterRef(appAdapterRef) {

		}

		void DocumentWindow::closeButtonPressed() {
			if (!this->appState) {
				return;
			}

			LUCE_PUSH_OBJ(this->appState, this->appAdapterRef);

			LUCE_PUSH_PARENT(this->appState, -1);

			lua_getfield(this->appState, -1, "closeButtonPressed");
			if (!lua_isfunction(this->appState, -1)) {
				lua_pop(this->appState, 3);
				return;
			}

			lua_pushvalue(this->appState, -2);
			lua_call(this->appState, 1, 0);

			lua_pop(this->appState, 2);
		}

		void DocumentWindow::minimiseButtonPressed() {
			if (!this->appState) {
				return;
			}

			LUCE_PUSH_OBJ(this->appState, this->appAdapterRef);

			LUCE_PUSH_PARENT(this->appState, -1);

			lua_getfield(this->appState, -1, "minimiseButtonPressed");
			if (!lua_isfunction(this->appState, -1)) {
				lua_pop(this->appState, 3);
				return;
			}

			lua_pushvalue(this->appState, -2);
			lua_call(this->appState, 1, 0);

			lua_pop(this->appState, 2);
		}
		
		void DocumentWindow::maximiseButtonPressed() {
			if (!this->appState) {
				return;
			}

			LUCE_PUSH_OBJ(this->appState, this->appAdapterRef);

			LUCE_PUSH_PARENT(this->appState, -1);

			lua_getfield(this->appState, -1, "maximiseButtonPressed");
			if (!lua_isfunction(this->appState, -1)) {
				lua_pop(this->appState, 3);
				return;
			}

			lua_pushvalue(this->appState, -2);
			lua_call(this->appState, 1, 0);

			lua_pop(this->appState, 2);
		}
	}
}
