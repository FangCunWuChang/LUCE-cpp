#include "../../LUCE.h"

static int wrap_exceptions(lua_State* L, lua_CFunction f)
{
	try {
		return f(L);  // Call wrapped function and return result.
	}
	catch (const char* s) {  // Catch and convert exceptions.
		lua_pushstring(L, s);
	}
	catch (std::exception& e) {
		lua_pushstring(L, e.what());
	}
	catch (...) {
		lua_pushliteral(L, "caught (...)");
	}
	return lua_error(L);
}

int main(int argc, char* argv[])
{
	lua_State* L = luaL_newstate();
	if (!L) { return -1; }

	int ret_value = 0;
	try {
		lua_pushlightuserdata(L, (void*)wrap_exceptions);
		luaJIT_setmode(L, -1, LUAJIT_MODE_WRAPCFUNC | LUAJIT_MODE_ON);
		lua_pop(L, 1);

		lua_newtable(L);
		lua_pushstring(L, "APP_ARGC");
		lua_pushinteger(L, argc);
		lua_settable(L, -3);
		lua_pushstring(L, "APP_ARGV");
		lua_pushlightuserdata(L, argv);
		lua_settable(L, -3);
		lua_pushstring(L, "APP_RET");
		lua_pushinteger(L, 0);
		lua_settable(L, -3);
		lua_setglobal(L, "LUCE_APPENV");

		luaL_openlibs(L);

		if (luaL_dofile(L, (SCRIPT_DIR "demo1.lua"))) {
			printf(luaL_checkstring(L, -1));
			lua_close(L);
			return -1;
		}

		lua_getglobal(L, "LUCE_APPENV");
		lua_pushstring(L, "APP_RET");
		lua_gettable(L, -2);
		ret_value = luaL_checkinteger(L, -1);
		lua_pop(L, -2);
	}
	catch (...) {
		lua_close(L);
		return -1;
	}
	
	lua_close(L);
	return ret_value;
}
