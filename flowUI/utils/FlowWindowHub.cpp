#include "FlowWindowHub.h"
#include "FlowWindow.h"

namespace luce {
	namespace utils {
		void FlowWindowHub::addWindow(FlowWindow* window) {
			if (!FlowWindowHub::getInstance()->windows.contains(window)) {
				int size = FlowWindowHub::getInstance()->windows.size();
				if (size < INT_MAX - 1) {
					FlowWindowHub::getInstance()->windows.add(window);
					window->setName(juce::translate("Window") + " " + juce::String(size + 1));
				}
				else {
					delete window;
				}
			}
		}

		void FlowWindowHub::closeWindow(FlowWindow* window) {
			FlowWindowHub::getInstance()->windows.removeObject(window, false);
			int size = FlowWindowHub::getInstance()->windows.size();
			for (int i = 0; i < size; i++) {
				auto window = FlowWindowHub::getInstance()->windows[i];
				if (window) {
					window->setName(juce::translate("Window") + " " + juce::String(i + 1));
				}
			}
		}

		int FlowWindowHub::getSize() {
			return FlowWindowHub::getInstance()->windows.size();
		}

		int FlowWindowHub::findWindow(FlowWindow* window) {
			return FlowWindowHub::getInstance()->windows.indexOf(window);
		}

		FlowWindow* FlowWindowHub::getWindow(int index) {
			return FlowWindowHub::getInstance()->windows[index];
		}

		void FlowWindowHub::shutdown() {
			FlowWindowHub::getInstance()->windows.clear();
		}

		FlowWindowHub* FlowWindowHub::getInstance() {
			return FlowWindowHub::instance;
		}

		FlowWindowHub* FlowWindowHub::instance = new FlowWindowHub();
	}
}
