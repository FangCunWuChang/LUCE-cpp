#include "core.h"

namespace luce {
	int loadCore(lua_State* L) {

		LUCE_REG(L, LUCEApplication);

		return 0;
	}
}