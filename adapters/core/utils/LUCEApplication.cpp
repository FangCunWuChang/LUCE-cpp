#include "LUCEApplication.h"

namespace luce {
	namespace utils {
		lua_State* LUCEApplication::appState = nullptr;
		int LUCEApplication::appAdapterRef = 0;

		LUCEApplication::LUCEApplication() {}

		const juce::String LUCEApplication::getApplicationName() {
			if (!LUCEApplication::appState) {
				return juce::String();
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "getApplicationName");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return juce::String();
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = luaL_checkstring(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 3);

			return result;
		}

		const juce::String LUCEApplication::getApplicationVersion() {
			if (!LUCEApplication::appState) {
				return juce::String();
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "getApplicationVersion");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return juce::String();
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = luaL_checkstring(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 3);

			return result;
		}

		void LUCEApplication::initialise(const juce::String& commandLineParameters) {
			if (!LUCEApplication::appState) {
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "initialise");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_pushstring(LUCEApplication::appState, commandLineParameters.toStdString().c_str());
			lua_call(LUCEApplication::appState, 2, 0);

			lua_pop(LUCEApplication::appState, 2);
		}

		void LUCEApplication::shutdown() {
			if (!LUCEApplication::appState) {
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "shutdown");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 0);

			lua_pop(LUCEApplication::appState, 2);
		}

		bool LUCEApplication::moreThanOneInstanceAllowed() {
			if (!LUCEApplication::appState) {
				return true;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "moreThanOneInstanceAllowed");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return true;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = lua_toboolean(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 3);

			return result;
		}

		void LUCEApplication::anotherInstanceStarted(const juce::String& commandLine) {
			if (!LUCEApplication::appState) {
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "anotherInstanceStarted");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_pushstring(LUCEApplication::appState, commandLine.toStdString().c_str());
			lua_call(LUCEApplication::appState, 2, 0);

			lua_pop(LUCEApplication::appState, 2);
		}

		void LUCEApplication::suspended() {
			if (!LUCEApplication::appState) {
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "suspended");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 0);

			lua_pop(LUCEApplication::appState, 2);
		}

		void LUCEApplication::resumed() {
			if (!LUCEApplication::appState) {
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "resumed");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 0);

			lua_pop(LUCEApplication::appState, 2);
		}

		void LUCEApplication::memoryWarningReceived() {
			if (!LUCEApplication::appState) {
				return;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "memoryWarningReceived");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 0);

			lua_pop(LUCEApplication::appState, 2);
		}

		bool LUCEApplication::backButtonPressed() {
			if (!LUCEApplication::appState) {
				return false;
			}

			LUCE_PUSH_OBJ(LUCEApplication::appState, LUCEApplication::appAdapterRef);

			LUCE_PUSH_PARENT(LUCEApplication::appState, -1);

			lua_getfield(LUCEApplication::appState, -1, "backButtonPressed");
			if (!lua_isfunction(LUCEApplication::appState, -1)) {
				lua_pop(LUCEApplication::appState, 3);
				return false;
			}

			lua_pushvalue(LUCEApplication::appState, -2);
			lua_call(LUCEApplication::appState, 1, 1);

			auto result = lua_toboolean(LUCEApplication::appState, -1);

			lua_pop(LUCEApplication::appState, 3);

			return result;
		}
	}
}
