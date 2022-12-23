#include "LUCE.h"

namespace luce {
	static int createData(lua_State* L) {
		LUCE_CREATE_DATA(L, 1);
		LUCE_PUSH_DATA(L, 1);

		return 1;
	}

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

		/** datas table */
		lua_newtable(L);

		/** Create datas table metatable */
		lua_newtable(L);
		lua_pushstring(L, "k");
		lua_setfield(L, -2, "__mode");
		lua_setmetatable(L, -2);

		/** Leave datas table */
		lua_setfield(L, -2, "__datas");

		/** createData function */
		lua_pushcfunction(L, createData);
		lua_setfield(L, -2, "createData");

		/** Leave luce table */
		lua_setglobal(L, "luce");

		return 0;
	}
}