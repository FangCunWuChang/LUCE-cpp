#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	LUCE_ADAPTER_WITH_API(String) {
	public:
		static int test(lua_State* L);
		void test(const char* m);

	public:
		String();
		~String();

		LUCE_ADAPTER_STANDARD_PROPERTIES
	};
}
