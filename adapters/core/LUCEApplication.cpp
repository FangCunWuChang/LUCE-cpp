#include "LUCEApplication.h"
#include "utils/LUCEApplication.h"

namespace luce {
	LUCE_MAKE_ADAPTER_FUNCTION_LIST(LUCEApplication, exec);

	LUCE_ADAPTER_NEW_WITH_STANDARD_INSTANCES(LUCEApplication) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, LUCEApplication, pInstance);
		return 1;
	}

	static juce::JUCEApplicationBase* createApp() { return new utils::LUCEApplication; }

	LUCEApplication::LUCEApplication()
		: LUCE_Adapter() {
		utils::LUCEApplication::appState = this->__lState;
		utils::LUCEApplication::appAdapterRef = this->__objRef;

		juce::JUCEApplicationBase::createInstance = &createApp;
	}

	LUCE_ADAPTER_METHOD_INTERFACE(LUCEApplication, exec) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, LUCEApplication);
		int argc = luaL_checkinteger(L, 2);
		luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
		const char** argv = (const char**)(lua_topointer(L, 3));
		lua_pushinteger(L, pInstance->exec(argc, argv));
		return 1;
	}

	LUCE_ADAPTER_METHOD(LUCEApplication, exec, int, int argc, const char** argv) {
		return juce::JUCEApplicationBase::main(JUCE_MAIN_FUNCTION_ARGS);
	}
}
