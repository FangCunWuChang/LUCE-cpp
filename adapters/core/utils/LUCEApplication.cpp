#include "LUCEApplication.h"

namespace luce {
	namespace utils {
		lua_State* ApplicationHelper::__LUCEState = nullptr;
		int ApplicationHelper::__LUCERef = -1;

		ApplicationHelper::ApplicationHelper() {}

		const juce::String ApplicationHelper::getApplicationName() {
			if (!LUCE_GET_STATE()) {
				return juce::String();
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "getApplicationName");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return juce::String();
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 1);

			auto result = luaL_checkstring(LUCE_GET_STATE(), -1);

			lua_pop(LUCE_GET_STATE(), 2);

			return result;
		}

		const juce::String ApplicationHelper::getApplicationVersion() {
			if (!LUCE_GET_STATE()) {
				return juce::String();
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "getApplicationVersion");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return juce::String();
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 1);

			auto result = luaL_checkstring(LUCE_GET_STATE(), -1);

			lua_pop(LUCE_GET_STATE(), 2);

			return result;
		}

		void ApplicationHelper::initialise(const juce::String& commandLineParameters) {
			if (!LUCE_GET_STATE()) {
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "initialise");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_pushstring(LUCE_GET_STATE(), commandLineParameters.toStdString().c_str());
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void ApplicationHelper::shutdown() {
			if (!LUCE_GET_STATE()) {
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "shutdown");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		bool ApplicationHelper::moreThanOneInstanceAllowed() {
			if (!LUCE_GET_STATE()) {
				return true;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "moreThanOneInstanceAllowed");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return true;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 1);

			auto result = lua_toboolean(LUCE_GET_STATE(), -1);

			lua_pop(LUCE_GET_STATE(), 2);

			return result;
		}

		void ApplicationHelper::anotherInstanceStarted(const juce::String& commandLine) {
			if (!LUCE_GET_STATE()) {
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "anotherInstanceStarted");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_pushstring(LUCE_GET_STATE(), commandLine.toStdString().c_str());
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void ApplicationHelper::suspended() {
			if (!LUCE_GET_STATE()) {
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "suspended");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void ApplicationHelper::resumed() {
			if (!LUCE_GET_STATE()) {
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "resumed");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void ApplicationHelper::memoryWarningReceived() {
			if (!LUCE_GET_STATE()) {
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "memoryWarningReceived");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		bool ApplicationHelper::backButtonPressed() {
			if (!LUCE_GET_STATE()) {
				return false;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "backButtonPressed");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				return false;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 1);

			auto result = lua_toboolean(LUCE_GET_STATE(), -1);

			lua_pop(LUCE_GET_STATE(), 2);

			return result;
		}
	}
}
