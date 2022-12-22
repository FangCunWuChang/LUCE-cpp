#include "../Defs.h"

namespace luce {
	using juce::Label;

	LUCE_METHOD(setJustificationType) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Label);
		pInstance->setJustificationType(luaL_checkinteger(L, 2));
		return 0;
	}

	LUCE_METHOD_LIST(Label,
		setJustificationType
	);
	LUCE_STATIC_METHOD_LIST(Label);

	LUCE_NEW(Label) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Label, pInstance,
			juce::String(luaL_checkstring(L, 1)), juce::String(luaL_checkstring(L, 2)));

		return 1;
	}
}
