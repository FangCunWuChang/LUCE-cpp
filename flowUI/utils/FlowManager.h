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

			void openComponent(FlowComponent* comp, bool vertical = true);
			void closeComponent(FlowComponent* comp);

			FlowContainer* findComponent(FlowComponent* comp) const;

		private:
			friend class FlowContainer;

			void moveProgressing(
				const juce::Point<int> currentPoint,
				const juce::Point<int> topLeftDistance,
				FlowContainer* container);
			void moveEnd(
				const juce::Point<int> endPoint,
				const juce::Point<int> topLeftDistance);

			void paintOverChildren(juce::Graphics& g) override;

			void resized() override;

		private:
			FlowWindow* const window = nullptr;
			std::unique_ptr<FlowGrid> grid = nullptr;
			juce::OwnedArray<FlowContainer> freeContainers;

			FlowContainer* movingContainer = nullptr;
			juce::Point<int> currentPoint;
			juce::Rectangle<int> baseRect;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowManager)
		};
	}
}
