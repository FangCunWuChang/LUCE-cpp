#include "../Defs.h"
#include "utils/DocumentWindow.h"
#include "utils/Component.h"

namespace luce {
	using utils::DocumentWindow;
	using juce::Colour;
	using utils::Component;

	LUCE_METHOD(setVisible) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->setVisible(lua_toboolean(L, 2));
		
		return 0;
	}

	LUCE_METHOD(setContentNonOwned) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->setContentNonOwned(
			LUCE_CHECK_USERDATA(L, 2, Component), lua_toboolean(L, 3));
		return 0;
	}

	LUCE_METHOD(centreWithSize) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->centreWithSize(
			luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
		return 0;
	}

	LUCE_METHOD(setUsingNativeTitleBar) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->setUsingNativeTitleBar(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD(setResizable) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->setResizable(lua_toboolean(L, 2), lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD_LIST(DocumentWindow,
		setVisible,
		setContentNonOwned,
		centreWithSize,
		setUsingNativeTitleBar,
		setResizable
	);
	LUCE_STATIC_METHOD_LIST(DocumentWindow);

	LUCE_NEW(DocumentWindow) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, DocumentWindow, pInstance,
			juce::String::fromUTF8(luaL_checkstring(L, 1)), *LUCE_CHECK_USERDATA(L, 2, Colour),
			(int)luaL_checkinteger(L, 3), (bool)lua_toboolean(L, 4));

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}
