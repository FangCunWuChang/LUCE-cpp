#include "FlowContainer.h"
#include "FlowWindow.h"
#include "FlowStyle.h"

namespace luce {
	namespace utils {
		FlowContainer::FlowContainer(FlowWindow* window, bool isVertical)
			: window(window), isVertical(isVertical) {}

		void FlowContainer::add(FlowComponent* comp, bool show) {
			if (!comp) { return; }
			if (!this->components.contains(comp)) {
				this->components.add(comp);
				if (show) {
					this->current = this->components.size() - 1;
				}
			}
			this->updateComponents();
		}

		void FlowContainer::setCurrent(int current) {
			if (current >= 0 && current < this->components.size()) {
				this->current = current;
				this->updateComponents();
			}
		}

		void FlowContainer::resized() {
			this->updateComponents(false);
		}

		void FlowContainer::paint(juce::Graphics& g) {
			/** Title Bar */

		}

		void FlowContainer::updateComponents(bool repaint) {
			juce::Rectangle<int> componentBounds = this->getLocalBounds();
			if (this->isVertical) {
				int titleHeight = FlowStyle::getTitleHeight() * this->window->getScreenSize().getHeight();
				componentBounds.removeFromTop(titleHeight);
			}
			else {
				int titleWidth = FlowStyle::getTitleWidth() * this->window->getScreenSize().getWidth();
				componentBounds.removeFromLeft(titleWidth);
			}

			for (int i = 0; i < this->components.size(); i++) {
				this->components.getUnchecked(i)->setBounds(componentBounds);
				this->components.getUnchecked(i)->setVisible(i == this->current);
			}

			if (repaint) {
				this->repaint();
			}
		}
	}
}
