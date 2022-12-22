#include "../Defs.h"

namespace luce {
	using juce::LookAndFeel;
	using juce::Colour;

	LUCE_METHOD(findColour) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, LookAndFeel);
		auto color = pInstance->findColour(luaL_checkinteger(L, 2));
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColour, color);
		return 1;
	}

	LUCE_METHOD_LIST(LookAndFeel,
		findColour
	);
	LUCE_STATIC_METHOD_LIST(LookAndFeel);

	LUCE_NEW(LookAndFeel) {
		return 0;
	}
}