#pragma once

/**
 * @brief		LUCE-cpp.
 * @author		WuChang
 * @license		MIT License
 */

#include <JuceHeader.h>
#include "lua.hpp"

#include "Macros.h"
#include "Defs.h"
#include "LUCEApplication.h"

#include "adapters/core/core.h"
#include "adapters/gui/gui.h"
#include "adapters/graphics/graphics.h"

#include "quickUI/quickUI.h"

namespace luce {
	/**
	 * @brief		Create a table named "luce" on global.
	 * 
	 * @param L		The Lua state which you want to create the table.
	 */
	int LUCE_API createLUCETable(lua_State* L);
}
