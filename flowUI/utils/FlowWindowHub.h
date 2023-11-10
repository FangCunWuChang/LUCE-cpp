#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowWindow;
		class FlowComponent;

		class FlowWindowHub final : private juce::DeletedAtShutdown {
		public:
			FlowWindowHub() = default;

			static void addWindow(FlowWindow* window);
			static void closeWindow(FlowWindow* window);

			static void setToolBar(juce::Component* toolBar, double size);
			static void removeToolBar();

			static int getSize();
			static int findWindow(FlowWindow* window);
			static FlowWindow* getWindow(int index);

			static void shutdown();

			static void setIcon(const juce::String& iconPath);

			static void autoLayout(const juce::String& layoutPath, juce::Array<FlowComponent*> list);

			static void setOpenGL(bool openGLOn);

		private:
			juce::OwnedArray<FlowWindow> windows;
			juce::Component* toolBar = nullptr;
			double toolBarSize = 0;
			juce::Image iconTemp;
			bool openGLOn = false;

		private:
			static FlowWindowHub* getInstance();
			static FlowWindowHub* instance;
		};
	}
}
