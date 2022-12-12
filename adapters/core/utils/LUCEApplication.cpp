#include "LUCEApplication.h"

namespace luce {
	namespace utils {
		lua_State* LUCEApplication::appState = nullptr;
		const char* LUCEApplication::appAdapterName = nullptr;
		int LUCEApplication::appAdapterRef = 0;

		LUCEApplication::LUCEApplication() {}

		const juce::String LUCEApplication::getApplicationName() {
			if (!LUCEApplication::appState) {
				return juce::String();
			}

			lua_getglobal(LUCEApplication::appState, "luce");

			lua_getfield(LUCEApplication::appState, -1, "APP_NAME_FUNC");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 2);
				return juce::String();
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterName, LUCEApplication::appAdapterRef);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = luaL_checkstring(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 2);

			return result;
		}

		const juce::String LUCEApplication::getApplicationVersion() {
			if (!LUCEApplication::appState) {
				return juce::String();
			}

			lua_getglobal(LUCEApplication::appState, "luce");

			lua_getfield(LUCEApplication::appState, -1, "APP_VER_FUNC");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 2);
				return juce::String();
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterName, LUCEApplication::appAdapterRef);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = luaL_checkstring(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 2);

			return result;
		}

		void LUCEApplication::initialise(const juce::String& commandLineParameters) {
			if (!LUCEApplication::appState) {
				return;
			}

			lua_getglobal(LUCEApplication::appState, "luce");

			lua_getfield(LUCEApplication::appState, -1, "APP_INIT_FUNC");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 2);
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterName, LUCEApplication::appAdapterRef);
			lua_pushstring(LUCEApplication::appState, commandLineParameters.toStdString().c_str());
			lua_call(LUCEApplication::appState, 2, 0);

			lua_pop(LUCEApplication::appState, 1);
		}

		void LUCEApplication::shutdown() {
			if (!LUCEApplication::appState) {
				return;
			}

			lua_getglobal(LUCEApplication::appState, "luce");

			lua_getfield(LUCEApplication::appState, -1, "APP_SHUTDOWN_FUNC");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 2);
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterName, LUCEApplication::appAdapterRef);
			lua_call(LUCEApplication::appState, 1, 0);

			lua_pop(LUCEApplication::appState, 1);
		}

		bool LUCEApplication::moreThanOneInstanceAllowed() {
			if (!LUCEApplication::appState) {
				return true;
			}

			lua_getglobal(LUCEApplication::appState, "luce");

			lua_getfield(LUCEApplication::appState, -1, "APP_ALLOW_MULTI_FUNC");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 2);
				return true;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterName, LUCEApplication::appAdapterRef);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = lua_toboolean(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 2);

			return result;
		}

		void LUCEApplication::anotherInstanceStarted(const juce::String& commandLine) {
			if (!LUCEApplication::appState) {
				return;
			}

			lua_getglobal(LUCEApplication::appState, "luce");

			lua_getfield(LUCEApplication::appState, -1, "APP_ANOTHER_START_FUNC");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 2);
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterName, LUCEApplication::appAdapterRef);
			lua_pushstring(LUCEApplication::appState, commandLine.toStdString().c_str());
			lua_call(LUCEApplication::appState, 2, 0);

			lua_pop(LUCEApplication::appState, 1);
		}

		void LUCEApplication::systemRequestedQuit() {

		}

		void LUCEApplication::suspended() {

		}

		void LUCEApplication::resumed() {

		}

		void LUCEApplication::unhandledException(const std::exception*,
			const juce::String& sourceFilename,
			int lineNumber) {

		}

		void LUCEApplication::memoryWarningReceived() {

		}

		bool LUCEApplication::backButtonPressed() {
			return false;
		}
	}
}
