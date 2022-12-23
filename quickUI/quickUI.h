#pragma once

#include "../Defs.h"

namespace luce {
	/**
	 * @brief		Load LUCE QuickUI module.
	 *
	 * @param L		The Lua state which you want to load the module.
	 */
	int LUCE_API loadQuickUI(lua_State* L);
}
