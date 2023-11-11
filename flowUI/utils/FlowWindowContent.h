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
			friend class FlowWindow;
			void setToolBar(FlowComponent* toolBar, double size);
			void removeToolBar();

		private:
			void resized() override;

		private:
			FlowWindow* const parent = nullptr;
			std::unique_ptr<FlowManager> manager = nullptr;
			FlowComponent* toolBar = nullptr;
			double toolBarSize = 0;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowWindowContent)
		};
	}
}
