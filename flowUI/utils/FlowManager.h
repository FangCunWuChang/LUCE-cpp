#pragma once

#include "../../Defs.h"
#include "FlowGrid.h"

namespace luce {
	namespace utils {
		class FlowWindow;

		class FlowManager : public juce::Component {
		public:
			FlowManager() = delete;
			FlowManager(FlowWindow* window);

		private:
			FlowWindow* window = nullptr;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowManager)
		};
	}
}
