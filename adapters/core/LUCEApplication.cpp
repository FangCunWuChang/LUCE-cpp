#include "../Defs.h"
#include "utils/LUCEApplication.h"

namespace luce {
	using utils::LUCEApplication;

	LUCE_METHOD(exec) {
		LUCE_CHECK_USERDATA(L, 1, LUCEApplication);
		int argc = luaL_checkinteger(L, 2);
		luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
		const char** argv = (const char**)(lua_topointer(L, 3));

		lua_pushinteger(L, juce::JUCEApplicationBase::main(JUCE_MAIN_FUNCTION_ARGS));
		return 1;
	}

	LUCE_FUNCTION_LIST(LUCEApplication, exec);

	static juce::JUCEApplicationBase* createApp() { return new utils::ApplicationHelper; }

	LUCE_NEW_FUNCTION(LUCEApplication) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, LUCEApplication, pInstance);
		
		utils::ApplicationHelper::LUCE_state() = L;
		utils::ApplicationHelper::LUCE_ref() = LUCE_REF(L, -1);

		juce::JUCEApplicationBase::createInstance = &createApp;
		return 1;
	}
}
