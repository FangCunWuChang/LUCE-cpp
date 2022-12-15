#include "DocumentWindow.h"

namespace luce {
	LUCE_MAKE_ADAPTER_FUNCTION_LIST(DocumentWindow, setVisible);

	LUCE_ADAPTER_NEW_WITH_STANDARD_INSTANCES(DocumentWindow) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, DocumentWindow, pInstance,
			luaL_checkstring(L, 1), reinterpret_cast<luce::Colour*>(luaL_checkudata(L, 2, "Colour")),
			luaL_checkinteger(L, 3), lua_toboolean(L, 4));
		return 1;
	}

	DocumentWindow::DocumentWindow(
		const juce::String& name, luce::Colour* backgroundColour,
		int requiredButtons, bool addToDesktop) 
		: LUCE_Adapter() {
		this->__object = std::make_unique<utils::DocumentWindow>(
			this->__lState, this->__objRef,
			name, *(backgroundColour->__getObject()),
			requiredButtons, addToDesktop);
	}

	LUCE_ADAPTER_METHOD_INTERFACE(DocumentWindow, setVisible) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, DocumentWindow);
		pInstance->setVisible(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_ADAPTER_METHOD(DocumentWindow, setVisible, void, bool visible) {
		this->__object->setVisible(visible);
	}
}
