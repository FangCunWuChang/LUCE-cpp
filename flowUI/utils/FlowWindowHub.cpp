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
					window->setIcon(FlowWindowHub::getInstance()->iconTemp);
					window->getPeer()->setIcon(FlowWindowHub::getInstance()->iconTemp);
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

		void FlowWindowHub::setIcon(const juce::String& iconPath) {
			juce::File iconFile = juce::File::getCurrentWorkingDirectory().getChildFile(iconPath);
			FlowWindowHub::getInstance()->iconTemp = juce::ImageFileFormat::loadFrom(iconFile);

			for (auto i : FlowWindowHub::getInstance()->windows) {
				i->setIcon(FlowWindowHub::getInstance()->iconTemp);
				i->getPeer()->setIcon(FlowWindowHub::getInstance()->iconTemp);
			}
		}

		void FlowWindowHub::autoLayout(const juce::String& layoutPath, juce::Array<FlowComponent*> list) {
			/** Close All Windows */
			FlowWindowHub::getInstance()->windows.clear();

			/** Load Layout File */
			juce::File layoutFile = juce::File::getCurrentWorkingDirectory().getChildFile(layoutPath);
			auto layoutData = juce::JSON::parse(layoutFile);

			/** Error */
			if (!layoutData.isObject()) { return; }

			/** Windows List */
			auto window = layoutData.getProperty("window", juce::var());
			if (!window.isArray()) { return; }

			auto windowArray = window.getArray();
			for (auto& i : *windowArray) {
				auto grid = i.getProperty("grid", juce::var());
				if (!grid.isObject()) { return; }

				/** Window */
				auto ptrWindow = new FlowWindow();
				ptrWindow->autoLayout(grid, list);
			}
		}

		FlowWindowHub* FlowWindowHub::getInstance() {
			return FlowWindowHub::instance;
		}

		FlowWindowHub* FlowWindowHub::instance = new FlowWindowHub();
	}
}
