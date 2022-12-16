#include "gui.h"

namespace luce {
	using utils::DocumentWindow;

	int loadGUI(lua_State* L) {
		LUCE_REG(L, DocumentWindow);

		return 0;
	}
}