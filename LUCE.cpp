#include "LUCE.h"

namespace luce {
	int createLUCETable(lua_State* L) {
		/** luce table */
		lua_newtable(L);

		/** adapter table */
		lua_pushstring(L, "adapters");
		lua_newtable(L);
		lua_settable(L, -3);

		/** luce table */
		lua_setglobal(L, "luce");

		return 0;
	}

	int setENV(lua_State* L, int argc, char* argv[]) {
		lua_getglobal(L, "luce");

		lua_pushstring(L, "APP_ARGC");
		lua_pushinteger(L, argc);
		lua_settable(L, -3);
		lua_pushstring(L, "APP_ARGV");
		lua_pushlightuserdata(L, argv);
		lua_settable(L, -3);
		lua_pushstring(L, "APP_RET");
		lua_pushinteger(L, 0);
		lua_settable(L, -3);

		lua_pop(L, 1);

		return 0;
	}

	int getRET(lua_State* L) {
		lua_getglobal(L, "luce");

		lua_pushstring(L, "APP_RET");
		lua_gettable(L, -2);
		int ret_value = luaL_checkinteger(L, -1);

		lua_pop(L, 2);

		return ret_value;
	}
}