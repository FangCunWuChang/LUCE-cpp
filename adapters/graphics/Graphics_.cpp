#include "../Defs.h"

namespace luce {
	using juce::Graphics;
	using juce::Colour;
	using RectangleFloat = juce::Rectangle<float>;

	LUCE_METHOD(setColour) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Graphics);
		auto& pColour = LUCE_CHECK_USERDATA(L, 2, Colour);
		pInstance->setColour(*pColour);
		return 0;
	}

	LUCE_METHOD(fillRect) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Graphics);
		auto& pRect = LUCE_CHECK_USERDATA(L, 2, RectangleFloat);
		pInstance->fillRect(*pRect);
		return 0;
	}

	LUCE_METHOD(fillAll) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Graphics);
		auto& pColour = LUCE_CHECK_USERDATA(L, 2, Colour);
		pInstance->fillAll(*pColour);
		return 0;
	}

	LUCE_METHOD(fillRoundedRectangle) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Graphics);
		auto& pRect = LUCE_CHECK_USERDATA(L, 2, RectangleFloat);
		pInstance->fillRoundedRectangle(*pRect, luaL_checknumber(L, 3));
		return 0;
	}

	LUCE_METHOD(drawRect) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Graphics);
		auto& pRect = LUCE_CHECK_USERDATA(L, 2, RectangleFloat);
		if (lua_isnumber(L, 3)) {
			pInstance->drawRect(*pRect, lua_tonumber(L, 3));
		}
		else {
			pInstance->drawRect(*pRect);
		}
		return 0;
	}

	LUCE_METHOD(drawRoundedRectangle) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Graphics);
		auto& pRect = LUCE_CHECK_USERDATA(L, 2, RectangleFloat);
		if (lua_isnumber(L, 4)) {
			pInstance->drawRoundedRectangle(*pRect, lua_tonumber(L, 3), lua_tonumber(L, 4));
		}
		else {
			pInstance->drawRoundedRectangle(*pRect, lua_tonumber(L, 3), 1.0f);
		}
		return 0;
	}

	LUCE_METHOD_LIST(Graphics,
		setColour,
		fillRect,
		fillAll,
		fillRoundedRectangle,
		drawRect,
		drawRoundedRectangle
	);
	LUCE_STATIC_METHOD_LIST(Graphics);

	LUCE_NEW(Graphics) {
		//LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Graphics, pInstance);				/**< Graphics() */
		//return 1;
		return 0;
	}
}