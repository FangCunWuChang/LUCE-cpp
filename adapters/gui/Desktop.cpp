#include "../Defs.h"

namespace luce {
	using juce::Desktop;
	using juce::LookAndFeel;

	LUCE_METHOD(getDefaultLookAndFeel) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Desktop);
		auto& laf = pInstance->getDefaultLookAndFeel();
		LUCE_PUSH_USERDATA(L, LookAndFeel, pLAF, laf);
		return 1;
	}

	LUCE_METHOD_LIST(Desktop,
		getDefaultLookAndFeel
	);

	LUCE_METHOD(getInstance) {
		auto& instance = juce::Desktop::getInstance();
		LUCE_PUSH_USERDATA(L, Desktop, pInstance, instance);
		return 1;
	}

	LUCE_STATIC_METHOD_LIST(Desktop,
		getInstance,
	);

	LUCE_NEW(Desktop) {
		return 0;
	}
}