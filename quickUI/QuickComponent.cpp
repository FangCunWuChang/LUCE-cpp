#include "../Defs.h"
#include "utils/QuickComponent.h"

namespace luce {
	using utils::QuickComponent;

	LUCE_METHOD_LIST(QuickComponent);
	LUCE_STATIC_METHOD_LIST(QuickComponent);

	LUCE_NEW(QuickComponent) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, QuickComponent, pInstance,
			juce::String(luaL_checkstring(L, 1)));

		LUCE_CREATE_DATA(L, -1);

		LUCE_OBJ_STATE(pInstance) = L;
		LUCE_OBJ_REF(pInstance) = LUCE_REF(L, -1);

		return 1;
	}
}
