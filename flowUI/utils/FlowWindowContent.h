#pragma once

#include "FlowManager.h"

namespace luce {
	namespace utils {
		class FlowWindow;

		class FlowWindowContent final : public juce::Component {
		public:
			FlowWindowContent() = delete;
			FlowWindowContent(FlowWindow* parent);

			FlowManager* getManager() const;

		private:
			void resized() override;

		private:
			std::unique_ptr<FlowManager> manager = nullptr;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowWindowContent)
		};
	}
}
