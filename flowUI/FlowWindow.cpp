#include "../Defs.h"
#include "utils/FlowWindow.h"
#include "utils/FlowComponent.h"
#include "utils/FlowWindowHub.h"

namespace luce {
	using utils::FlowWindow;
	using utils::FlowComponent;
	using utils::FlowWindowHub;
	using RectangleInt = juce::Rectangle<int>;

	LUCE_METHOD(openComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowWindow);
		auto& pComp = LUCE_CHECK_USERDATA(L, 2, FlowComponent);
		if (lua_isboolean(L, 3)) {
			pInstance->openComponent(pComp, lua_toboolean(L, 3));
			return 0;
		}
		pInstance->openComponent(pComp);
		return 0;
	}

	LUCE_METHOD(closeComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowWindow);
		auto& pComp = LUCE_CHECK_USERDATA(L, 2, FlowComponent);
		pInstance->closeComponent(pComp);
		return 0;
	}

	LUCE_METHOD(hasComponent) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowWindow);
		auto& pComp = LUCE_CHECK_USERDATA(L, 2, FlowComponent);
		lua_pushboolean(L, pInstance->hasComponent(pComp));
		return 1;
	}

	LUCE_METHOD(setFullScreen) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowWindow);
		pInstance->setFullScreen(lua_toboolean(L, 2));
		return 0;
	}

	LUCE_METHOD(getScreenSize) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, FlowWindow);
		auto screenSize = pInstance->getScreenSize();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, RectangleInt, pRect, screenSize);
		return 1;
	}

	LUCE_METHOD_LIST(FlowWindow,
		openComponent,
		closeComponent,
		hasComponent,
		setFullScreen,
		getScreenSize
	);

	LUCE_METHOD(shutdown) {
		FlowWindowHub::shutdown();
		return 0;
	}

	LUCE_METHOD(getWindowNum) {
		lua_pushinteger(L, FlowWindowHub::getSize());
		return 1;
	}

	LUCE_METHOD(getWindow) {
		auto window = FlowWindowHub::getWindow(luaL_checkinteger(L, 1));
		if (window) {
			LUCE_PUSH_USERDATA(L, FlowWindow, pInstance, *window);
		}
		else {
			lua_pushnil(L);
		}
		return 1;
	}

	LUCE_METHOD(setIcon) {
		FlowWindowHub::setIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(autoLayout) {
		auto path = luaL_checkstring(L, 1);

		juce::Array<FlowComponent*> list;
		lua_pushvalue(L, 2);

		lua_pushnil(L);
		while (lua_next(L, -2)) {
			auto& pComp = LUCE_CHECK_USERDATA(L, -1, FlowComponent);
			list.add(pComp);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		FlowWindowHub::autoLayout(path, list);

		return 0;
	}

	LUCE_STATIC_METHOD_LIST(FlowWindow,
		shutdown,
		getWindowNum,
		getWindow,
		setIcon,
		autoLayout
	);

	LUCE_NEW(FlowWindow) {
		LUCE_PUSH_USERDATA(L, FlowWindow, pInstance, *new FlowWindow);
		return 1;
	}
}
