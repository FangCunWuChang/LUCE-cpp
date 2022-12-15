#include "../../LUCE.h"

int main(int argc, char* argv[]) {
	lua_State* L = luaL_newstate();
	if (!L) { return -1; }

	int ret_value = 0;
	LUCE_TRY {
		luaL_openlibs(L);
		
		luce::createLUCETable(L);
		luce::setENV(L, argc, argv);

		luce::loadCore(L);
		luce::loadGUI(L);
		luce::loadGraphics(L);

		LUCE_RUN(L, "demo1.lua");

		ret_value = luce::getRET(L);
	}
	LUCE_CATCH_EXCEPTION(L);
	
	lua_close(L);
	return ret_value;
}
