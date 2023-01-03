#pragma once

#include "../../Defs.h"
#include "FlowComponent.h"
#include "FlowContainerResizer.h"

namespace luce {
	namespace utils {
		class FlowWindow;
		class FlowContainer;

		class FlowGridableUnit : public juce::Component {
		public:
			FlowGridableUnit() = delete;
			FlowGridableUnit(FlowWindow* window, bool isContainer = true);
			virtual ~FlowGridableUnit() = default;

			bool thisIsContainer() const;
			virtual FlowContainer* findComponent(FlowComponent* comp) const = 0;

			virtual const juce::Point<float> getMinSize() const = 0;
 
		protected:
			FlowWindow* const window = nullptr;
			const bool isContainer = true;

		private:
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowGridableUnit)
		};

		class FlowContainer : public FlowGridableUnit {
		public:
			FlowContainer() = delete;
			FlowContainer(FlowWindow* window, bool isVertical = true);

			void add(FlowComponent* comp, bool show = true);
			void remove(FlowComponent* comp);
			bool isEmpty() const;
			void setCurrent(int current);
			void moveTo(FlowContainer* container);
			FlowContainer* findComponent(FlowComponent* comp) const override;
			const juce::Point<float> getMinSize() const override;

			void setSizeTemp(const juce::Point<int> sizeTemp);
			const juce::Point<int> getSizeTemp() const;

			void setResizerShown(bool resizerShown);
			void setVertical(bool isVertical);

		private:
			void resized() override;
			void paint(juce::Graphics& g) override;
			void paintOverChildren(juce::Graphics& g) override;

			void mouseDown(const juce::MouseEvent& event) override;
			void mouseUp(const juce::MouseEvent& event) override;
			void mouseMove(const juce::MouseEvent& event) override;
			void mouseDrag(const juce::MouseEvent& event) override;
			void mouseExit(const juce::MouseEvent& event) override;

			void parentHierarchyChanged() override;

		private:
			bool isVertical = true;
			juce::Array<FlowComponent*> components;
			int current = -1;
			/** name, size, index */
			using TabSizeTempElement = std::tuple<juce::String, float, int>;
			juce::Array<TabSizeTempElement> tabSizeTemp;
			juce::Point<int> mousePosTemp;

			juce::Point<int> freeSizeTemp;

			std::unique_ptr<FlowContainerResizer> leftResizer, rightResizer, topResizer, bottomResizer,
				topLeftResizer, topRightResizer, bottomLeftResizer, bottomRightResizer;

			void updateComponents(bool repaint = true);
			void showMenu(int tabIndex);

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowContainer)
		};
	}
}
