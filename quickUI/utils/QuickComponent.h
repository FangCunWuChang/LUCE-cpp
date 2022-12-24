#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class QuickComponent : public juce::Component {
		public:
			QuickComponent(const juce::String& name);

			void paint(juce::Graphics& g) override;
			void paintOverChildren(juce::Graphics& g) override;
			void mouseMove(const juce::MouseEvent& event) override;
			void mouseEnter(const juce::MouseEvent& event) override;
			void mouseExit(const juce::MouseEvent& event) override;
			void mouseDown(const juce::MouseEvent& event) override;
			void mouseDrag(const juce::MouseEvent& event) override;
			void mouseUp(const juce::MouseEvent& event) override;
			void mouseDoubleClick(const juce::MouseEvent& event) override;
			void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;
			void resized() override;
			void moved() override;

			const juce::Rectangle<int> getScreenSize() const;

			LUCE_REF_DATA;
		};
	}
}