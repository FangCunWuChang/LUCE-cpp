#include "FlowManager.h"
#include "FlowWindow.h"
#include "FlowStyle.h"
#include "FlowWindowHub.h"
#include "../../adapters/gui/utils/IconManager.h"

namespace luce {
	namespace utils {
		FlowManager::FlowManager(FlowWindow* window)
			: window(window) {
			this->grid = std::make_unique<FlowGrid>(window);
			this->addAndMakeVisible(this->grid.get());
		}

		void FlowManager::addContainer(FlowContainer* container) {
			if (!container) { return; }

			/** Size */
			auto screenSize = this->window->getScreenSize();

			this->addAndMakeVisible(container);
			this->freeContainers.add(container);
			container->centreWithSize(
				FlowStyle::getContainerDefaultWidth() * screenSize.getWidth(),
				FlowStyle::getContainerDefaultHeight() * screenSize.getHeight()
			);
			container->toFront(true);
		}

		bool FlowManager::removeContainer(FlowContainer* container) {
			if (!container) { return false; }

			auto checkCloseFunc = [this] {
				if (this->grid->isEmpty() && this->freeContainers.size() == 0 && FlowWindowHub::getSize() > 1) {
					juce::MessageManager::callAsync(
						[window = juce::Component::SafePointer(this->window)] {
							if (window) {
								delete window;
							}
						}
					);
				}
			};

			if (this->grid->releaseContainer(container)) {
				checkCloseFunc();
				return true;
			}
			else {
				if (this->freeContainers.contains(container)) {
					this->removeChildComponent(container);
					this->freeContainers.removeObject(container, false);

					checkCloseFunc();
					return true;
				}
				return false;
			}
		}

		void FlowManager::openComponent(FlowComponent* comp, bool vertical) {
			if (this->findComponent(comp)) { return; }

			auto container = new FlowContainer(this->window, vertical);
			container->add(comp);

			this->addContainer(container);
		}

		void FlowManager::closeComponent(FlowComponent* comp) {
			auto container = this->findComponent(comp);
			if (!container) { return; }
			container->remove(comp);

			if (container->isEmpty()) {
				this->removeContainer(container);
				delete container;
				container = nullptr;
			}
		}

		void FlowManager::releaseComponent(FlowComponent* comp) {
			this->closeComponent(comp);
			this->openComponent(comp);
		}

