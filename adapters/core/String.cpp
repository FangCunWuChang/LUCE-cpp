#include "String.h"

namespace luce {
	LUCE_MAKE_ADAPTER_FUNCTION_LIST(String, test);

	LUCE_ADAPTER_NEW(String) {
		auto pInstance = LUCE_CREATE_USERDATA_WITH_METATABLE(L, String);
		LUCE_ADAPTER_INIT(pInstance);

		return 1;
	}

	String::String() {
		printf("constructor\n");
	}

	String::~String() {
		printf("destructor\n");
	}

	int String::test(lua_State* L) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, String);
		auto mes = luaL_checkstring(L, 2);
		pInstance->test(mes);
		return 0;
	}

	void String::test(const char* m) {
		printf("test:%s\n", m);
	}
}
