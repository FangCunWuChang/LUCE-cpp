#include "../Defs.h"

namespace luce {
	using PointFloat = juce::Point<float>;

	LUCE_METHOD(getX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointFloat);
		lua_pushnumber(L, pInstance->getX());
		return 1;
	}

	LUCE_METHOD(getY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointFloat);
		lua_pushnumber(L, pInstance->getY());
		return 1;
	}

	LUCE_METHOD(setX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointFloat);
		pInstance->setX(luaL_checknumber(L, 2));
		return 0;
	}

	LUCE_METHOD(setY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointFloat);
		pInstance->setY(luaL_checknumber(L, 2));
		return 0;
	}

	LUCE_METHOD_LIST(PointFloat,
		getX,
		getY,
		setX,
		setY,
		);
	LUCE_STATIC_METHOD_LIST(PointFloat);

	LUCE_NEW(PointFloat) {
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2)) {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, PointFloat, pInstance,
				(float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2));
		}
		else {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, PointFloat, pInstance);
		}
		return 1;
	}
}