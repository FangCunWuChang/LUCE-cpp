#include "core.h"

namespace luce {
	using utils::LUCEApplication;
	using juce::String;

	int loadCore(lua_State* L) {
		LUCE_REG(L, LUCEApplication);
		LUCE_REG(L, String);

		return 0;
	}
}