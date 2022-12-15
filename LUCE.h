#pragma once

/**
 * @brief		LUCE-cpp.
 * @author		WuChang
 * @license		MIT License
 */

#include <JuceHeader.h>
#include <lua.hpp>

#include "Macros.h"
#include "Defs.h"

#include "adapters/core/core.h"
#include "adapters/gui/gui.h"
#include "adapters/graphics/graphics.h"

namespace luce {
	/**
	 * @brief		Create a table named "luce" on global.
	 * 
	 * @param L		The Lua state which you want to create the table.
	 */
	int LUCE_API createLUCETable(lua_State* L);

	/**
	 * @brief		Set command args in the "luce" table.
	 * 
	 * @param L		The Lua state which you want to set args.
	 * @param argc	The count of arguments.
	 * @param argv	The pointer of argument list.
	 */
	int LUCE_API setENV(lua_State* L, int argc, char* argv[]);

	/**
	 * @brief		Get application return code in the "luce" table.
	 * 
	 * @param L		The Lua state which you want to get return code.
	 * 
	 * @return		The return code in the "luce" table.
	 */
	int LUCE_API getRET(lua_State* L);
}
