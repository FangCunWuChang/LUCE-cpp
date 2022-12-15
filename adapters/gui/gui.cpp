#include "gui.h"

namespace luce {
	int loadGUI(lua_State* L) {
		LUCE_ADAPTER_REG(L, DocumentWindow);

		return 0;
	}
}