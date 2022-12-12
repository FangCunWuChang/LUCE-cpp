#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	LUCE_ADAPTER_WITH_API(String) {
	public:
		String();
		~String();

		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(test, void, const char* m);
		LUCE_ADAPTER_STANDARD_PROPERTIES
	};
}
