﻿#pragma once

/**
 * @file		Defs-internal.h
 * @author		Wu Chang
 * @brief		Some internal macros and functtions.
 * @attention	Requires C++20.
 */

#define LUCE_MAKE_REG_LIST_INTERNAL49(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL50(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL48(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL49(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL47(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL48(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL46(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL47(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL45(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL46(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL44(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL45(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL43(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL44(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL42(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL43(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL41(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL42(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL40(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL41(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL39(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL40(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL38(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL39(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL37(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL38(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL36(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL37(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL35(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL36(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL34(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL35(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL33(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL34(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL32(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL33(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL31(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL32(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL30(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL31(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL29(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL30(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL28(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL29(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL27(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL28(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL26(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL27(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL25(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL26(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL24(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL25(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL23(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL24(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL22(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL23(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL21(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL22(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL20(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL21(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL19(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL20(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL18(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL19(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL17(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL18(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL16(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL17(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL15(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL16(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL14(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL15(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL13(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL14(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL12(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL13(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL11(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL12(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL10(t, f, ...)		LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL11(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL9(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL10(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL8(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL9(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL7(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL8(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL6(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL7(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL5(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL6(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL4(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL5(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL3(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL4(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL2(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL3(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL1(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL2(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL0(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL1(t, __VA_ARGS__))
#define LUCE_MAKE_REG_LIST_INTERNAL(t, f, ...)			LUCE_TO_LUA_REG(t, f), __VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL0(t, __VA_ARGS__))
