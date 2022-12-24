#include "../Defs.h"
#include "utils/QuickComponent.h"
#include "../adapters/gui/utils/Component.h"

namespace luce {
	using utils::QuickComponent;
	using utils::Component;
	using RectangleInt = juce::Rectangle<int>;

	LUCE_METHOD(repaint) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		pInstance->repaint();
		return 0;
	}

	LUCE_METHOD(setVisible) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		pInstance->setVisible(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD(setSize) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		pInstance->setSize(
			luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
		return 0;
	}

	LUCE_METHOD(getWidth) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		lua_pushinteger(L, pInstance->getWidth());
		return 1;
	}

	LUCE_METHOD(getHeight) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		lua_pushinteger(L, pInstance->getHeight());
		return 1;
	}

	LUCE_METHOD(addChildComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		auto& pChild = LUCE_CHECK_USERDATA(L, 2, Component);
		if (lua_isinteger(L, 3)) {
			pInstance->addChildComponent(pChild, luaL_checkinteger(L, 3));
		}
		pInstance->addChildComponent(pChild);
		return 0;
	}

	LUCE_METHOD(removeChildComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		auto& pChild = LUCE_CHECK_USERDATA(L, 2, Component);
		pInstance->removeChildComponent(pChild);
		return 0;
	}

	LUCE_METHOD(removeAllChildren) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		pInstance->removeAllChildren();
		return 0;
	}

	LUCE_METHOD(setBounds) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		pInstance->setBounds(
			luaL_checkinteger(L, 2), luaL_checkinteger(L, 3),
			luaL_checkinteger(L, 4), luaL_checkinteger(L, 5));
		return 0;
	}

	LUCE_METHOD(getArea) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleInt, pRect,
			0, 0, pInstance->getWidth(), pInstance->getHeight());
		return 1;
	}

	LUCE_METHOD(getScreen) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, QuickComponent);
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleInt, pRect,
			pInstance->getScreenSize());
		return 1;
	}

	LUCE_METHOD_LIST(QuickComponent,
		repaint,
		setVisible,
		setSize,
		getWidth,
		getHeight,
		addChildComponent,
		removeChildComponent,
		removeAllChildren,
		setBounds,
		getArea,
		getScreen
	);
	LUCE_STATIC_METHOD_LIST(QuickComponent);

	LUCE_NEW(QuickComponent) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, QuickComponent, pInstance,
			juce::String(luaL_checkstring(L, 1)));

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}
