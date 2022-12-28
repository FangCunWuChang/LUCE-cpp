﻿#include "FlowContainer.h"
#include "FlowWindow.h"
#include "FlowStyle.h"

namespace luce {
	namespace utils {
		FlowGridableUnit::FlowGridableUnit(FlowWindow* window, bool isContainer) 
			: window(window), isContainer(isContainer) {

		}

		bool FlowGridableUnit::thisIsContainer() const {
			return this->isContainer;
		}

		FlowContainer::FlowContainer(FlowWindow* window, bool isVertical)
			: FlowGridableUnit(window, true), isVertical(isVertical) {
			this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
		}

		void FlowContainer::add(FlowComponent* comp, bool show) {
			if (!comp) { return; }
			if (!this->components.contains(comp)) {
				this->components.add(comp);
				this->addChildComponent(comp);
				if (show) {
					this->current = this->components.size() - 1;
				}
			}
			this->updateComponents();
		}

		void FlowContainer::remove(FlowComponent* comp) {
			comp->setVisible(false);
			this->components.removeAllInstancesOf(comp);
			this->removeChildComponent(comp);
			this->updateComponents();
		}

		bool FlowContainer::isEmpty() const {
			return this->components.size() == 0;
		}

		void FlowContainer::setCurrent(int current) {
			if (current >= 0 && current < this->components.size()) {
				this->current = current;
				this->updateComponents();
			}
		}

		void FlowContainer::moveTo(FlowContainer* container) {
			for (auto i : this->components) {
				this->removeChildComponent(i);
				container->addChildComponent(i);
			}
			container->current = container->components.size() + this->current;
			container->components.addArray(this->components);
			this->components.clear();
			this->current = -1;
			this->updateComponents();
			container->updateComponents();
		}

		FlowContainer* FlowContainer::findComponent(FlowComponent* comp) const {
			for (auto i : this->components) {
				if (i == comp) {
					return const_cast<FlowContainer*>(this);
				}
			}
			return nullptr;
		}

		void FlowContainer::resized() {
			this->updateComponents(false);
		}

		void FlowContainer::paint(juce::Graphics& g) {
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Title Bar */
			{
				/** Background */
				{
					juce::Rectangle<float> titleArea(
						0, 0,
						this->isVertical ? this->getWidth() : (FlowStyle::getTitleWidth() * screenSize.getWidth()),
						this->isVertical ? (FlowStyle::getTitleHeight() * screenSize.getHeight()) : this->getHeight()
					);
					g.setColour(FlowStyle::getTitleBackgroundColor());
					g.fillRect(titleArea);
				}

				/** Tab */
				{
					/** Size */
					float paddingSize =
						(this->isVertical ? FlowStyle::getTitleTextPaddingWidth() : FlowStyle::getTitleTextPaddingHeight())
						* (this->isVertical ? screenSize.getWidth() : screenSize.getHeight());
					float fontSize = (this->isVertical ? FlowStyle::getTitleTextHeight() : FlowStyle::getTitleTextWidth())
						* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());
					
					/** Font */
					juce::Font font(fontSize);
					g.setFont(font);

					float tabTotalSize = 0;
					for (int i = 0; i < this->tabSizeTemp.size(); i++) {
						/** Background */
						auto& temp = this->tabSizeTemp.getReference(i);
						juce::Rectangle<float> tabArea(
							this->isVertical ? tabTotalSize : 0,
							this->isVertical ? 0 : tabTotalSize,
							this->isVertical ? std::get<1>(temp) : (FlowStyle::getTitleWidth() * screenSize.getWidth()),
							this->isVertical ? (FlowStyle::getTitleHeight() * screenSize.getHeight()) : std::get<1>(temp)
						);
						tabTotalSize += std::get<1>(temp);

						g.setColour((i == this->current) ? FlowStyle::getTitleHighlightColor() : FlowStyle::getTitleBackgroundColor());
						g.fillRect(tabArea);

						/** Border */
						if (i == this->current) {
							juce::Rectangle<float> borderArea = (this->isVertical)
								? tabArea.withHeight(FlowStyle::getTitleBorderHeight() * screenSize.getHeight())
								: tabArea.withWidth(FlowStyle::getTitleBorderWidth() * screenSize.getWidth());
							g.setColour(FlowStyle::getTitleBorderColor());
							g.fillRect(borderArea);
						}

						/** Text */
						if (this->isVertical) {
							juce::Rectangle<float> textArea = tabArea
								.withTrimmedLeft(paddingSize).withTrimmedRight(paddingSize);
							g.setColour((i == this->current) ? FlowStyle::getTitleTextHighlightColor() : FlowStyle::getTitleTextHighlightColor());
							g.drawFittedText(std::get<0>(temp), textArea.toNearestInt(), juce::Justification::centred, 1, 1);
						}
						else {
							juce::Rectangle<float> textArea = tabArea
								.withTrimmedTop(paddingSize).withTrimmedBottom(paddingSize);
							g.setColour((i == this->current) ? FlowStyle::getTitleTextHighlightColor() : FlowStyle::getTitleTextHighlightColor());

							g.addTransform(juce::AffineTransform(
								0, 1, textArea.getX(),
								-1, 0, textArea.getY() + textArea.getHeight()
							));
							g.drawFittedText(std::get<0>(temp),
								textArea.withZeroOrigin().transformedBy(juce::AffineTransform(0, 1, 0, 1, 0, 0)).toNearestInt(),
								juce::Justification::centred, 1, 1);
							g.addTransform(juce::AffineTransform(
								1, 0, 0,
								0, 1, 0
							));
						}
					}
				}

			}
		}

