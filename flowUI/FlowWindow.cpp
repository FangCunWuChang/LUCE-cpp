#include "../Defs.h"
#include "utils/FlowWindow.h"
#include "utils/FlowComponent.h"

namespace luce {
	using utils::FlowWindow;
	using utils::FlowComponent;

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

	LUCE_METHOD_LIST(FlowWindow,
		openComponent,
		closeComponent,
		hasComponent
	);
	LUCE_STATIC_METHOD_LIST(FlowWindow);

	LUCE_NEW(FlowWindow) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, FlowWindow, pInstance);
		return 1;
	}
}
