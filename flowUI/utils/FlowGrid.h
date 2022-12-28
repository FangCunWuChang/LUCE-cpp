#pragma once

#include "../../Defs.h"
#include "FlowContainer.h"

namespace luce {
	namespace utils {
		class FlowGrid : public FlowGridableUnit {
		public:
			FlowGrid() = delete;
			FlowGrid(FlowWindow* window);

			enum class ContainerAddPlace {
				Center,
				Left,
				Right,
				Top,
				Bottom
			};

			bool addContainer(
				FlowContainer* container,
				FlowContainer* base,
				ContainerAddPlace place);
			bool addContainerOutside(
				FlowContainer* container,
				ContainerAddPlace place);
			bool releaseContainer(FlowContainer* container);

			bool isEmpty() const;
			FlowContainer* findComponent(FlowComponent* comp) const override;
			bool findContainer(FlowContainer* container) const;

			juce::Rectangle<int> findRect(juce::Point<int> point) const;

		private:
			bool addUniqueUnit(FlowContainer* container);
			bool releaseUniqueUnit(FlowContainer* container);

			void decreaseLayer(FlowGrid* layer);

		private:
			void resized() override;

		private:
			juce::OwnedArray<FlowGridableUnit> units;
			juce::OwnedArray<juce::StretchableLayoutResizerBar> resizers;
			std::unique_ptr<juce::StretchableLayoutManager> manager = nullptr;
			std::unique_ptr<juce::LookAndFeel> resizerLookAndFeel = nullptr;
			bool isVertical = false;

			void updateComponents();

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowGrid)
		};
	}
}