		void FlowContainer::mouseDown(const juce::MouseEvent& event) {
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Title Size */
			float titleSize = (this->isVertical ? FlowStyle::getTitleHeight() : FlowStyle::getTitleWidth())
				* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());

			/** Left Button */
			if (event.mods.isLeftButtonDown()) {
				this->mousePosTemp = event.getPosition();

				float totalSize = 0;
				for (int i = 0; i < this->tabSizeTemp.size(); i++) {
					auto tabSize = std::get<1>(this->tabSizeTemp.getReference(i));
					juce::Rectangle<float> tabArea(
						this->isVertical ? totalSize : 0,
						this->isVertical ? 0 : totalSize,
						this->isVertical ? tabSize : titleSize,
						this->isVertical ? titleSize : tabSize
					);

					if (tabArea.contains(event.getPosition().toFloat())) {
						auto messageManager = juce::MessageManager::getInstance();
						
						messageManager->callAsync([ptr = juce::Component::SafePointer(this), i] {
							if (ptr != nullptr) {
								ptr->setCurrent(i);
							}
						});
						break;
					}

					totalSize += tabSize;
				}

				this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
			}
		}

		void FlowContainer::mouseUp(const juce::MouseEvent& event) {
			/** Left Button */
			if (event.mods.isLeftButtonDown()) {
				if (event.mouseWasDraggedSinceMouseDown()) {
					this->window->getManager()->moveEnd(
						event.getEventRelativeTo(this->window->getManager()).getPosition(),
						-this->mousePosTemp);
					this->mousePosTemp = juce::Point<int>(0, 0);

					/** Get Screen Size */
					auto screenSize = this->window->getScreenSize();

					/** Title Size */
					float titleSize = (this->isVertical ? FlowStyle::getTitleHeight() : FlowStyle::getTitleWidth())
						* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());

					/** Mouse Cursor */
					{
						float totalSize = 0;
						for (int i = 0; i < this->tabSizeTemp.size(); i++) {
							auto tabSize = std::get<1>(this->tabSizeTemp.getReference(i));
							juce::Rectangle<float> tabArea(
								this->isVertical ? totalSize : 0,
								this->isVertical ? 0 : totalSize,
								this->isVertical ? tabSize : titleSize,
								this->isVertical ? titleSize : tabSize
							);

							if (tabArea.contains(event.getPosition().toFloat())) {
								this->setMouseCursor(juce::MouseCursor::PointingHandCursor);
								return;
							}

							totalSize += tabSize;
						}
					}

					this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
				}
			}
		}

		void FlowContainer::mouseMove(const juce::MouseEvent& event) {
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Title Size */
			float titleSize = (this->isVertical ? FlowStyle::getTitleHeight() : FlowStyle::getTitleWidth())
				* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());

			/** Mouse Cursor */
			{
				float totalSize = 0;
				for (int i = 0; i < this->tabSizeTemp.size(); i++) {
					auto tabSize = std::get<1>(this->tabSizeTemp.getReference(i));
					juce::Rectangle<float> tabArea(
						this->isVertical ? totalSize : 0,
						this->isVertical ? 0 : totalSize,
						this->isVertical ? tabSize : titleSize,
						this->isVertical ? titleSize : tabSize
					);

					if (tabArea.contains(event.getPosition().toFloat())) {
						this->setMouseCursor(juce::MouseCursor::PointingHandCursor);
						return;
					}

					totalSize += tabSize;
				}
			}

			this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
		}

		void FlowContainer::mouseDrag(const juce::MouseEvent& event) {
			/** Left Button */
			if (event.mods.isLeftButtonDown()) {
				if (event.mouseWasDraggedSinceMouseDown()) {
					this->window->getManager()->moveProgressing(
						event.getEventRelativeTo(this->window->getManager()).getPosition(),
						-this->mousePosTemp, this);

					this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
				}
			}
		}

		void FlowContainer::mouseExit(const juce::MouseEvent& event) {
			/** Left Button */
			if (event.mods.isLeftButtonDown()) {
				if (event.mouseWasDraggedSinceMouseDown()) {
					this->window->getManager()->moveEnd(
						event.getEventRelativeTo(this->window->getManager()).getPosition(),
						-this->mousePosTemp);
					this->mousePosTemp = juce::Point<int>(0, 0);
				}
			}
		}

		void FlowContainer::updateComponents(bool repaint) {
			/** Component Size */
			{
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
			}
			
			/** Title Size */
			{
				/** Get Screen Size */
				auto screenSize = this->window->getScreenSize();

				/** Get Size */
				float paddingSize =
					(this->isVertical ? FlowStyle::getTitleTextPaddingWidth() : FlowStyle::getTitleTextPaddingHeight())
					* (this->isVertical ? screenSize.getWidth() : screenSize.getHeight());
				float fontSize = (this->isVertical ? FlowStyle::getTitleTextHeight() : FlowStyle::getTitleTextWidth())
					* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());
				float titleLongSideSize = (this->isVertical ? this->getWidth() : this->getHeight());
				float titleShortSideSize = (this->isVertical ? FlowStyle::getTitleHeight() : FlowStyle::getTitleWidth())
					* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());
				
				/** Get Font */
				juce::Font font(fontSize);
				
				/** Get Tab Size */
				this->tabSizeTemp.clear();
				float totalSize = 0;
				for (int i = 0; i < this->components.size(); i++) {
					auto name = this->components.getUnchecked(i)->getName();
					float fontSize = font.getStringWidthFloat(name);
					float tabSize = fontSize + paddingSize * 2;
					this->tabSizeTemp.add(std::make_tuple(name, tabSize, i));
					totalSize += tabSize;
				}

				/** Size Reach Limit */
				if (totalSize > titleLongSideSize) {
					/** Sort by Size */
					struct SortBySizeType {
					public:
						static constexpr auto compareElements(
							const TabSizeTempElement& first,
							const TabSizeTempElement& second) {
							return std::get<1>(second) - std::get<1>(first);
						};
					} sortBySizeComparator;
					this->tabSizeTemp.sort(sortBySizeComparator, false);

					/** Find Minium Limit Element Index */
					int minIndex = 0;
					for (int i = 0; i < this->tabSizeTemp.size() - 1; i++) {
						/** Target Size: nextFullSize */
						auto fullSize = std::get<1>(this->tabSizeTemp.getReference(i));
						auto nextFullSize = std::get<1>(this->tabSizeTemp.getReference(i + 1));
						auto delta = fullSize - nextFullSize;
						totalSize -= delta * (i + 1);

						/** Eligible */
						if (totalSize <= titleLongSideSize) {
							break;
						}

						/** minIndex Increase */
						minIndex = i + 1;
					}

					/** Get Fixed Section Size */
					float fixedLength = 0;
					if (minIndex < this->tabSizeTemp.size() - 1) {
						fixedLength = totalSize - (minIndex + 1) * std::get<1>(this->tabSizeTemp.getReference(minIndex + 1));
					}

					/** Get Dynamic Element Size */
					float dynamicElementSize = (titleLongSideSize - fixedLength) / (minIndex + 1);

					/** Set Dynamic Element Size */
					for (int i = 0; i <= minIndex; i++) {
						std::get<1>(this->tabSizeTemp.getReference(i)) = dynamicElementSize;
					}

					/** Sort by Index */
					struct SortByIndexType {
					public:
						static constexpr auto compareElements(
							const TabSizeTempElement& first,
							const TabSizeTempElement& second) {
							return std::get<2>(first) - std::get<2>(second);
						};
					} sortByIndexComparator;
					this->tabSizeTemp.sort(sortByIndexComparator, false);
				}
			}

			if (repaint) {
				this->repaint();
			}
		}
	}
}