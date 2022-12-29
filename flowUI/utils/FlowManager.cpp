#include "FlowManager.h"
#include "FlowWindow.h"
#include "FlowStyle.h"
#include "../../adapters/gui/utils/IconManager.h"

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

				/** Paint Adsorb */
				g.setColour(FlowStyle::getButtonIconBackgroundColor());
				g.fillRoundedRectangle(rectLeft, buttonCornerSize);
				g.fillRoundedRectangle(rectRight, buttonCornerSize);
				g.fillRoundedRectangle(rectTop, buttonCornerSize);
				g.fillRoundedRectangle(rectBottom, buttonCornerSize);
				g.fillRoundedRectangle(rectAdsorbCenter, buttonCornerSize);
				g.fillRoundedRectangle(rectAdsorbLeft, buttonCornerSize);
				g.fillRoundedRectangle(rectAdsorbRight, buttonCornerSize);
				g.fillRoundedRectangle(rectAdsorbTop, buttonCornerSize);
				g.fillRoundedRectangle(rectAdsorbBottom, buttonCornerSize);

				g.setColour(FlowStyle::getButtonIconColor());
				g.drawRoundedRectangle(rectLeft, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectRight, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectTop, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectBottom, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectAdsorbCenter, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectAdsorbLeft, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectAdsorbRight, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectAdsorbTop, buttonCornerSize, buttonBorderSize);
				g.drawRoundedRectangle(rectAdsorbBottom, buttonCornerSize, buttonBorderSize);

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

				iconLeft->drawWithin(g, rectIconLeft, juce::RectanglePlacement::centred, 1.0);
				iconRight->drawWithin(g, rectIconRight, juce::RectanglePlacement::centred, 1.0);
				iconTop->drawWithin(g, rectIconTop, juce::RectanglePlacement::centred, 1.0);
				iconBottom->drawWithin(g, rectIconBottom, juce::RectanglePlacement::centred, 1.0);
				iconAdsorbCenter->drawWithin(g, rectIconAdsorbCenter, juce::RectanglePlacement::centred, 1.0);
				iconAdsorbLeft->drawWithin(g, rectIconAdsorbLeft, juce::RectanglePlacement::centred, 1.0);
				iconAdsorbRight->drawWithin(g, rectIconAdsorbRight, juce::RectanglePlacement::centred, 1.0);
				iconAdsorbTop->drawWithin(g, rectIconAdsorbTop, juce::RectanglePlacement::centred, 1.0);
				iconAdsorbBottom->drawWithin(g, rectIconAdsorbBottom, juce::RectanglePlacement::centred, 1.0);

				/** Adsorb Area */
				juce::Rectangle<float> adsorbRect;
				auto compBounds = this->getBounds().toFloat(), baseBounds = this->baseRect.toFloat();
				if (rectLeft.contains(this->currentPoint.toFloat())) {
					adsorbRect = compBounds.withTrimmedRight(compBounds.getWidth() / 2);
				}
				else if (rectRight.contains(this->currentPoint.toFloat())) {
					adsorbRect = compBounds.withTrimmedLeft(compBounds.getWidth() / 2);
				}
				else if (rectTop.contains(this->currentPoint.toFloat())) {
					adsorbRect = compBounds.withTrimmedBottom(compBounds.getHeight() / 2);
				}
				else if (rectBottom.contains(this->currentPoint.toFloat())) {
					adsorbRect = compBounds.withTrimmedTop(compBounds.getHeight() / 2);
				}
				else if (rectAdsorbCenter.contains(this->currentPoint.toFloat())) {
					adsorbRect = baseBounds;
				}
				else if (rectAdsorbLeft.contains(this->currentPoint.toFloat())) {
					adsorbRect = baseBounds.withTrimmedRight(baseBounds.getWidth() / 2);
				}
				else if (rectAdsorbRight.contains(this->currentPoint.toFloat())) {
					adsorbRect = baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2);
				}
				else if (rectAdsorbTop.contains(this->currentPoint.toFloat())) {
					adsorbRect = baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2);
				}
				else if (rectAdsorbBottom.contains(this->currentPoint.toFloat())) {
					adsorbRect = baseBounds.withTrimmedTop(baseBounds.getHeight() / 2);
				}

				g.setColour(FlowStyle::getAdsorbColor());
				g.fillRect(adsorbRect);
			}
		}
	}
}
