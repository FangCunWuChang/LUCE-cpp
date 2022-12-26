#pragma once

#include "../../Defs.h"
#include "FlowComponent.h"

namespace luce {
	namespace utils {
		class FlowWindow;

		class FlowContainer : public juce::Component {
			FlowContainer() = delete;
			FlowContainer(FlowWindow* window, bool isVertical = true);

			void add(FlowComponent* comp, bool show = true);
			void setCurrent(int current);

		private:
			void resized() override;
			void paint(juce::Graphics& g) override;

		private:
			FlowWindow* window = nullptr;
			bool isVertical = true;
			juce::Array<FlowComponent*> components;
			int current = -1;

			void updateComponents(bool repaint = true);

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowContainer)
		};
	}
}
