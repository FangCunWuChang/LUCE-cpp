#include "Colour.h"

namespace luce {
	LUCE_MAKE_ADAPTER_FUNCTION_LIST(Colour, getRed, getGreen, getBlue, getAlpha);

	LUCE_ADAPTER_NEW_WITH_STANDARD_INSTANCES(Colour) {
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
			if (lua_isnumber(L, 4)) {
				LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pInstance,
					lua_tointeger(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4));	/**< Colour(r, g, b, a) */
				return 1;
			}
			LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pInstance,
				lua_tointeger(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));								/**< Colour(r, g, b) */
			return 1;
		}

		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pInstance);								/**< Colour() */
		return 1;
	}

	Colour::Colour() {
		this->__object = std::make_unique<juce::Colour>();
	}

	Colour::Colour(juce::uint8 red,
		juce::uint8 green,
		juce::uint8 blue, 
		juce::uint8 alpha) {
		this->__object = std::make_unique<juce::Colour>(red, green, blue, alpha);
	}

	LUCE_ADAPTER_METHOD_INTERFACE(Colour, getRed) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getRed());
		return 1;
	}

	LUCE_ADAPTER_METHOD(Colour, getRed, juce::uint8) {
		return this->__object->getRed();
	}

	LUCE_ADAPTER_METHOD_INTERFACE(Colour, getGreen) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getGreen());
		return 1;
	}

	LUCE_ADAPTER_METHOD(Colour, getGreen, juce::uint8) {
		return this->__object->getGreen();
	}

	LUCE_ADAPTER_METHOD_INTERFACE(Colour, getBlue) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getBlue());
		return 1;
	}

	LUCE_ADAPTER_METHOD(Colour, getBlue, juce::uint8) {
		return this->__object->getBlue();
	}

	LUCE_ADAPTER_METHOD_INTERFACE(Colour, getAlpha) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, Colour);
		lua_pushinteger(L, pInstance->getAlpha());
		return 1;
	}

	LUCE_ADAPTER_METHOD(Colour, getAlpha, juce::uint8) {
		return this->__object->getAlpha();
	}
}
