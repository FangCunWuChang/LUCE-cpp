#include "FlowMenu.h"
#include "FlowWindowHub.h"
#include "FlowWindow.h"

namespace luce {
	namespace utils {
		juce::PopupMenu FlowMenu::createContainerMenu(FlowWindow* currentWindow, std::function<void(int)> windowCallback, bool isTab, bool isFree, bool isMulti, bool isVertical) {
			juce::PopupMenu menu;

			menu.addItem(1, juce::translate("Release"), isTab && isMulti);
			menu.addItem(2, juce::translate("Release Container"), !isFree);
			menu.addSeparator();
			menu.addItem(3, juce::translate("Vertical"), true, isVertical);
			menu.addSeparator();
			menu.addSubMenu(juce::translate("Windows"), FlowMenu::createWindowMenu(currentWindow, windowCallback));

			return menu;
		}

		juce::PopupMenu FlowMenu::createWindowMenu(FlowWindow* currentWindow, std::function<void(int)> windowCallback) {
			juce::PopupMenu menu;

			int windowSize = FlowWindowHub::getSize();
			int currentIndex = FlowWindowHub::findWindow(currentWindow);
			for (int i = 0; i < windowSize; i++) {
				auto window = FlowWindowHub::getWindow(i);
				menu.addItem(window->getName(), true, i == currentIndex, std::bind(windowCallback, i));
			}
			menu.addSeparator();
			menu.addItem(juce::translate("New Window"), std::bind(windowCallback, windowSize));

			return menu;
		}
	}
}
