#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowMenu final {
		public:
			static juce::PopupMenu createContainerMenu(bool isTab, bool isFree, bool isMulti);
		};
	}
}
