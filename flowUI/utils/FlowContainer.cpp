#include "FlowContainer.h"
#include "FlowWindow.h"
#include "FlowStyle.h"
#include "FlowMenu.h"

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

			this->leftResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::Left, window, this);
			this->rightResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::Right, window, this);
			this->topResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::Top, window, this);
			this->bottomResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::Bottom, window, this);
			this->topLeftResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::TopLeft, window, this);
			this->topRightResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::TopRight, window, this);
			this->bottomLeftResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::BottomLeft, window, this);
			this->bottomRightResizer
				= std::make_unique<FlowContainerResizer>(FlowContainerResizer::ResizerPlace::BottomRight, window, this);

			this->addAndMakeVisible(this->leftResizer.get());
			this->addAndMakeVisible(this->rightResizer.get());
			this->addAndMakeVisible(this->topResizer.get());
			this->addAndMakeVisible(this->bottomResizer.get());
			this->addAndMakeVisible(this->topLeftResizer.get());
			this->addAndMakeVisible(this->topRightResizer.get());
			this->addAndMakeVisible(this->bottomLeftResizer.get());
			this->addAndMakeVisible(this->bottomRightResizer.get());
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

			if (this->current >= this->components.size()) {
				this->current = this->components.size() - 1;
			}

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

		const juce::Point<float> FlowContainer::getMinSize() const {
			auto screenSize = this->window->getScreenSize();
			return juce::Point<float>(
				FlowStyle::getUnitMinimumWidth() * screenSize.getWidth(),
				FlowStyle::getUnitMinimumHeight() * screenSize.getHeight()
			);
		}

		void FlowContainer::setSizeTemp(const juce::Point<int> sizeTemp) {
			this->freeSizeTemp = sizeTemp;
		}

		const juce::Point<int> FlowContainer::getSizeTemp() const {
			return this->freeSizeTemp; 
		}

		void FlowContainer::setResizerShown(bool resizerShown) {
			this->leftResizer->setVisible(resizerShown);
			this->rightResizer->setVisible(resizerShown);
			this->topResizer->setVisible(resizerShown);
			this->bottomResizer->setVisible(resizerShown);
			this->topLeftResizer->setVisible(resizerShown);
			this->topRightResizer->setVisible(resizerShown);
			this->bottomLeftResizer->setVisible(resizerShown);
			this->bottomRightResizer->setVisible(resizerShown);
		}

		void FlowContainer::setVertical(bool isVertical) {
			this->isVertical = isVertical;
			this->updateComponents();
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
					auto splitSize = this->isVertical
						? FlowStyle::getTitleSplitWidth() * screenSize.getWidth()
						: FlowStyle::getTitleSplitHeight() * screenSize.getHeight();
					auto splitLength = this->isVertical
						? FlowStyle::getTitleSplitVLength() * screenSize.getHeight()
						: FlowStyle::getTitleSplitHLength() * screenSize.getWidth();

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
						if (i == this->current) {
							g.setColour(FlowStyle::getTitleHighlightColor());
							g.fillRect(tabArea);
						}
						
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
							if (textArea.getWidth() < 0) { textArea.setWidth(0); }
							g.setColour((i == this->current) ? FlowStyle::getTitleTextHighlightColor() : FlowStyle::getTitleTextColor());
							g.drawFittedText(std::get<0>(temp), textArea.toNearestInt(), juce::Justification::centred, 1, .9f);
						}
						else {
							juce::Rectangle<float> textArea = tabArea
								.withTrimmedTop(paddingSize).withTrimmedBottom(paddingSize);
							if (textArea.getHeight() < 0) { textArea.setHeight(0); }
							g.setColour((i == this->current) ? FlowStyle::getTitleTextHighlightColor() : FlowStyle::getTitleTextColor());

							g.saveState();
							g.addTransform(juce::AffineTransform(
								0, 1, textArea.getX(),
								-1, 0, textArea.getY() + textArea.getHeight()
							));
							g.drawFittedText(std::get<0>(temp),
								textArea.withZeroOrigin().transformedBy(juce::AffineTransform(0, 1, 0, 1, 0, 0)).toNearestInt(),
								juce::Justification::centred, 1, .9f);
							g.restoreState();
						}

						/** Split Line */
						if (i != this->current && (i + 1) != this->current) {
							juce::Rectangle<float> splitRect(
								this->isVertical ? tabTotalSize - splitSize / 2 : (FlowStyle::getTitleWidth() * screenSize.getWidth()) / 2 - splitLength / 2,
								this->isVertical ? (FlowStyle::getTitleHeight() * screenSize.getHeight()) / 2 - splitLength / 2 : tabTotalSize - splitSize / 2,
								this->isVertical ? splitSize : splitLength,
								this->isVertical ? splitLength : splitSize
							);
							g.setColour(FlowStyle::getTitleSplitColor());
							g.fillRect(splitRect);
						}
					}
				}

			}
		}

		void FlowContainer::paintOverChildren(juce::Graphics& g) {
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();
			auto borderSize = FlowStyle::getContainerBorderSize() * screenSize.getWidth();

			/** Draw Border */
			g.setColour(FlowStyle::getContainerBorderColor());
			g.drawRect(this->getLocalBounds(), borderSize);
		}

		void FlowContainer::mouseDown(const juce::MouseEvent& event) {
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Title Size */
			float titleSize = (this->isVertical ? FlowStyle::getTitleHeight() : FlowStyle::getTitleWidth())
				* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());

			/** Left / Right Button */
			if (event.mods.isLeftButtonDown() || event.mods.isRightButtonDown()) {
				this->toFront(true);
				if (event.mods.isLeftButtonDown()) {
					this->mousePosTemp = event.getPosition();
				}

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

				if (event.mods.isLeftButtonDown()) {
					this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
				}
			}
		}

		void FlowContainer::mouseUp(const juce::MouseEvent& event) {
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Title Size */
			float titleSize = (this->isVertical ? FlowStyle::getTitleHeight() : FlowStyle::getTitleWidth())
				* (this->isVertical ? screenSize.getHeight() : screenSize.getWidth());

			/** Left Button */
			if (event.mods.isLeftButtonDown()) {
				if (event.mouseWasDraggedSinceMouseDown()) {
					auto messageManager = juce::MessageManager::getInstance();
					if (messageManager) {
						messageManager->callAsync(
							[point = event.getEventRelativeTo(this->window->getManager()).getPosition(),
							distance = -this->mousePosTemp,
							manager = this->window->getManager()] {
								manager->moveEnd(point, distance);
							}
						);
					}
					this->mousePosTemp = juce::Point<int>();
				}

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
			/** Right Menu */
			else if (event.mods.isRightButtonDown()) {
				/** Find Tab */
				int tabIndex = -1;
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
							tabIndex = i;
							break;
						}

						totalSize += tabSize;
					}
				}

				auto messageManager = juce::MessageManager::getInstance();
				if (messageManager) {
					messageManager->callAsync(
						[this, tabIndex] {
							this->showMenu(tabIndex);
						}
					);
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
					auto messageManager = juce::MessageManager::getInstance();
					if (messageManager) {
						messageManager->callAsync(
							[point = event.getEventRelativeTo(this->window->getManager()).getPosition(),
							distance = -this->mousePosTemp,
							this,
							manager = this->window->getManager()] {
								manager->moveProgressing(point, distance, this);
							}
						);
					}

					this->setMouseCursor(juce::MouseCursor::DraggingHandCursor);
				}
			}
		}

		void FlowContainer::mouseExit(const juce::MouseEvent& event) {
			/** Left Button */
			if (event.mods.isLeftButtonDown()) {
				if (event.mouseWasDraggedSinceMouseDown()) {
					auto messageManager = juce::MessageManager::getInstance();
					if (messageManager) {
						messageManager->callAsync(
							[point = event.getEventRelativeTo(this->window->getManager()).getPosition(),
							distance = -this->mousePosTemp,
							manager = this->window->getManager()] {
								manager->moveEnd(point, distance);
							}
						);
					}
					this->mousePosTemp = juce::Point<int>();
				}
			}
		}

		void FlowContainer::parentHierarchyChanged() {
			this->setResizerShown(dynamic_cast<FlowManager*>(this->getParentComponent()));
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
			
			/** Get Screen Size */
			auto screenSize = this->window->getScreenSize();

			/** Title Size */
			{
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

			/** Resizer Size */
			{
				auto resizerWidth = FlowStyle::getResizerWidth() * screenSize.getWidth();
				auto resizerHeight = FlowStyle::getResizerHeight() * screenSize.getHeight();

				auto bounds = this->getLocalBounds();
				auto leftBounds = bounds
					.withTrimmedRight(bounds.getWidth() - resizerWidth)
					.withTrimmedTop(resizerHeight).withTrimmedBottom(resizerHeight);
				auto rightBounds = bounds
					.withTrimmedLeft(bounds.getWidth() - resizerWidth)
					.withTrimmedTop(resizerHeight).withTrimmedBottom(resizerHeight);
				auto topBounds = bounds
					.withTrimmedBottom(bounds.getHeight() - resizerHeight)
					.withTrimmedLeft(resizerWidth).withTrimmedRight(resizerWidth);
				auto bottomBounds = bounds
					.withTrimmedTop(bounds.getHeight() - resizerHeight)
					.withTrimmedLeft(resizerWidth).withTrimmedRight(resizerWidth);
				auto topLeftBounds = bounds
					.withTrimmedBottom(bounds.getHeight() - resizerHeight)
					.withTrimmedRight(bounds.getWidth() - resizerWidth);
				auto topRightBounds = bounds
					.withTrimmedBottom(bounds.getHeight() - resizerHeight)
					.withTrimmedLeft(bounds.getWidth() - resizerWidth);
				auto bottomLeftBounds = bounds
					.withTrimmedTop(bounds.getHeight() - resizerHeight)
					.withTrimmedRight(bounds.getWidth() - resizerWidth);
				auto bottomRightBounds = bounds
					.withTrimmedTop(bounds.getHeight() - resizerHeight)
					.withTrimmedLeft(bounds.getWidth() - resizerWidth);

				this->leftResizer->setBounds(leftBounds);
				this->rightResizer->setBounds(rightBounds);
				this->topResizer->setBounds(topBounds);
				this->bottomResizer->setBounds(bottomBounds);
				this->topLeftResizer->setBounds(topLeftBounds);
				this->topRightResizer->setBounds(topRightBounds);
				this->bottomLeftResizer->setBounds(bottomLeftBounds);
				this->bottomRightResizer->setBounds(bottomRightBounds);

				this->leftResizer->toFront(false);
				this->rightResizer->toFront(false);
				this->topResizer->toFront(false);
				this->bottomResizer->toFront(false);
				this->topLeftResizer->toFront(false);
				this->topRightResizer->toFront(false);
				this->bottomLeftResizer->toFront(false);
				this->bottomRightResizer->toFront(false);
			}

			if (repaint) {
				this->repaint();
			}
		}

		void FlowContainer::showMenu(int tabIndex) {
			bool isTab = tabIndex >= 0 && tabIndex < this->components.size();
			bool isFree = dynamic_cast<FlowManager*>(this->getParentComponent());
			bool isMulti = this->components.size() > 1;
			bool isVertical = this->isVertical;

			auto messageManager = juce::MessageManager::getInstance();
			if (!messageManager) { return; }

			auto menu = FlowMenu::createContainerMenu(isTab, isFree, isMulti, isVertical);

			int result = menu.show();
			switch (result) {
			case 1:
				messageManager->callAsync(
					[manager = this->window->getManager(),
					comp = this->components[tabIndex]] {
						manager->releaseComponent(comp);
					}
				);
				break;
			case 2:
				messageManager->callAsync(
					[manager = this->window->getManager(),
					this] {
						manager->releaseContainer(this);
					}
				);
				break;
			case 3:
				messageManager->callAsync(
					[this, vertical = !isVertical] {
						this->setVertical(vertical);
					}
				);
				break;
			}
		}
	}
}
