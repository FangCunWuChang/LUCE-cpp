#include "../../LUCE.h"

static int wrap_exceptions(lua_State* L, lua_CFunction f) {
	try {
		return f(L);
	}
	catch (const char* s) {
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

int main(int argc, char* argv[]) {
	lua_State* L = luaL_newstate();
	if (!L) { return -1; }

	int ret_value = 0;
	try {
		lua_pushlightuserdata(L, (void*)wrap_exceptions);
		luaJIT_setmode(L, -1, LUAJIT_MODE_WRAPCFUNC | LUAJIT_MODE_ON);
		lua_pop(L, 1);

		luaL_openlibs(L);
		
		luce::createLUCETable(L);
		luce::setENV(L, argc, argv);

		luce::loadCore(L);

		if (luaL_dofile(L, (SCRIPT_DIR "demo1.lua"))) {
			printf(luaL_checkstring(L, -1));
			lua_close(L);
			return -1;
		}

		ret_value = luce::getRET(L);
	}
	catch (...) {
		lua_close(L);
		return -1;
	}
	
	lua_close(L);
	return ret_value;
}
