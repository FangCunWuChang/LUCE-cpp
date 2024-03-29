﻿#pragma once

#include "../../Defs.h"
#include "FlowContainer.h"

namespace luce {
	namespace utils {
		class FlowGrid : public FlowGridableUnit {
		public:
			FlowGrid() = delete;
			FlowGrid(FlowWindow* window);
			~FlowGrid();

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
			const juce::Point<float> getMinSize() const override;

			juce::Rectangle<int> findAdsorbRect(juce::Point<int> point) const;
			FlowContainer* findAdsorbContainer(juce::Point<int> point) const;

			const juce::Array<FlowContainer*> getAllContainers() const;

			void autoLayout(const juce::var& grid, const juce::Array<FlowComponent*>& list);
			const juce::var getLayout(const juce::Array<FlowComponent*>& list) const;

		private:
			bool addUniqueUnit(FlowContainer* container);
			bool releaseUniqueUnit(FlowContainer* container);

			void decreaseLayer();
			void gcLayer(FlowGrid* layer);

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
