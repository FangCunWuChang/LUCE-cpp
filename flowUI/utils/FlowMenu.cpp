#include "FlowMenu.h"

namespace luce {
	namespace utils {
		juce::PopupMenu FlowMenu::createContainerMenu(bool isTab, bool isFree, bool isMulti, bool isVertical) {
			juce::PopupMenu menu;

			menu.addItem(1, juce::translate("Release"), isTab && isMulti);
			menu.addItem(2, juce::translate("Release Container"), !isFree);
			menu.addSeparator();
			menu.addItem(3, juce::translate("Vertical"), true, isVertical);

			return menu;
		}
	}
}
