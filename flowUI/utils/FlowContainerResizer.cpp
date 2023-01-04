#include "FlowContainerResizer.h"
#include "FlowWindow.h"
#include "FlowContainer.h"

namespace luce {
	namespace utils {
		FlowContainerResizer::FlowContainerResizer(
			ResizerPlace place,
			FlowWindow* window,
			FlowContainer* container)
			: place(place), window(window), container(container) {
			switch (place) {
			case ResizerPlace::Left:
				this->setMouseCursor(juce::MouseCursor::LeftEdgeResizeCursor);
				break;
			case ResizerPlace::Right:
				this->setMouseCursor(juce::MouseCursor::RightEdgeResizeCursor);
				break;
			case ResizerPlace::Top:
				this->setMouseCursor(juce::MouseCursor::TopEdgeResizeCursor);
				break;
			case ResizerPlace::Bottom:
				this->setMouseCursor(juce::MouseCursor::BottomEdgeResizeCursor);
				break;
			case ResizerPlace::TopLeft:
				this->setMouseCursor(juce::MouseCursor::TopLeftCornerResizeCursor);
				break;
			case ResizerPlace::TopRight:
				this->setMouseCursor(juce::MouseCursor::TopRightCornerResizeCursor);
				break;
			case ResizerPlace::BottomLeft:
				this->setMouseCursor(juce::MouseCursor::BottomLeftCornerResizeCursor);
				break;
			case ResizerPlace::BottomRight:
				this->setMouseCursor(juce::MouseCursor::BottomRightCornerResizeCursor);
				break;
			}
		}

		void FlowContainerResizer::setWindow(FlowWindow* window) {
			this->window = window;
		}

		void FlowContainerResizer::mouseDrag(const juce::MouseEvent& event) {
			if (event.mods.isLeftButtonDown()) {
				if (event.mouseWasDraggedSinceMouseDown()) {
					auto manager = this->window->getManager();
					if (dynamic_cast<FlowManager*>(container->getParentComponent()) == manager) {
						/** Limit Point Place */
						auto point = event.getEventRelativeTo(manager).getPosition();
						auto managerBounds = manager->getLocalBounds();

						if (point.getX() < 0) { point.setX(0); }
						if (point.getX() > managerBounds.getWidth()) { point.setX(managerBounds.getWidth()); }
						if (point.getY() < 0) { point.setY(0); }
						if (point.getY() > managerBounds.getHeight()) { point.setY(managerBounds.getHeight()); }

						/** Container Size */
						auto containerMinSize = this->container->getMinSize();
						auto containerBounds = this->container->getBounds();
						if (((int)this->place & (int)ResizerPlace::Left) != 0) {
							if (containerBounds.getWidth() + (containerBounds.getX() - point.getX()) < containerMinSize.getX()) {
								point.setX(containerBounds.getX() + (containerBounds.getWidth() - containerMinSize.getX()));
							}
							containerBounds.setLeft(point.getX());
						}
						if (((int)this->place & (int)ResizerPlace::Right) != 0) {
							if (point.getX() - containerBounds.getX() < containerMinSize.getX()) {
								point.setX(containerBounds.getX()+ containerMinSize.getX());
							}
							containerBounds.setRight(point.getX());
						}
						if (((int)this->place & (int)ResizerPlace::Top) != 0) {
							if (containerBounds.getHeight() + (containerBounds.getY() - point.getY()) < containerMinSize.getY()) {
								point.setY(containerBounds.getY() + (containerBounds.getHeight() - containerMinSize.getY()));
							}
							containerBounds.setTop(point.getY());
						}
						if (((int)this->place & (int)ResizerPlace::Bottom) != 0) {
							if (point.getY() - containerBounds.getY() < containerMinSize.getY()) {
								point.setY(containerBounds.getY() + containerMinSize.getY());
							}
							containerBounds.setBottom(point.getY());
						}

						/** Set Bounds */
						auto messageManager = juce::MessageManager::getInstance();
						if (messageManager) {
							messageManager->callAsync(
								[containerBounds, container = this->container] {
									container->setBounds(containerBounds);
									container->toFront(true);
								}
							);
						}
					}
				}
			}
		}
	}
}
