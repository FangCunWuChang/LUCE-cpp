#pragma once

#include "DocumentWindow.h"

namespace luce {
	/**
	 * @brief		Load LUCE gui module.
	 *
	 * @param L		The Lua state which you want to load the module.
	 */
	int LUCE_API loadGUI(lua_State* L);
}
