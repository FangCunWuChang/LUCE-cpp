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
}