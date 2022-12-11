#include "core.h"

namespace luce {
	int loadCore(lua_State* L) {

		LUCE_ADAPTER_REG(L, LUCEApplication);
		LUCE_ADAPTER_REG(L, String);

		return 0;
	}
}