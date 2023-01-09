#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowWindow;
		class FlowComponent;

		class FlowWindowHub final : public juce::DeletedAtShutdown {
		public:
			FlowWindowHub() = default;

			static void addWindow(FlowWindow* window);
			static void closeWindow(FlowWindow* window);

			static int getSize();
			static int findWindow(FlowWindow* window);
			static FlowWindow* getWindow(int index);

			static void shutdown();

			static void setIcon(const juce::String& iconPath);

			static void autoLayout(const juce::String& layoutPath, juce::Array<FlowComponent*> list);

		private:
			juce::OwnedArray<FlowWindow> windows;
			juce::Image iconTemp;

		private:
			static FlowWindowHub* getInstance();
			static FlowWindowHub* instance;
		};
	}
}
