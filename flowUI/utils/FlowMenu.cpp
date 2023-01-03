#include "FlowMenu.h"

namespace luce {
	namespace utils {
		juce::PopupMenu FlowMenu::createContainerMenu(bool isTab, bool isFree, bool isMulti) {
			juce::PopupMenu menu;

			menu.addItem(1, juce::translate("Release"), isTab && (isFree ? isMulti : true));
			menu.addItem(2, juce::translate("Release Container"), !isFree);

			return menu;
		}
	}
}
