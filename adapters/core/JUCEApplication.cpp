#include "JUCEApplication.h"

namespace luce {
	namespace utils {
		juce::String LUCEApplication::appName;
		juce::String LUCEApplication::appVersion;

		LUCEApplication::LUCEApplication() {}

		const juce::String LUCEApplication::getApplicationName() {
			return LUCEApplication::appName;
		}

		const juce::String LUCEApplication::getApplicationVersion() {
			return LUCEApplication::appVersion;
		}

		void LUCEApplication::initialise(const juce::String& commandLineParameters) {
			printf("App started! Name:%s Version:%s", this->appName.toStdString().c_str(), this->appVersion.toStdString().c_str());
		}

		void LUCEApplication::shutdown() {

		}
	}

	LUCE_MAKE_ADAPTER_FUNCTION_LIST(LUCEApplication, exec);

	LUCE_ADAPTER_NEW(LUCEApplication) {
		auto appName = luaL_checkstring(L, 1);
		auto appVersion = luaL_checkstring(L, 2);

		auto pInstance = LUCE_CREATE_USERDATA_WITH_METATABLE(L, LUCEApplication);
		LUCE_ADAPTER_INIT(pInstance, appName, appVersion);

		return 1;
	}

	static juce::JUCEApplicationBase* createApp() { return new utils::LUCEApplication; }

	LUCEApplication::LUCEApplication(const juce::String& appName, const juce::String& appVersion) {
		utils::LUCEApplication::appName = appName;
		utils::LUCEApplication::appVersion = appVersion;

		juce::JUCEApplicationBase::createInstance = &createApp;
	}

	int LUCEApplication::exec(lua_State* L) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, LUCEApplication);
		lua_pushinteger(L, pInstance->exec());
		return 1;
	}

	int LUCEApplication::exec() {
		return juce::JUCEApplicationBase::main();
	}
}
