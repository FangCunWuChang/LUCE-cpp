#include "../Defs.h"

namespace luce {
	using RectangleInt = juce::Rectangle<int>;

	LUCE_METHOD(getX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		lua_pushinteger(L, pInstance->getX());
		return 1;
	}

	LUCE_METHOD(getY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		lua_pushinteger(L, pInstance->getY());
		return 1;
	}

	LUCE_METHOD(getWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		lua_pushinteger(L, pInstance->getWidth());
		return 1;
	}

	LUCE_METHOD(getHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		lua_pushinteger(L, pInstance->getHeight());
		return 1;
	}

	LUCE_METHOD(setX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		pInstance->setX(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD(setY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		pInstance->setY(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD(setWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		pInstance->setWidth(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD(setHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, RectangleInt);
		pInstance->setHeight(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD_LIST(RectangleInt,
		getX,
		getY,
		getWidth,
		getHeight,
		setX,
		setY,
		setWidth,
		setHeight
		);
	LUCE_STATIC_METHOD_LIST(RectangleInt);

	LUCE_NEW(RectangleInt) {
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) &&
			lua_isnumber(L, 3) && lua_isnumber(L, 4)) {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleInt, pInstance,
				(int)lua_tonumber(L, 1), (int)lua_tonumber(L, 2),
				(int)lua_tonumber(L, 3), (int)lua_tonumber(L, 4));
		}
		else {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleInt, pInstance);
		}
		return 1;
	}
}