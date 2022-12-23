#pragma once

#include "lua.hpp"
#include "Macros.h"

namespace luce {
	/**
	 * @brief		Print the Lua stack.
	 *
	 * @param L		The Lua state.
	 */
	int LUCE_API LUCE_printStack(lua_State* L);

	/**
	 * @brief		Print the LUCE object information.
	 * 
	 * @param L		The Lua state.
	 * @param ud	The index of the object.
	 */
	int LUCE_API LUCE_printObjectInformation(lua_State* L, int ud);

	/**
	 * @brief		Print the current object in refs list.
	 *
	 * @param L		The Lua state.
	 * @param ud	The index of the object.
	 */
	int LUCE_API LUCE_printObjectRefs(lua_State* L, int ud);

	/**
	 * @brief		Print the LUCE object refs list.
	 *
	 * @param L		The Lua state.
	 */
	int LUCE_API LUCE_printAllObjectRefs(lua_State* L);

	/**
	 * @brief		Print the current object data table in datas list.
	 *
	 * @param L		The Lua state.
	 * @param ud	The index of the object.
	 */
	int LUCE_API LUCE_printObjectDatas(lua_State* L, int ud);

	/**
	 * @brief		Print the LUCE object datas list.
	 *
	 * @param L		The Lua state.
	 */
	int LUCE_API LUCE_printAllObjectDatas(lua_State* L);
}