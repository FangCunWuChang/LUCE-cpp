#include "flowUI.h"

namespace luce {
	using utils::FlowWindow;
	using utils::FlowComponent;
	using utils::FlowStyle;

	int loadFlowUI(lua_State* L) {
		LUCE_REG(L, FlowWindow);
		LUCE_REG(L, FlowComponent);
		LUCE_REG(L, FlowStyle);

		return 0;
	}
}
