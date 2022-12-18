#include "gui.h"

namespace luce {
	using utils::DocumentWindow;
	using utils::Component;

	int loadGUI(lua_State* L) {
		LUCE_REG(L, DocumentWindow);
		LUCE_REG(L, Component);

		return 0;
	}
}