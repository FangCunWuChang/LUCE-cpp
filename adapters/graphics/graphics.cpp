#include "graphics.h"

namespace luce {
	int loadGraphics(lua_State* L) {
		LUCE_ADAPTER_REG(L, Colour);

		return 0;
	}
}
