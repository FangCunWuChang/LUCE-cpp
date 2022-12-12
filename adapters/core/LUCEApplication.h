#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	LUCE_ADAPTER_WITH_API(LUCEApplication) {
	public:
		LUCEApplication();
		~LUCEApplication() override = default;

		LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(exec, int);
		LUCE_ADAPTER_STANDARD_PROPERTIES
	};
}