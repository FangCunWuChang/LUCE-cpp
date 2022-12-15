#include "LUCE.h"

namespace luce {
	namespace utils {
		/**
		 * @brief	Remove ref when object gc.
		 */
		int LUCEObjectGCFunction(lua_State* L) {
			auto adapter = reinterpret_cast<LUCE_AdapterBase*>(lua_touserdata(L, 1));

			/** Get ref table */
			lua_getglobal(L, "luce");
			lua_getfield(L, -1, "__refs");

			/** Remove ref */
			luaL_unref(L, -1, adapter->getParentRef());

			/** Leave luce and ref table */
			lua_pop(L, 2);

			return 0;
		}
		/**
		 * @brief	Bind adapter to object.
		 */
		int LUCEBindFunction(lua_State* L) {
			if (!lua_istable(L, 1)) {
				return luaL_argerror(L, 1, "Isn't table!");
			}
			if (!lua_isuserdata(L, 2)) {
				return luaL_argerror(L, 2, "Isn't userdata!");
			}

			/** Get ref table */
			lua_getglobal(L, "luce");
			lua_getfield(L, -1, "__refs");

			auto adapter = reinterpret_cast<LUCE_AdapterBase*>(lua_touserdata(L, 2));
			lua_pushvalue(L, 1);
			adapter->getParentRef() = luaL_ref(L, -2);

			/** Leave luce and ref table */
			lua_pop(L, 2);

			/** Link adapter to parent */
			lua_pushvalue(L, 2);
			lua_setfield(L, 1, "__adapter");

			/** Get parent metatable */
			lua_getmetatable(L, 1);

			lua_pushcfunction(L, LUCEObjectGCFunction);
			lua_setfield(L, -2, "__gc");
			
			/** Leave ref table */
			lua_pop(L, 1);

			return 0;
		}
		/**
		 * @brief	Bind adapter to object.
		 */
		int LUCENewFunction(lua_State* L) {
			/** Check arg 1 */
			luaL_checktype(L, 1, LUA_TTABLE);

			/** Object */
			lua_newtable(L);

			lua_pushvalue(L, 1);

			lua_pushvalue(L, 1);
			lua_setfield(L, -2, "__index");

			lua_setmetatable(L, -2);

			return 1;
		}
	}

	int createLUCETable(lua_State* L) {
		/** luce table */
		lua_newtable(L);

		/** adapter table */
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

		/** Leave adapters table */
		lua_setfield(L, -2, "adapters");

		/** refs table */
		lua_newtable(L);

		/** Create refs table metatable */
		lua_newtable(L);
		lua_pushstring(L, "v");
		lua_setfield(L, -2, "__mode");
		lua_setmetatable(L, -2);

		/** Leave refs table */
		lua_setfield(L, -2, "__refs");

		/** bind function */
		lua_pushcfunction(L, utils::LUCEBindFunction);
		lua_setfield(L, -2, "bind");

		/** new function */
		lua_pushcfunction(L, utils::LUCENewFunction);
		lua_setfield(L, -2, "new");

		/** luce table */
		lua_setglobal(L, "luce");

		return 0;
	}

	int setENV(lua_State* L, int argc, char* argv[]) {
		lua_getglobal(L, "luce");

		lua_pushinteger(L, argc);
		lua_setfield(L, -2, "APP_ARGC");
		lua_pushlightuserdata(L, argv);
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