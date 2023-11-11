#pragma once

#include "../../Defs.h"
#include "FlowWindowContent.h"

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

			void autoLayout(const juce::var& grid, const juce::Array<FlowComponent*>& list);
			const juce::var getLayout(const juce::Array<FlowComponent*>& list) const;

			void setOpenGL(bool openGLOn);

		protected:
			void closeButtonPressed() override;
			void moved() override;

		private:
			friend class FlowWindowHub;
			void setToolBar(FlowComponent* toolBar, double size);
			void removeToolBar();

		private:
			mutable const juce::Displays::Display* ptrCurrentDisplay = nullptr;
			mutable juce::Rectangle<int> sizeTemp;
			mutable double currentScale = 1.;

		private:
			std::unique_ptr<juce::OpenGLContext> openGLContext = nullptr;

			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowWindow)
		};
	}
}
