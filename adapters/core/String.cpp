#include "../Defs.h"

namespace luce {
	using juce::String;

	LUCE_METHOD(test) {
		auto& pInstance = LUCE_CHECK_USERDATA(L, 1, String);
		auto mes = luaL_checkstring(L, 2);

		printf("test:%s\n", mes);

		return 0;
	}

	LUCE_METHOD_LIST(String, test);
	LUCE_STATIC_METHOD_LIST(String);

	LUCE_NEW(String) {
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, String, pInstance);
		return 1;
	}
}
