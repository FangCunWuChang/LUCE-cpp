#include "flowUI.h"

namespace luce {
	using utils::FlowWindow;
	using utils::FlowComponent;

	int loadFlowUI(lua_State* L) {
		LUCE_REG(L, FlowWindow);
		LUCE_REG(L, FlowComponent);

		return 0;
	}
}
