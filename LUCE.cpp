#include "LUCE.h"

namespace luce {

	int createLUCETable(lua_State* L) {
		/** luce table */
		lua_newtable(L);

		/** refs table */
		lua_newtable(L);

		/** Create refs table metatable */
		lua_newtable(L);
		lua_pushstring(L, "v");
		lua_setfield(L, -2, "__mode");
		lua_setmetatable(L, -2);

		/** Leave refs table */
		lua_setfield(L, -2, "__refs");

		/** luce table */
		lua_setglobal(L, "luce");

		return 0;
	}

	LUCE_SET_ENV_FUNCTION_DEFINATION {
		lua_getglobal(L, "luce");

		lua_pushinteger(L, LUCE_ENV_ARGC);
		lua_setfield(L, -2, "APP_ARGC");
		lua_pushlightuserdata(L, LUCE_ENV_ARGV);
		lua_setfield(L, -2, "APP_ARGV");
		lua_pushinteger(L, 0);
		lua_setfield(L, -2, "APP_RET");

		lua_pop(L, 1);

		return 0;
	}

	int getRET(lua_State* L) {
		lua_getglobal(L, "luce");

		lua_getfield(L, -1, "APP_RET");
		int ret_value = luaL_checkinteger(L, -1);

		lua_pop(L, 2);

		return ret_value;
	}
}