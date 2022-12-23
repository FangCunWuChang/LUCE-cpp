#include "quickUI.h"

namespace luce {
	using utils::QuickComponent;

	int loadQuickUI(lua_State* L) {
		LUCE_REG(L, QuickComponent);

		return 0;
	}
}