		void FlowManager::releaseContainer(FlowContainer* container) {
			if (this->removeContainer(container)) {
				this->addContainer(container);

				container->centreWithSize(container->getWidth(), container->getHeight());
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

		const juce::Array<FlowContainer*> FlowManager::getAllContainers() const {
			auto result = this->grid->getAllContainers();
			result.addArray(this->freeContainers);
			return result;
		}

		void FlowManager::autoLayout(const juce::var& grid, const juce::Array<FlowComponent*>& list) {
			this->grid->autoLayout(grid, list);
		}

		const juce::var FlowManager::getLayout(const juce::Array<FlowComponent*>& list) const {
			return this->grid->getLayout(list);
		}

		void FlowManager::moveProgressing(
			const juce::Point<int> currentPoint,
			const juce::Point<int> topLeftDistance,
			FlowContainer* container) {
			this->movingContainer = container;
			this->currentPoint = currentPoint;

			if (this->currentPoint.getX() < 0) { this->currentPoint.setX(0); }
			if (this->currentPoint.getY() < 0) { this->currentPoint.setY(0); }
			if (this->currentPoint.getX() > this->getWidth()) { this->currentPoint.setX(this->getWidth()); }
			if (this->currentPoint.getY() > this->getHeight()) { this->currentPoint.setY(this->getHeight()); }

			if (this->grid->findContainer(container)) {
				this->grid->releaseContainer(container);
				this->addAndMakeVisible(container);
				this->freeContainers.add(container);
			}
			
			container->setTopLeftPosition(this->currentPoint + topLeftDistance);
			
			container->toFront(true);

			if (!this->baseRect.contains(this->currentPoint)) {
				this->baseRect = this->grid->findAdsorbRect(this->currentPoint);
			}

			this->repaint();
		}

		void FlowManager::moveEnd(
			const juce::Point<int> endPoint,
			const juce::Point<int> topLeftDistance) {
			/** Check Adsorb */
			this->currentPoint = endPoint;

			if (this->currentPoint.getX() < 0) { this->currentPoint.setX(0); }
			if (this->currentPoint.getY() < 0) { this->currentPoint.setY(0); }
			if (this->currentPoint.getX() > this->getWidth()) { this->currentPoint.setX(this->getWidth()); }
			if (this->currentPoint.getY() > this->getHeight()) { this->currentPoint.setY(this->getHeight()); }

			if (!this->baseRect.contains(this->currentPoint)) {
				this->baseRect = this->grid->findAdsorbRect(this->currentPoint);
			}

			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Sizes */
			float buttonWidth = FlowStyle::getButtonWidth() * screenSize.getWidth();
			float buttonHeight = FlowStyle::getButtonHeight() * screenSize.getHeight();
			float buttonIconWidth = FlowStyle::getButtonIconWidth() * screenSize.getWidth();
			float buttonIconHeight = FlowStyle::getButtonIconHeight() * screenSize.getHeight();
			float buttonSplitWidth = FlowStyle::getButtonSplitWidth() * screenSize.getWidth();
			float buttonSplitHeight = FlowStyle::getButtonSplitHeight() * screenSize.getHeight();
			float buttonPaddingWidth = FlowStyle::getButtonPaddingWidth() * screenSize.getWidth();
			float buttonPaddingHeight = FlowStyle::getButtonPaddingHeight() * screenSize.getHeight();
			float buttonCornerSize = FlowStyle::getButtonCornerSize() * screenSize.getWidth();
			float buttonBorderSize = FlowStyle::getButtonBorderSize() * screenSize.getWidth();

			/** Button Rects */
			juce::Rectangle<float> rectLeft(
				buttonPaddingWidth, this->getHeight() / 2 - buttonWidth / 2,
				buttonHeight, buttonWidth
			);
			juce::Rectangle<float> rectRight(
				this->getWidth() - buttonPaddingWidth - buttonHeight, this->getHeight() / 2 - buttonWidth / 2,
				buttonHeight, buttonWidth
			);
			juce::Rectangle<float> rectTop(
				this->getWidth() / 2 - buttonWidth / 2, buttonPaddingHeight,
				buttonWidth, buttonHeight
			);
			juce::Rectangle<float> rectBottom(
				this->getWidth() / 2 - buttonWidth / 2, this->getHeight() - buttonPaddingHeight - buttonHeight,
				buttonWidth, buttonHeight
			);

			juce::Point<float> baseCenter = this->baseRect.getCentre().toFloat();
			juce::Rectangle<float> rectAdsorbCenter(
				baseCenter.getX() - buttonWidth / 2, baseCenter.getY() - buttonWidth / 2,
				buttonWidth, buttonWidth
			);
			juce::Rectangle<float> rectAdsorbLeft(
				baseCenter.getX() - buttonWidth / 2 - buttonSplitWidth - buttonHeight, baseCenter.getY() - buttonWidth / 2,
				buttonHeight, buttonWidth
			);
			juce::Rectangle<float> rectAdsorbRight(
				baseCenter.getX() + buttonWidth / 2 + buttonSplitWidth, baseCenter.getY() - buttonWidth / 2,
				buttonHeight, buttonWidth
			);
			juce::Rectangle<float> rectAdsorbTop(
				baseCenter.getX() - buttonWidth / 2, baseCenter.getY() - buttonWidth / 2 - buttonSplitHeight - buttonHeight,
				buttonWidth, buttonHeight
			);
			juce::Rectangle<float> rectAdsorbBottom(
				baseCenter.getX() - buttonWidth / 2, baseCenter.getY() + buttonWidth / 2 + buttonSplitHeight,
				buttonWidth, buttonHeight
			);

			/** Adsorb */
			auto adsorbContainer = this->grid->findAdsorbContainer(this->currentPoint);
			
			if (this->movingContainer) {
				if (rectLeft.contains(this->currentPoint.toFloat())) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Left)) {
						this->freeContainers.add(this->movingContainer);
						this->addChildComponent(this->movingContainer);
					}
				}
				else if (rectRight.contains(this->currentPoint.toFloat())) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Right)) {
						this->freeContainers.add(this->movingContainer);
						this->addChildComponent(this->movingContainer);
					}
				}
				else if (rectTop.contains(this->currentPoint.toFloat())) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Top)) {
						this->freeContainers.add(this->movingContainer);
						this->addChildComponent(this->movingContainer);
					}
				}
				else if (rectBottom.contains(this->currentPoint.toFloat())) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Bottom)) {
						this->freeContainers.add(this->movingContainer);
						this->addChildComponent(this->movingContainer);
					}
				}
				else if (rectAdsorbCenter.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (adsorbContainer) {
						if (!this->grid->addContainer(this->movingContainer, adsorbContainer, FlowGrid::ContainerAddPlace::Center)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
					else {
						if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Center)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
				}
				else if (rectAdsorbLeft.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (adsorbContainer) {
						if (!this->grid->addContainer(this->movingContainer, adsorbContainer, FlowGrid::ContainerAddPlace::Left)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
					else {
						if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Left)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
				}
				else if (rectAdsorbRight.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (adsorbContainer) {
						if (!this->grid->addContainer(this->movingContainer, adsorbContainer, FlowGrid::ContainerAddPlace::Right)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
					else {
						if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Right)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
				}
				else if (rectAdsorbTop.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (adsorbContainer) {
						if (!this->grid->addContainer(this->movingContainer, adsorbContainer, FlowGrid::ContainerAddPlace::Top)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
					else {
						if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Top)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
				}
				else if (rectAdsorbBottom.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					this->freeContainers.removeObject(this->movingContainer, false);
					this->removeChildComponent(this->movingContainer);
					if (adsorbContainer) {
						if (!this->grid->addContainer(this->movingContainer, adsorbContainer, FlowGrid::ContainerAddPlace::Bottom)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
					else {
						if (!this->grid->addContainerOutside(this->movingContainer, FlowGrid::ContainerAddPlace::Bottom)) {
							this->freeContainers.add(this->movingContainer);
							this->addChildComponent(this->movingContainer);
						}
					}
				}
				else {
					/** No Adsorb */
					this->movingContainer->setTopLeftPosition(this->currentPoint + topLeftDistance);
					auto containerBounds = this->movingContainer->getBounds();
					if (containerBounds.getX() + containerBounds.getWidth() <= 0 ||
						containerBounds.getX() >= this->getWidth() ||
						containerBounds.getY() + containerBounds.getHeight() <= 0 ||
						containerBounds.getY() >= this->getHeight()) {
						this->movingContainer->centreWithSize(
							containerBounds.getWidth(), containerBounds.getHeight());
					}
					this->movingContainer->toFront(true);
				}
			}

			/** Reset Temp */
			this->movingContainer = nullptr;
			this->currentPoint = juce::Point<int>();
			this->baseRect = juce::Rectangle<int>();

			this->repaint();
		}

		void FlowManager::paintOverChildren(juce::Graphics& g) {
			/** Check Moving */
			if (this->movingContainer) {
				/** Get Screen Size */
				auto screenSize = this->window->getScreenSize();

				/** Sizes */
				float buttonWidth = FlowStyle::getButtonWidth() * screenSize.getWidth();
				float buttonHeight = FlowStyle::getButtonHeight() * screenSize.getHeight();
				float buttonIconWidth = FlowStyle::getButtonIconWidth() * screenSize.getWidth();
				float buttonIconHeight = FlowStyle::getButtonIconHeight() * screenSize.getHeight();
				float buttonSplitWidth = FlowStyle::getButtonSplitWidth() * screenSize.getWidth();
				float buttonSplitHeight = FlowStyle::getButtonSplitHeight() * screenSize.getHeight();
				float buttonPaddingWidth = FlowStyle::getButtonPaddingWidth() * screenSize.getWidth();
				float buttonPaddingHeight = FlowStyle::getButtonPaddingHeight() * screenSize.getHeight();
				float buttonCornerSize = FlowStyle::getButtonCornerSize() * screenSize.getWidth();
				float buttonBorderSize = FlowStyle::getButtonBorderSize() * screenSize.getWidth();

				/** Button Rects */
				juce::Rectangle<float> rectLeft(
					buttonPaddingWidth, this->getHeight() / 2 - buttonWidth / 2,
					buttonHeight, buttonWidth
				);
				juce::Rectangle<float> rectRight(
					this->getWidth() - buttonPaddingWidth - buttonHeight, this->getHeight() / 2 - buttonWidth / 2,
					buttonHeight, buttonWidth
				);
				juce::Rectangle<float> rectTop(
					this->getWidth() / 2 - buttonWidth / 2, buttonPaddingHeight,
					buttonWidth, buttonHeight
				);
				juce::Rectangle<float> rectBottom(
					this->getWidth() / 2 - buttonWidth / 2, this->getHeight() - buttonPaddingHeight - buttonHeight,
					buttonWidth, buttonHeight
				);

				juce::Point<float> baseCenter = this->baseRect.getCentre().toFloat();
				juce::Rectangle<float> rectAdsorbCenter(
					baseCenter.getX() - buttonWidth / 2, baseCenter.getY() - buttonWidth / 2,
					buttonWidth, buttonWidth
				);
				juce::Rectangle<float> rectAdsorbLeft(
					baseCenter.getX() - buttonWidth / 2 - buttonSplitWidth - buttonHeight, baseCenter.getY() - buttonWidth / 2,
					buttonHeight, buttonWidth
				);
				juce::Rectangle<float> rectAdsorbRight(
					baseCenter.getX() + buttonWidth / 2 + buttonSplitWidth, baseCenter.getY() - buttonWidth / 2,
					buttonHeight, buttonWidth
				);
				juce::Rectangle<float> rectAdsorbTop(
					baseCenter.getX() - buttonWidth / 2, baseCenter.getY() - buttonWidth / 2 - buttonSplitHeight - buttonHeight,
					buttonWidth, buttonHeight
				);
				juce::Rectangle<float> rectAdsorbBottom(
					baseCenter.getX() - buttonWidth / 2, baseCenter.getY() + buttonWidth / 2 + buttonSplitHeight,
					buttonWidth, buttonHeight
				);

				/** Button Icon */
				auto iconLeft = IconManager::getSVG(FlowStyle::getButtonLeftIcon());
				auto iconRight = IconManager::getSVG(FlowStyle::getButtonRightIcon());
				auto iconTop = IconManager::getSVG(FlowStyle::getButtonTopIcon());
				auto iconBottom = IconManager::getSVG(FlowStyle::getButtonBottomIcon());
				auto iconAdsorbCenter = IconManager::getSVG(FlowStyle::getButtonAdsorbCenterIcon());
				auto iconAdsorbLeft = IconManager::getSVG(FlowStyle::getButtonAdsorbLeftIcon());
				auto iconAdsorbRight = IconManager::getSVG(FlowStyle::getButtonAdsorbRightIcon());
				auto iconAdsorbTop = IconManager::getSVG(FlowStyle::getButtonAdsorbTopIcon());
				auto iconAdsorbBottom = IconManager::getSVG(FlowStyle::getButtonAdsorbBottomIcon());

				iconLeft->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconRight->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconTop->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconBottom->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconAdsorbCenter->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconAdsorbLeft->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconAdsorbRight->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconAdsorbTop->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());
				iconAdsorbBottom->replaceColour(juce::Colours::black, FlowStyle::getButtonIconColor());

				float buttonWhiteSpaceWidth = (buttonWidth - buttonIconWidth) / 2;
				float buttonWhiteSpaceHeight = (buttonHeight - buttonIconHeight) / 2;

				juce::Rectangle<float> rectIconLeft = rectLeft
					.withTrimmedLeft(buttonWhiteSpaceHeight).withTrimmedRight(buttonWhiteSpaceHeight)
					.withTrimmedTop(buttonWhiteSpaceWidth).withTrimmedBottom(buttonWhiteSpaceWidth);
				juce::Rectangle<float> rectIconRight = rectRight
					.withTrimmedLeft(buttonWhiteSpaceHeight).withTrimmedRight(buttonWhiteSpaceHeight)
					.withTrimmedTop(buttonWhiteSpaceWidth).withTrimmedBottom(buttonWhiteSpaceWidth);
				juce::Rectangle<float> rectIconTop = rectTop
					.withTrimmedLeft(buttonWhiteSpaceWidth).withTrimmedRight(buttonWhiteSpaceWidth)
					.withTrimmedTop(buttonWhiteSpaceHeight).withTrimmedBottom(buttonWhiteSpaceHeight);
				juce::Rectangle<float> rectIconBottom = rectBottom
					.withTrimmedLeft(buttonWhiteSpaceWidth).withTrimmedRight(buttonWhiteSpaceWidth)
					.withTrimmedTop(buttonWhiteSpaceHeight).withTrimmedBottom(buttonWhiteSpaceHeight);
				juce::Rectangle<float> rectIconAdsorbCenter = rectAdsorbCenter
					.withTrimmedLeft(buttonWhiteSpaceWidth).withTrimmedRight(buttonWhiteSpaceWidth)
					.withTrimmedTop(buttonWhiteSpaceWidth).withTrimmedBottom(buttonWhiteSpaceWidth);
				juce::Rectangle<float> rectIconAdsorbLeft = rectAdsorbLeft
					.withTrimmedLeft(buttonWhiteSpaceHeight).withTrimmedRight(buttonWhiteSpaceHeight)
					.withTrimmedTop(buttonWhiteSpaceWidth).withTrimmedBottom(buttonWhiteSpaceWidth);
				juce::Rectangle<float> rectIconAdsorbRight = rectAdsorbRight
					.withTrimmedLeft(buttonWhiteSpaceHeight).withTrimmedRight(buttonWhiteSpaceHeight)
					.withTrimmedTop(buttonWhiteSpaceWidth).withTrimmedBottom(buttonWhiteSpaceWidth);
				juce::Rectangle<float> rectIconAdsorbTop = rectAdsorbTop
					.withTrimmedLeft(buttonWhiteSpaceWidth).withTrimmedRight(buttonWhiteSpaceWidth)
					.withTrimmedTop(buttonWhiteSpaceHeight).withTrimmedBottom(buttonWhiteSpaceHeight);
				juce::Rectangle<float> rectIconAdsorbBottom = rectAdsorbBottom
					.withTrimmedLeft(buttonWhiteSpaceWidth).withTrimmedRight(buttonWhiteSpaceWidth)
					.withTrimmedTop(buttonWhiteSpaceHeight).withTrimmedBottom(buttonWhiteSpaceHeight);

				/** Paint Adsorb Buton */
				if (this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					g.setColour(FlowStyle::getButtonIconBackgroundColor());
					g.fillRoundedRectangle(rectAdsorbCenter, buttonCornerSize);
					g.fillRoundedRectangle(rectAdsorbLeft, buttonCornerSize);
					g.fillRoundedRectangle(rectAdsorbRight, buttonCornerSize);
					g.fillRoundedRectangle(rectAdsorbTop, buttonCornerSize);
					g.fillRoundedRectangle(rectAdsorbBottom, buttonCornerSize);
					g.setColour(FlowStyle::getButtonIconColor());
					g.drawRoundedRectangle(rectAdsorbCenter, buttonCornerSize, buttonBorderSize);
					g.drawRoundedRectangle(rectAdsorbLeft, buttonCornerSize, buttonBorderSize);
					g.drawRoundedRectangle(rectAdsorbRight, buttonCornerSize, buttonBorderSize);
					g.drawRoundedRectangle(rectAdsorbTop, buttonCornerSize, buttonBorderSize);
					g.drawRoundedRectangle(rectAdsorbBottom, buttonCornerSize, buttonBorderSize);

					iconAdsorbCenter->drawWithin(g, rectIconAdsorbCenter, juce::RectanglePlacement::centred, 1.0);
					iconAdsorbLeft->drawWithin(g, rectIconAdsorbLeft, juce::RectanglePlacement::centred, 1.0);
					iconAdsorbRight->drawWithin(g, rectIconAdsorbRight, juce::RectanglePlacement::centred, 1.0);
					iconAdsorbTop->drawWithin(g, rectIconAdsorbTop, juce::RectanglePlacement::centred, 1.0);
					iconAdsorbBottom->drawWithin(g, rectIconAdsorbBottom, juce::RectanglePlacement::centred, 1.0);
				}

				g.setColour(FlowStyle::getButtonIconBackgroundColor());
				g.fillRoundedRectangle(rectLeft, buttonCornerSize);
				g.fillRoundedRectangle(rectRight, buttonCornerSize);
				g.fillRoundedRectangle(rectTop, buttonCornerSize);
				g.fillRoundedRectangle(rectBottom, buttonCornerSize);
				g.setColour(FlowStyle::getButtonIconColor());
				g.drawRoundedRectangle(rectLeft, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectRight, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectTop, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectBottom, buttonCornerSize, buttonBorderSize);

				iconLeft->drawWithin(g, rectIconLeft, juce::RectanglePlacement::centred, 1.0);
				iconRight->drawWithin(g, rectIconRight, juce::RectanglePlacement::centred, 1.0);
				iconTop->drawWithin(g, rectIconTop, juce::RectanglePlacement::centred, 1.0);
				iconBottom->drawWithin(g, rectIconBottom, juce::RectanglePlacement::centred, 1.0);

				/** Adsorb Area */
				juce::Rectangle<float> adsorbRect;
				auto compBounds = this->getLocalBounds().toFloat(), baseBounds = this->baseRect.toFloat();
				auto movingBounds = this->movingContainer->getBounds().toFloat();
				if (rectLeft.contains(this->currentPoint.toFloat())) {
					adsorbRect = movingBounds.getWidth() <= compBounds.getWidth() / 2
						? compBounds.withTrimmedRight(compBounds.getWidth() - movingBounds.getWidth())
						: compBounds.withTrimmedRight(compBounds.getWidth() / 2);
				}
				else if (rectRight.contains(this->currentPoint.toFloat())) {
					adsorbRect = movingBounds.getWidth() <= compBounds.getWidth() / 2
						? compBounds.withTrimmedLeft(compBounds.getWidth() - movingBounds.getWidth())
						: compBounds.withTrimmedLeft(compBounds.getWidth() / 2);
				}
				else if (rectTop.contains(this->currentPoint.toFloat())) {
					adsorbRect = movingBounds.getHeight() <= compBounds.getHeight() / 2
						? compBounds.withTrimmedBottom(compBounds.getHeight() - movingBounds.getHeight())
						: compBounds.withTrimmedBottom(compBounds.getHeight() / 2);
				}
				else if (rectBottom.contains(this->currentPoint.toFloat())) {
					adsorbRect = movingBounds.getHeight() <= compBounds.getHeight() / 2
						? compBounds.withTrimmedTop(compBounds.getHeight() - movingBounds.getHeight())
						: compBounds.withTrimmedTop(compBounds.getHeight() / 2);
				}
				else if (rectAdsorbCenter.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					adsorbRect = baseBounds;
				}
				else if (rectAdsorbLeft.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					adsorbRect = movingBounds.getWidth() <= baseBounds.getWidth() / 2
						? baseBounds.withTrimmedRight(baseBounds.getWidth() - movingBounds.getWidth())
						: baseBounds.withTrimmedRight(baseBounds.getWidth() / 2);
				}
				else if (rectAdsorbRight.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					adsorbRect = movingBounds.getWidth() <= baseBounds.getWidth() / 2
						? baseBounds.withTrimmedLeft(baseBounds.getWidth() - movingBounds.getWidth())
						: baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2);
				}
				else if (rectAdsorbTop.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					adsorbRect = movingBounds.getHeight() <= baseBounds.getHeight() / 2
						? baseBounds.withTrimmedBottom(baseBounds.getHeight() - movingBounds.getHeight())
						: baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2);
				}
				else if (rectAdsorbBottom.contains(this->currentPoint.toFloat()) &&
					this->baseRect.getWidth() > 0 && this->baseRect.getHeight() > 0) {
					adsorbRect = movingBounds.getHeight() <= baseBounds.getHeight() / 2
						? baseBounds.withTrimmedTop(baseBounds.getHeight() - movingBounds.getHeight())
						: baseBounds.withTrimmedTop(baseBounds.getHeight() / 2);
				}

				g.setColour(FlowStyle::getAdsorbColor());
				g.fillRect(adsorbRect);
			}
		}

		void FlowManager::resized() {
			this->grid->setBounds(this->getLocalBounds());

			for (auto i : this->freeContainers) {
				if (!this->getLocalBounds().contains(i->getBounds())) {
					if (i->getRight() > this->getWidth()) { i->setTopLeftPosition(this->getWidth() - i->getWidth(), i->getY()); }
					if (i->getBottom() > this->getHeight()) { i->setTopLeftPosition(i->getX(), this->getHeight() - i->getHeight()); }
					if (i->getX() < 0) { i->setTopLeftPosition(0, i->getY()); }
					if (i->getY() < 0) { i->setTopLeftPosition(i->getX(), 0); }
				}
			}
		}
	}
}
