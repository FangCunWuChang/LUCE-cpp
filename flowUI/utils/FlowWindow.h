#pragma once

#include "../../Defs.h"
#include "FlowManager.h"

namespace luce {
	namespace utils {
		class FlowWindow : public juce::DocumentWindow {
		public:
			FlowWindow();
			~FlowWindow();

			FlowManager* getManager() const;
			const juce::Rectangle<int> getScreenSize() const;

			void openComponent(FlowComponent* comp, bool vertical = true);
			void closeComponent(FlowComponent* comp);
			bool hasComponent(FlowComponent* comp) const;

		protected:
			void closeButtonPressed() override;
			void moved() override;

		private:
			mutable const juce::Displays::Display* ptrCurrentDisplay = nullptr;
			mutable juce::Rectangle<int> sizeTemp;
			mutable double currentScale = 1.;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowWindow)
		};
	}
}
