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

	LUCE_METHOD(setColour) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, LookAndFeel);
		auto& pColor = LUCE_CHECK_USERDATA(L, 3, Colour);
		pInstance->setColour(luaL_checkinteger(L, 2), *pColor);
		return 0;
	}

	LUCE_METHOD(setDefaultSansSerifTypeface) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, LookAndFeel);
		juce::String path = juce::String::fromUTF8(luaL_checkstring(L, 2));

		juce::File file = juce::File::getCurrentWorkingDirectory().getChildFile(path);
		
		auto size = file.getSize();
		auto ptrData = std::unique_ptr<char[]>(new char[size]);

		auto stream = file.createInputStream();
		stream->read(ptrData.get(), size);

		auto ptrTypeface = juce::Typeface::createSystemTypefaceFor(ptrData.get(), size);
		pInstance->setDefaultSansSerifTypeface(ptrTypeface);

		return 0;
	}

	LUCE_METHOD_LIST(LookAndFeel,
		findColour,
		setColour,
		setDefaultSansSerifTypeface
	);
	LUCE_STATIC_METHOD_LIST(LookAndFeel);

	LUCE_NEW(LookAndFeel) {
		return 0;
	}
}