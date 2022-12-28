#include "FlowManager.h"
#include "FlowWindow.h"
#include "FlowStyle.h"

namespace luce {
	namespace utils {
		FlowManager::FlowManager(FlowWindow* window)
			: window(window) {
			this->grid = std::make_unique<FlowGrid>(window);
		}

		void FlowManager::openComponent(FlowComponent* comp, bool vertical) {
			if (this->findComponent(comp)) { return; }

			auto container = new FlowContainer(this->window, vertical);
			container->add(comp);

			/** Size */
			auto screenSize = this->window->getScreenSize();
			container->centreWithSize(
				FlowStyle::getContainerDefaultWidth() * screenSize.getWidth(),
				FlowStyle::getContainerDefaultHeight() * screenSize.getHeight()
			);

			if (this->grid->isEmpty()) {
				this->grid->addContainerOutside(container, FlowGrid::ContainerAddPlace::Bottom);
			}
			else {
				this->addAndMakeVisible(container);
				this->freeContainers.add(container);
				container->toFront(true);
			}
		}

		void FlowManager::closeComponent(FlowComponent* comp) {
			auto container = this->findComponent(comp);
			if (!container) { return; }
			container->remove(comp);

			if (container->isEmpty()) {
				if (!this->grid->releaseContainer(container)) {
					this->removeChildComponent(container);
					this->freeContainers.removeObject(container, false);
				}
				delete container;
			}
		}

		FlowContainer* FlowManager::findComponent(FlowComponent* comp) const {
			if (auto ptr = this->grid->findComponent(comp)) {
				return ptr;
			}
			for (auto i : this->freeContainers) {
				if (auto ptr = i->findComponent(comp)) {
					return ptr;
				}
			}
			return nullptr;
		}

		void FlowManager::moveProgressing(
			const juce::Point<int> currentPoint,
			const juce::Point<int> topLeftDistance,
			FlowContainer* container) {
			this->movingContainer = container;
			this->currentPoint = currentPoint;

			if (this->grid->findContainer(container)) {
				this->grid->releaseContainer(container);
				this->addAndMakeVisible(container);
				this->freeContainers.add(container);
			}
			
			container->setTopLeftPosition(currentPoint + topLeftDistance);
			container->toFront(true);

			if (!this->baseRect.contains(currentPoint)) {
				this->baseRect = this->grid->findRect(currentPoint - this->grid->getPosition());
			}

			this->repaint();
		}

		void FlowManager::moveEnd(
			const juce::Point<int> endPoint,
			const juce::Point<int> topLeftDistance) {
			/** TODO Check Adsorb */
			/** TODO Reset Temp */
		}

		void FlowManager::paintOverChildren(juce::Graphics& g) {
			/** TODO Check Moving */
			/** TODO Paint Adsorb */
		}
	}
}
