#include "Debug.h"
#include "Defs.h"

namespace luce {
	int LUCE_printStack(lua_State* L) {
		int num = lua_gettop(L);
		fprintf(stderr, "\n");
		fprintf(stderr, "======================Stack Top======================\n");

		fprintf(stderr, "Index-\tIndex+\tType\t\tValue\n");
		for (int i = num; i > 0; i--) {
			int type = lua_type(L, i);
			switch (type) {
			case LUA_TNONE:
			case LUA_TNIL:
				fprintf(stderr, "%d\t%d\t%s\t\t%s\n",
					(-1 - (num - i)), i,
					lua_typename(L, type), "(null)");
				break;
			case LUA_TBOOLEAN:
				fprintf(stderr, "%d\t%d\t%s\t\t%s\n",
					(-1 - (num - i)), i,
					lua_typename(L, type), lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				fprintf(stderr, "%d\t%d\t%s\t\t%lf\n",
					(-1 - (num - i)), i,
					lua_typename(L, type), lua_tonumber(L, i));
				break;
			case LUA_TSTRING:
				fprintf(stderr, "%d\t%d\t%s\t\t%s\n",
					(-1 - (num - i)), i,
					lua_typename(L, type), lua_tostring(L, i));
				break;
			case LUA_TLIGHTUSERDATA:
			case LUA_TTABLE:
			case LUA_TFUNCTION:
			case LUA_TUSERDATA:
			case LUA_TTHREAD:
				fprintf(stderr, "%d\t%d\t%s\t\t%p\n",
					(-1 - (num - i)), i,
					lua_typename(L, type), lua_topointer(L, i));
				break;
			}
		}

		fprintf(stderr, "\n");
		fprintf(stderr, "Total %d objects in the stack.\n", num);
		fprintf(stderr, "=====================Stack Bottom====================\n");
		fprintf(stderr, "\n");
		return 0;
	}

	int LUCE_printObjectInformation(lua_State* L, int ud) {
		luaL_checktype(L, ud, LUA_TUSERDATA);

		fprintf(stderr, "\n");
		fprintf(stderr, "=====================LUCE Object=====================\n");

		/** Address */
		fprintf(stderr, "address: %p\n", lua_topointer(L, 1));

		/** Meta table */
		lua_getmetatable(L, 1);
		fprintf(stderr, "meta table: %p\n", lua_topointer(L, -1));

		int num = 0;
		lua_pushnil(L);
		while (lua_next(L, -2)) {
			int type = lua_type(L, -1);
			switch (type) {
			case LUA_TNONE:
			case LUA_TNIL:
				fprintf(stderr, "\t%s\t\t\t\t%s : %s\n",
					lua_tostring(L, -2),
					lua_typename(L, type), "(null)");
				break;
			case LUA_TBOOLEAN:
				fprintf(stderr, "\t%s\t\t\t\t%s : %s\n",
					lua_tostring(L, -2),
					lua_typename(L, type), lua_toboolean(L, -1) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				fprintf(stderr, "\t%s\t\t\t\t%s : %lf\n",
					lua_tostring(L, -2),
					lua_typename(L, type), lua_tonumber(L, -1));
				break;
			case LUA_TSTRING:
				fprintf(stderr, "\t%s\t\t\t\t%s : %s\n",
					lua_tostring(L, -2),
					lua_typename(L, type), lua_tostring(L, -1));
				break;
			case LUA_TLIGHTUSERDATA:
			case LUA_TTABLE:
			case LUA_TFUNCTION:
			case LUA_TUSERDATA:
			case LUA_TTHREAD:
				fprintf(stderr, "\t%s\t\t\t\t%s : %p\n",
					lua_tostring(L, -2),
					lua_typename(L, type), lua_topointer(L, -1));
				break;
			}

			lua_pop(L, 1);
			num++;
		}

		/** Leave metatable */
		lua_pop(L, 1);

		fprintf(stderr, "\n");
		fprintf(stderr, "Total %d objects in the meta table.\n", num);
		fprintf(stderr, "=====================================================\n");
		fprintf(stderr, "\n");

		return 0;
	}

	int LUCE_printObjectRefs(lua_State* L, int ud) {
		luaL_checktype(L, ud, LUA_TUSERDATA);

		fprintf(stderr, "\n");
		fprintf(stderr, "===================LUCE Object Refs===================\n");

		/** Object address */
		fprintf(stderr, "object address: %p\n", lua_topointer(L, 1));

		/** __refs table */
		lua_getglobal(L, "luce");
		lua_getfield(L, -1, "__refs");
		fprintf(stderr, "__refs table: %p\n", lua_topointer(L, -1));
		
		int num = 0;
		int count = 0;
		lua_pushnil(L);
		while (lua_next(L, -2)) {
			if (lua_topointer(L, -1) == lua_topointer(L, 1)) {
				fprintf(stderr, "\t[%d]\t\t%p\n",
					(int)lua_tointeger(L, -2),
					lua_topointer(L, -1));
				count++;
			}
			lua_pop(L, 1);
			num++;
		}

		/** Leave luce table */
		lua_pop(L, 2);

		fprintf(stderr, "\n");
		fprintf(stderr, "Total %d objects in the __refs table. %d is the ref of current object.\n", num, count);
		fprintf(stderr, "======================================================\n");
		fprintf(stderr, "\n");

		return 0;
	}

	int LUCE_printAllObjectRefs(lua_State* L) {
		fprintf(stderr, "\n");
		fprintf(stderr, "=================LUCE All Object Refs=================\n");

		/** __refs table */
		lua_getglobal(L, "luce");
		lua_getfield(L, -1, "__refs");
		fprintf(stderr, "__refs table: %p\n", lua_topointer(L, -1));

		int num = 0;

		lua_pushnil(L);
		while (lua_next(L, -2)) {
			fprintf(stderr, "\t[%d]\t\t%p\n",
				(int)lua_tointeger(L, -2),
				lua_topointer(L, -1));
			lua_pop(L, 1);
			num++;
		}

		/** Leave luce table */
		lua_pop(L, 2);

		fprintf(stderr, "\n");
		fprintf(stderr, "Total %d objects in the __refs table.\n", num);
		fprintf(stderr, "======================================================\n");
		fprintf(stderr, "\n");

		return 0;
	}
}
