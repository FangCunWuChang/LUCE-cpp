#include "../Defs.h"
#include "utils/Component.h"

namespace luce {
	using utils::Component;

	LUCE_METHOD(setVisible) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		pInstance->setVisible(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD(setSize) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		pInstance->setSize(
			luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
		return 0;
	}

	LUCE_FUNCTION_LIST(Component, setVisible, setSize);

	LUCE_NEW_FUNCTION(Component) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Component, pInstance,
			juce::String(luaL_checkstring(L, 1)));

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}
