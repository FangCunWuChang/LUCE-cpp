#pragma once

#include "LUCEApplication.h"
#include "String.h"

namespace luce {
	/**
	 * @brief		Load LUCE core module.
	 * 
	 * @param L		The Lua state which you want to load the module.
	 */
	int LUCE_API loadCore(lua_State* L);
}