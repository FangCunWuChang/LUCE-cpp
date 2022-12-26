#pragma once

#include "../../Defs.h"
#include "FlowManager.h"

namespace luce {
	namespace utils {
		class FlowWindow : public juce::DocumentWindow {
		public:
			FlowWindow();

			FlowManager* getManager() const;
			const juce::Rectangle<int> getScreenSize() const;

		private:
			mutable const juce::Displays::Display* ptrCurrentDisplay = nullptr;
			mutable juce::Rectangle<int> sizeTemp;
			mutable double currentScale = 1.;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowWindow)
		};
	}
}
