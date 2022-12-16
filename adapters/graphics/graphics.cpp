#include "graphics.h"

namespace luce {
	using juce::Colour;

	int loadGraphics(lua_State* L) {
		LUCE_REG(L, Colour);

		return 0;
	}
}
