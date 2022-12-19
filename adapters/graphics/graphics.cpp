#include "graphics.h"

namespace luce {
	using juce::Colour;
	using juce::Graphics;

	int loadGraphics(lua_State* L) {
		LUCE_REG(L, Colour);
		LUCE_REG(L, Graphics);

		return 0;
	}
}
