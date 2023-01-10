#include "core.h"

namespace luce {
	using juce::String;
	using juce::LocalisedStrings;

	int loadCore(lua_State* L) {
		LUCE_REG(L, String);
		LUCE_REG(L, LocalisedStrings);

		return 0;
	}
}