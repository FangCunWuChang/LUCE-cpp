#pragma once

#include "../Defs.h"

namespace luce {
	/**
	 * @brief		Load LUCE graphics module.
	 *
	 * @param L		The Lua state which you want to load the module.
	 */
	int LUCE_API loadGraphics(lua_State* L);
}