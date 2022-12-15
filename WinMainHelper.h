#pragma once

#include "Macros.h"

#if _MSC_VER && ! defined(_CONSOLE)

#include <Windows.h>

#define LUCE_MAIN								int __stdcall WinMain (struct HINSTANCE__*, struct HINSTANCE__*, char*, int)

#define LUCE_MAIN_FUNCTION_ARGS
/**
 * @brief		Set command args in the "luce" table.
 *
 * @param L		The Lua state which you want to set args.
 */
#define LUCE_SET_ENV(L)							luce::setENV(L)
#define LUCE_SET_ENV_FUNCTION()					int LUCE_API setENV(lua_State* L)
#define LUCE_SET_ENV_FUNCTION_DEFINATION		int setENV(lua_State* L)
#define LUCE_ENV_ARGC							0
#define LUCE_ENV_ARGV							0

#else

#define LUCE_MAIN								int main (int argc, char* argv[])

#define JUCE_MAIN_FUNCTION_ARGS					argc, (const char**) argv
/**
 * @brief		Set command args in the "luce" table.
 *
 * @param L		The Lua state which you want to set args.
 */
#define LUCE_SET_ENV(L)							luce::setENV(L, argc, argv)
#define LUCE_SET_ENV_FUNCTION()					int LUCE_API setENV(lua_State* L, int argc, char* argv[])
#define LUCE_SET_ENV_FUNCTION_DEFINATION		int setENV(lua_State* L, int argc, char* argv[])
#define LUCE_ENV_ARGC							argc
#define LUCE_ENV_ARGV							argv

#endif
