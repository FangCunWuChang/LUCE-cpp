#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class DocumentWindow : public juce::DocumentWindow {
		public:
			DocumentWindow(
				const juce::String& name, juce::Colour backgroundColour,
				int requiredButtons, bool addToDesktop);

			void closeButtonPressed() override;
			void minimiseButtonPressed() override;
			void maximiseButtonPressed() override;

			LUCE_REF_DATA;
		};
	}
}