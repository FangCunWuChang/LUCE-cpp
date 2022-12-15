#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	LUCE_ADAPTER_WITH_API(Colour) {
		LUCE_ADAPTER_OBJECT(juce::Colour);
	public:
		Colour();
		explicit Colour(juce::uint8 red,
			juce::uint8 green,
			juce::uint8 blue,
			juce::uint8 alpha = 255Ui8);

		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(getRed, juce::uint8);
		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(getGreen, juce::uint8);
		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(getBlue, juce::uint8);
		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(getAlpha, juce::uint8);
		LUCE_ADAPTER_STANDARD_PROPERTIES
	};
}