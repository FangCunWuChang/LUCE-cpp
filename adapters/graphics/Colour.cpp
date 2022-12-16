#include "../Defs.h"

namespace luce {
	using juce::Colour;

	LUCE_METHOD(getRed) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getRed());
		return 1;
	}

	LUCE_METHOD(getGreen) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getGreen());
		return 1;
	}

	LUCE_METHOD(getBlue) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getBlue());
		return 1;
	}

	LUCE_METHOD(getAlpha) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getAlpha());
		return 1;
	}

	LUCE_FUNCTION_LIST(Colour, getRed, getGreen, getBlue, getAlpha);

	LUCE_NEW_FUNCTION(Colour) {
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
			if (lua_isnumber(L, 4)) {
				LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pInstance,
					(juce::uint8)lua_tointeger(L, 1), (juce::uint8)lua_tointeger(L, 2),
					(juce::uint8)lua_tointeger(L, 3), (juce::uint8)lua_tointeger(L, 4));	/**< Colour(r, g, b, a) */
				return 1;
			}
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pInstance,
				(juce::uint8)lua_tointeger(L, 1), (juce::uint8)lua_tointeger(L, 2),
				(juce::uint8)lua_tointeger(L, 3));											/**< Colour(r, g, b) */
			return 1;
		}

		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pInstance);				/**< Colour() */
		return 1;
	}
}
