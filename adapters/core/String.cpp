#include "String.h"

namespace luce {
	LUCE_MAKE_ADAPTER_FUNCTION_LIST(String, test);

	LUCE_ADAPTER_NEW_WITH_STANDARD_INSTANCES(String) {
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

	LUCE_ADAPTER_METHOD_INTERFACE(String, test) {
		auto pInstance = LUCE_CHECK_USERDATA(L, 1, String);
		auto mes = luaL_checkstring(L, 2);
		pInstance->test(mes);
		return 0;
	}

	LUCE_ADAPTER_METHOD(String, test, void, const char* m) {
		printf("test:%s\n", m);
	}
}
