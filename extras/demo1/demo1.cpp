#include "../../LUCE.h"

int main(int argc, char* argv[]) {
	lua_State* L = luaL_newstate();
	if (!L) { return -1; }

	int ret_value = 0;
	try {
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
