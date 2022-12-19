#include "../Defs.h"

namespace luce {
	using juce::String;

	LUCE_METHOD(test) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, String);
		auto mes = luaL_checkstring(L, 2);

		printf("test:%s\n", mes);

		return 0;
	}

	LUCE_FUNCTION_LIST(String, test);

	LUCE_NEW_FUNCTION(String) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, String, pInstance);
		return 1;
	}
}
