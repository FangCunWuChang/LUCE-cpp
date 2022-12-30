#include "../Defs.h"
#include "utils/FlowComponent.h"
#include "../adapters/gui/utils/Component.h"

namespace luce {
	using utils::FlowComponent;
	using utils::Component;

	LUCE_METHOD(setVisible) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowComponent);
		pInstance->setVisible(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD(repaint) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowComponent);
		pInstance->repaint();
		return 0;
	}

	LUCE_METHOD(addChildComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowComponent);
		auto& pChild = LUCE_CHECK_USERDATA(L, 2, Component);
		if (lua_isinteger(L, 3)) {
			pInstance->addChildComponent(pChild, luaL_checkinteger(L, 3));
		}
		pInstance->addChildComponent(pChild);
		return 0;
	}

	LUCE_METHOD(getWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowComponent);
		lua_pushinteger(L, pInstance->getWidth());
		return 1;
	}

	LUCE_METHOD(getHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowComponent);
		lua_pushinteger(L, pInstance->getHeight());
		return 1;
	}

	LUCE_METHOD_LIST(FlowComponent,
		setVisible,
		repaint,
		addChildComponent,
		getWidth,
		getHeight
	);
	LUCE_STATIC_METHOD_LIST(FlowComponent);

	LUCE_NEW(FlowComponent) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, FlowComponent, pInstance,
			juce::String(luaL_checkstring(L, 1)));

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}