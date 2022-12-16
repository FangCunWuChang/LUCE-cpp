#include "../Defs.h"
#include "utils/DocumentWindow.h"

namespace luce {
	using utils::DocumentWindow;
	using juce::Colour;

	LUCE_METHOD(setVisible) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->setVisible(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_FUNCTION_LIST(DocumentWindow, setVisible);

	LUCE_NEW_FUNCTION(DocumentWindow) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, DocumentWindow, pInstance,
			juce::String(luaL_checkstring(L, 1)), *LUCE_CHECK_USERDATA(L, 2, Colour),
			(int)luaL_checkinteger(L, 3), (bool)lua_toboolean(L, 4));

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}
