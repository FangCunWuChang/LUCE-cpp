#include "../Defs.h"
#include "utils/Component.h"

namespace luce {
	using utils::Component;

	LUCE_METHOD(setVisible) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		pInstance->setVisible(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD(repaint) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		pInstance->repaint();
		return 0;
	}

	LUCE_METHOD(setSize) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		pInstance->setSize(
			luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
		return 0;
	}

	LUCE_METHOD(addChildComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		auto& pChild = LUCE_CHECK_USERDATA(L, 2, Component);
		if (lua_isinteger(L, 3)) {
			pInstance->addChildComponent(pChild, luaL_checkinteger(L, 3));
		}
		pInstance->addChildComponent(pChild);
		return 0;
	}
	LUCE_METHOD(addAndMakeVisible) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		auto& pChild = LUCE_CHECK_USERDATA(L, 2, Component);
		if (lua_isinteger(L, 3)) {
			pInstance->addAndMakeVisible(pChild, luaL_checkinteger(L, 3));
		}
		pInstance->addAndMakeVisible(pChild);
		return 0;
	}

	LUCE_METHOD(setBounds) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		pInstance->setBounds(
			luaL_checkinteger(L, 2), luaL_checkinteger(L, 3),
			luaL_checkinteger(L, 4), luaL_checkinteger(L, 5));
		return 0;
	}

	LUCE_METHOD(getWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		lua_pushinteger(L, pInstance->getWidth());
		return 1;
	}

	LUCE_METHOD(getHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, Component);
		lua_pushinteger(L, pInstance->getHeight());
		return 1;
	}

	LUCE_METHOD_LIST(Component,
		setVisible,
		repaint,
		setSize,
		addChildComponent,
		addAndMakeVisible,
		setBounds,
		getWidth,
		getHeight
	);
	LUCE_STATIC_METHOD_LIST(Component);

	LUCE_NEW(Component) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Component, pInstance,
			juce::String(luaL_checkstring(L, 1)));

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}
