#pragma once

#include "../Defs.h"
#include "utils/FlowWindow.h"
#include "utils/FlowComponent.h"

namespace luce {
	/**
	 * @brief		Load LUCE FlowUI module.
	 *
	 * @param L		The Lua state which you want to load the module.
	 */
	int LUCE_API loadFlowUI(lua_State* L);
}
