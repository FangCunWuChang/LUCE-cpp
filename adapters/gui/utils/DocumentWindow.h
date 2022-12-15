#pragma once

#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	namespace utils {
		class DocumentWindow : public juce::DocumentWindow {
		public:
			DocumentWindow(
				lua_State* appState, const int appAdapterRef,
				const juce::String& name, juce::Colour backgroundColour,
				int requiredButtons, bool addToDesktop);

			void closeButtonPressed() override;
			void minimiseButtonPressed() override;
			void maximiseButtonPressed() override;

		public:
			lua_State* appState;
			const int appAdapterRef;
		};
	}
}