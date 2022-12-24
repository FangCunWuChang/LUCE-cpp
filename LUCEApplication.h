#pragma once
#include "../../Defs.h"

/**
 * @brief		Load LUCE application.
 * 
 * @param n		Application name.
 * @param v		Application version.
 * @param ami	Allow multi instance.
 * @param f		Application main file.
 * @param m		Application module load code.
 */
#define LUCE_APPLICATION(n, v, ami, f, m) \
	class LUCEApplication : public juce::JUCEApplication { \
		std::unique_ptr<lua_State, std::function<void(lua_State*)>> _L = nullptr; \
		 \
	public: \
		const juce::String getApplicationName() override { return n; }; \
		const juce::String getApplicationVersion() override { return v; }; \
		bool moreThanOneInstanceAllowed() override { return ami; }; \
		 \
		void initialise(const juce::String& commandLineParameters) override { \
			this->_L = std::unique_ptr<lua_State, std::function<void(lua_State*)>>( \
				luaL_newstate(), [](lua_State* L) {lua_close(L); }); \
			auto L = this->_L.get(); \
			 \
			luaL_openlibs(L); \
			luce::createLUCETable(L); \
			 \
			{ \
				m \
			} \
			 \
			if (luaL_dofile(L, f)) { \
				fprintf(stderr, luaL_checkstring(L, -1)); \
				quit(); \
				return; \
			} \
			 \
			{ \
				lua_getglobal(L, "luce"); \
				 \
				lua_getfield(L, -1, "initialise"); \
				if (!lua_isfunction(L, -1)) { \
					lua_pop(L, 2); \
					return; \
				} \
				 \
				lua_pushstring(L, commandLineParameters.toStdString().c_str()); \
				lua_call(L, 1, 0); \
				 \
				lua_pop(L, 1); \
			} \
		}; \
		void shutdown() override { \
			auto L = this->_L.get(); \
			 \
			lua_getglobal(L, "luce"); \
			 \
			lua_getfield(L, -1, "shutdown"); \
			if (!lua_isfunction(L, -1)) { \
				lua_pop(L, 2); \
				return; \
			} \
			 \
			lua_call(L, 0, 0); \
			 \
			lua_pop(L, 1); \
		}; \
		void anotherInstanceStarted(const juce::String& commandLine) override { \
			auto L = this->_L.get(); \
			 \
			lua_getglobal(L, "luce"); \
			 \
			lua_getfield(L, -1, "anotherInstanceStarted"); \
			if (!lua_isfunction(L, -1)) { \
				lua_pop(L, 2); \
				return; \
			} \
			 \
			lua_pushstring(L, commandLine.toStdString().c_str()); \
			lua_call(L, 1, 0); \
			 \
			lua_pop(L, 1); \
		}; \
		void suspended() override { \
			auto L = this->_L.get(); \
			 \
			lua_getglobal(L, "luce"); \
			 \
			lua_getfield(L, -1, "suspended"); \
			if (!lua_isfunction(L, -1)) { \
				lua_pop(L, 2); \
				return; \
			} \
			 \
			lua_call(L, 0, 0); \
			 \
			lua_pop(L, 1); \
		}; \
		void resumed() override { \
			auto L = this->_L.get(); \
			 \
			lua_getglobal(L, "luce"); \
			 \
			lua_getfield(L, -1, "resumed"); \
			if (!lua_isfunction(L, -1)) { \
				lua_pop(L, 2); \
				return; \
			} \
			 \
			lua_call(L, 0, 0); \
			 \
			lua_pop(L, 1); \
		}; \
		void memoryWarningReceived() override { \
			auto L = this->_L.get(); \
			 \
			lua_getglobal(L, "luce"); \
			 \
			lua_getfield(L, -1, "memoryWarningReceived"); \
			if (!lua_isfunction(L, -1)) { \
				lua_pop(L, 2); \
				return; \
			} \
			 \
			lua_call(L, 0, 0); \
			 \
			lua_pop(L, 1); \
		}; \
		bool backButtonPressed() override { \
			auto L = this->_L.get(); \
			 \
			lua_getglobal(L, "luce"); \
			 \
			lua_getfield(L, -1, "backButtonPressed"); \
			if (!lua_isfunction(L, -1)) { \
				lua_pop(L, 2); \
				return this->juce::JUCEApplication::backButtonPressed(); \
			} \
			 \
			lua_pushvalue(L, -2); \
			lua_call(L, 1, 1); \
			 \
			auto result = lua_toboolean(L, -1); \
			 \
			lua_pop(L, 2); \
			 \
			return result; \
		}; \
	}; \
	 \
	START_JUCE_APPLICATION(LUCEApplication)
