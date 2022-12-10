#include "JUCEApplication.h"

namespace luce {
	namespace utils {
		LUCEApplication::LUCEApplication(const juce::String& appName, const juce::String& appVersion)
			: appName(appName), appVersion(appVersion) {}

		const juce::String LUCEApplication::getApplicationName() {
			return this->appName;
		}

		const juce::String LUCEApplication::getApplicationVersion() {
			return this->appVersion;
		}
	}

	luaL_Reg LUCEApplication::__funcList[] = {
		{"test", LUCEApplication::test},
		{NULL, NULL}
	};

	int LUCEApplication::__new(lua_State* L) {
		auto pInstance = reinterpret_cast<LUCEApplication*>(lua_newuserdata(L, sizeof(LUCEApplication)));
		new(pInstance) LUCEApplication();

		luaL_newmetatable(L, "LUCEApplication");

		luaL_setfuncs(L, LUCEApplication::__funcList, 0);

		lua_pushcfunction(L, LUCEApplication::__gc);
		lua_setfield(L, -2, "__gc");

		lua_pushvalue(L, -1);
		lua_setfield(L, -2, "__index");

		lua_setmetatable(L, -2);

		return 1;
	}

	LUCEApplication::LUCEApplication() {
		printf("constructor\n");
	}

	LUCEApplication::~LUCEApplication() {
		printf("destructor\n");
	}

	int LUCEApplication::test(lua_State* L) {
		auto pInstance = reinterpret_cast<LUCEApplication*>(luaL_checkudata(L, 1, "LUCEApplication"));
		auto mes = luaL_checkstring(L, 2);
		pInstance->test(mes);
		return 0;
	}

	void LUCEApplication::test(const char* m) {
		printf("test:%s\n", m);
	}
}
