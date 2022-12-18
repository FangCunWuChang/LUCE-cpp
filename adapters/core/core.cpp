#include "core.h"

namespace luce {
	using juce::String;

	int loadCore(lua_State* L) {
		LUCE_REG(L, String);

		return 0;
	}
}