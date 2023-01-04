#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowWindow;

		class FlowWindowHub final : public juce::DeletedAtShutdown {
		public:
			FlowWindowHub() = default;

			static void addWindow(FlowWindow* window);
			static void closeWindow(FlowWindow* window);

			static int getSize();
			static int findWindow(FlowWindow* window);
			static FlowWindow* getWindow(int index);

			static void shutdown();

		private:
			juce::OwnedArray<FlowWindow> windows;

		private:
			static FlowWindowHub* getInstance();
			static FlowWindowHub* instance;
		};
	}
}
