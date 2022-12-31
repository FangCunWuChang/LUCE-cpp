#pragma once

#include "../../Defs.h"
#include "FlowComponent.h"

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

		protected:
			FlowWindow* window = nullptr;
			bool isContainer = true;

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

			void setSizeTemp(const juce::Point<int> sizeTemp);
			const juce::Point<int> getSizeTemp() const;

		private:
			void resized() override;
			void paint(juce::Graphics& g) override;

			void mouseDown(const juce::MouseEvent& event) override;
			void mouseUp(const juce::MouseEvent& event) override;
			void mouseMove(const juce::MouseEvent& event) override;
			void mouseDrag(const juce::MouseEvent& event) override;
			void mouseExit(const juce::MouseEvent& event) override;

		private:
			bool isVertical = true;
			juce::Array<FlowComponent*> components;
			int current = -1;
			/** name, size, index */
			using TabSizeTempElement = std::tuple<juce::String, float, int>;
			juce::Array<TabSizeTempElement> tabSizeTemp;
			juce::Point<int> mousePosTemp;

			juce::Point<int> freeSizeTemp;

			void updateComponents(bool repaint = true);

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowContainer)
		};
	}
}
