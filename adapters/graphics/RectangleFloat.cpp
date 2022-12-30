#include "../Defs.h"

namespace luce {
	using RectangleFloat = juce::Rectangle<float>;

	LUCE_METHOD(getX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		lua_pushnumber(L, pInstance->getX());
		return 1;
	}

	LUCE_METHOD(getY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		lua_pushnumber(L, pInstance->getY());
		return 1;
	}

	LUCE_METHOD(getWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		lua_pushnumber(L, pInstance->getWidth());
		return 1;
	}

	LUCE_METHOD(getHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		lua_pushnumber(L, pInstance->getHeight());
		return 1;
	}

	LUCE_METHOD(setX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		pInstance->setX(luaL_checknumber(L, 2));
		return 0;
	}

	LUCE_METHOD(setY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		pInstance->setY(luaL_checknumber(L, 2));
		return 0;
	}

	LUCE_METHOD(setWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		pInstance->setWidth(luaL_checknumber(L, 2));
		return 0;
	}

	LUCE_METHOD(setHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleFloat);
		pInstance->setHeight(luaL_checknumber(L, 2));
		return 0;
	}

	LUCE_METHOD_LIST(RectangleFloat,
		getX,
		getY,
		getWidth,
		getHeight,
		setX,
		setY,
		setWidth,
		setHeight
	);
	LUCE_STATIC_METHOD_LIST(RectangleFloat);

	LUCE_NEW(RectangleFloat) {
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) &&
			lua_isnumber(L, 3) && lua_isnumber(L, 4)) {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleFloat, pInstance,
				(float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2),
				(float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4));
		}
		else {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleFloat, pInstance);
		}
		return 1;
	}
}