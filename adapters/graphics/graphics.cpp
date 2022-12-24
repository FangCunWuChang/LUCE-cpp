#include "graphics.h"

namespace luce {
	using juce::Colour;
	using juce::Graphics;
	using RectangleInt = juce::Rectangle<int>;
	using RectangleFloat = juce::Rectangle<float>;
	using PointInt = juce::Point<int>;
	using PointFloat = juce::Point<float>;

	int loadGraphics(lua_State* L) {
		LUCE_REG(L, Colour);
		LUCE_REG(L, Graphics);
		LUCE_REG(L, RectangleInt);
		LUCE_REG(L, RectangleFloat);
		LUCE_REG(L, PointInt);
		LUCE_REG(L, PointFloat);

		return 0;
	}
}
