#include "../Defs.h"

namespace luce {
	using PointInt = juce::Point<int>;

	LUCE_METHOD(getX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointInt);
		lua_pushinteger(L, pInstance->getX());
		return 1;
	}

	LUCE_METHOD(getY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointInt);
		lua_pushinteger(L, pInstance->getY());
		return 1;
	}

	LUCE_METHOD(setX) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointInt);
		pInstance->setX(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD(setY) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, PointInt);
		pInstance->setY(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD_LIST(PointInt,
		getX,
		getY,
		setX,
		setY,
	);
	LUCE_STATIC_METHOD_LIST(PointInt);

	LUCE_NEW(PointInt) {
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2)) {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, PointInt, pInstance,
				(int)lua_tonumber(L, 1), (int)lua_tonumber(L, 2));
		}
		else {
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, PointInt, pInstance);
		}
		return 1;
	}
}