#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

#include "utils/DocumentWindow.h"

#include "../graphics/Colour.h"

namespace luce {
	LUCE_ADAPTER_WITH_API(DocumentWindow) {
		LUCE_ADAPTER_OBJECT(utils::DocumentWindow);

	public:
		DocumentWindow(
			const juce::String& name, luce::Colour* backgroundColour,
			int requiredButtons, bool addToDesktop);

		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(setVisible, void, bool visible);
		LUCE_ADAPTER_STANDARD_PROPERTIES
	};
}
