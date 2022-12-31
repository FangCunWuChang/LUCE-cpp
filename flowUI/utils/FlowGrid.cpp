#include "FlowGrid.h"
#include "FlowWindow.h"
#include "FlowStyle.h"

namespace luce {
	namespace utils {
		FlowGrid::FlowGrid(FlowWindow* window)
			: FlowGridableUnit(window, false) {
			/** Resize Manager */
			this->manager = std::make_unique<juce::StretchableLayoutManager>();

			/** Resize Bar Look And Feel */
			class StretchableBarLAF final : public juce::LookAndFeel_V4 {
			public:
				StretchableBarLAF() = default;
				~StretchableBarLAF() override = default;

				void drawStretchableLayoutResizerBar(juce::Graphics& g, int /*w*/, int /*h*/, bool /*isVerticalBar*/,
					bool /*isMouseOver*/, bool isMouseDragging) override
				{
					g.fillAll(FlowStyle::getResizerColor());
					if (isMouseDragging)
						g.fillAll(FlowStyle::getResizerColor().contrasting(0.2f));
				};

			private:
				JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StretchableBarLAF)
			};
			this->resizerLookAndFeel = std::unique_ptr<juce::LookAndFeel>(new StretchableBarLAF);
		}

		FlowGrid::~FlowGrid() {
			for (auto i : this->resizers) {
				i->setLookAndFeel(nullptr);
			}
		}

		bool FlowGrid::addContainer(
			FlowContainer* container,
			FlowContainer* base,
			FlowGrid::ContainerAddPlace place) {
			/** Base Is In This Grid */
			int baseIndex = -1;
			for (int i = 0; i < this->units.size(); i++) {
				if (this->units.getUnchecked(i) == base) {
					baseIndex = i;
					break;
				}
			}

			if (baseIndex >= 0 && baseIndex < this->units.size()) {
				/** In Center */
				if (place == ContainerAddPlace::Center) {
					container->moveTo(base);
					delete container;
					return true;
				}

				/** Check For Layer Increase */
				bool layerIncrease = false;
				if (this->units.size() > 1) {
					layerIncrease = this->isVertical
						? (place == ContainerAddPlace::Left || place == ContainerAddPlace::Right)
						: (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);
				}

				if (layerIncrease) {
					/** Grid Layer Increase */
					bool subIsVertical = (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);
					auto newGrid = new FlowGrid(this->window);
					this->units.insert(baseIndex, newGrid);
					
					/** Grid Size */
					this->addChildComponent(newGrid);
					newGrid->setBounds(base->getBounds());
					this->removeChildComponent(base);

					/** Layer Relative */
					newGrid->units.add(base);
					newGrid->addChildComponent(base);
					newGrid->addContainer(container, base, place);

					/** Refresh */
					this->updateComponents();
					return true;
				}
				else {
					/** Set Vertical Mode */
					this->isVertical = (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);

					/** Insert Unit */
					this->addChildComponent(container);
					if (place == ContainerAddPlace::Left || place == ContainerAddPlace::Top) {
						/** Insert */
						this->units.insert(baseIndex, container);

						baseIndex += 1;

						/** Resize */
						if (place == ContainerAddPlace::Left) {
							auto baseBounds = base->getBounds();
							base->setBounds(baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2));
							container->setBounds(baseBounds.withTrimmedRight(baseBounds.getWidth() / 2));
						}
						else {
							auto baseBounds = base->getBounds();
							base->setBounds(baseBounds.withTrimmedTop(baseBounds.getHeight() / 2));
							container->setBounds(baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2));
						}
					}
					else {
						/** Insert */
						this->units.insert(baseIndex + 1, container);

						/** Resize */
						if (place == ContainerAddPlace::Right) {
							auto baseBounds = base->getBounds();
							base->setBounds(baseBounds.withTrimmedRight(baseBounds.getWidth() / 2));
							container->setBounds(baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2));
						}
						else {
							auto baseBounds = base->getBounds();
							base->setBounds(baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2));
							container->setBounds(baseBounds.withTrimmedTop(baseBounds.getHeight() / 2));
						}
					}

					/** Refresh */
					this->updateComponents();
					return true;
				}
			}
			else {
				/** Check If Base Is In Child */
				for (int i = 0; i < this->units.size(); i++) {
					if (!this->units.getUnchecked(i)->thisIsContainer()) {
						auto ptrGrid = dynamic_cast<FlowGrid*>(this->units.getUnchecked(i));
						if (ptrGrid->addContainer(container, base, place)) {
							return true;
						}
					}
				}
				return false;
			}
		}

		bool FlowGrid::addContainerOutside(
			FlowContainer* container,
			FlowGrid::ContainerAddPlace place) {
			/** Add Child In Empty Grid Should Use addUniqueUnit Method ! */
			if (this->units.size() < 1) { return this->addUniqueUnit(container); }

			/** In Center */
			if (place == ContainerAddPlace::Center) {
				jassertfalse;
				return false;
			}

			/** Check For Layer Increase */
			bool layerIncrease = false;
			if (this->units.size() > 1) {
				layerIncrease = this->isVertical
					? (place == ContainerAddPlace::Left || place == ContainerAddPlace::Right)
					: (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);
			}

			if (layerIncrease) {
				/** Grid Layer Increase */
				this->isVertical = (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);
				auto newGrid = new FlowGrid(this->window);
				while (this->units.size() > 0) {
					auto subUnit = this->units.removeAndReturn(0);
					this->removeChildComponent(subUnit);
					newGrid->units.add(subUnit);
					newGrid->addChildComponent(subUnit);
				}
				this->units.add(newGrid);
				this->addChildComponent(newGrid);

				/** Grid Size */
				auto bounds = this->getLocalBounds();
				this->addChildComponent(container);
				if (place == ContainerAddPlace::Left) {
					newGrid->setBounds(bounds.withTrimmedLeft(bounds.getWidth() / 2));
					container->setBounds(bounds.withTrimmedRight(bounds.getWidth() / 2));
				}
				else if (place == ContainerAddPlace::Right) {
					newGrid->setBounds(bounds.withTrimmedRight(bounds.getWidth() / 2));
					container->setBounds(bounds.withTrimmedLeft(bounds.getWidth() / 2));
				}
				else if (place == ContainerAddPlace::Top) {
					newGrid->setBounds(bounds.withTrimmedTop(bounds.getHeight() / 2));
					container->setBounds(bounds.withTrimmedBottom(bounds.getHeight() / 2));
				}
				else {
					newGrid->setBounds(bounds.withTrimmedBottom(bounds.getHeight() / 2));
					container->setBounds(bounds.withTrimmedTop(bounds.getHeight() / 2));
				}

				/** Refresh */
				newGrid->updateComponents();
				this->updateComponents();
				return true;
			}
			else {
				/** Set Vertical Mode */
				this->isVertical = (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);

				if (place == ContainerAddPlace::Left || place == ContainerAddPlace::Top) {
					this->units.insert(0, container);
					this->addChildComponent(container);

					auto unitBounds = this->units.getUnchecked(1)->getBounds();
					if (place == ContainerAddPlace::Left) {
						this->units.getUnchecked(1)->setBounds(unitBounds.withTrimmedLeft(unitBounds.getWidth() / 2));
						container->setBounds(unitBounds.withTrimmedRight(unitBounds.getWidth() / 2));
					}
					else {
						this->units.getUnchecked(1)->setBounds(unitBounds.withTrimmedTop(unitBounds.getHeight() / 2));
						container->setBounds(unitBounds.withTrimmedBottom(unitBounds.getHeight() / 2));
					}
				}
				else {
					this->units.add(container);
					this->addChildComponent(container);

					auto unitBounds = this->units.getUnchecked(this->units.size() - 2)->getBounds();
					if (place == ContainerAddPlace::Right) {
						this->units.getUnchecked(1)->setBounds(unitBounds.withTrimmedRight(unitBounds.getWidth() / 2));
						container->setBounds(unitBounds.withTrimmedLeft(unitBounds.getWidth() / 2));
					}
					else {
						this->units.getUnchecked(1)->setBounds(unitBounds.withTrimmedBottom(unitBounds.getHeight() / 2));
						container->setBounds(unitBounds.withTrimmedTop(unitBounds.getHeight() / 2));
					}
				}

				/** Refresh */
				this->updateComponents();
				return true;
			}
		}

		bool FlowGrid::releaseContainer(FlowContainer* container) {
			/** Unit Is In This Grid */
			int unitIndex = -1;
			for (int i = 0; i < this->units.size(); i++) {
				if (this->units.getUnchecked(i) == container) {
					unitIndex = i;
					break;
				}
			}

			if (unitIndex >= 0 && unitIndex < this->units.size()) {
				/** Remove Unique Child Should Use releaseUniqueUnit Method ! */
				if (this->units.size() == 1) {
					return this->releaseUniqueUnit(container);
				}

				/** Release */
				this->units.removeAndReturn(unitIndex);
				this->removeChildComponent(container);

				if (this->units.size() == 1) {
					auto parent = dynamic_cast<FlowGrid*>(this->getParentComponent());
					if (parent) {
						parent->decreaseLayer(this);
					}
				}
				else {
					/** Refresh */
					this->updateComponents();
				}
				return true;
			}
			else {
				/** Check If Is In Child */
				for (int i = 0; i < this->units.size(); i++) {
					if (!this->units.getUnchecked(i)->thisIsContainer()) {
						auto ptrGrid = dynamic_cast<FlowGrid*>(this->units.getUnchecked(i));
						if (ptrGrid->releaseContainer(container)) {
							return true;
						}
					}
				}
				return false;
			}
		}

		bool FlowGrid::isEmpty() const {
			return this->units.size() == 0;
		}

		FlowContainer* FlowGrid::findComponent(FlowComponent* comp) const {
			for (auto i : this->units) {
				if (auto ptr = i->findComponent(comp)) {
					return ptr;
				}
			}
			return nullptr;
		}

		bool FlowGrid::findContainer(FlowContainer* container) const {
			for (auto i : this->units) {
				if (i->thisIsContainer()) {
					if (i == container) {
						return true;
					}
				}
				else {
					if (dynamic_cast<FlowGrid*>(i)->findContainer(container)) {
						return true;
					}
				}
			}
			return false;
		}

		juce::Rectangle<int> FlowGrid::findAdsorbRect(juce::Point<int> point) const {
			auto ptrContainer = this->findAdsorbContainer(point);
			if (ptrContainer) {
				auto bounds = ptrContainer->getScreenBounds();
				bounds.setPosition(bounds.getTopLeft() - this->window->getManager()->getScreenPosition());
				return bounds;
			}
			return juce::Rectangle<int>(0, 0, 0, 0);
		}

		FlowContainer* FlowGrid::findAdsorbContainer(juce::Point<int> point) const {
			for (auto i : this->units) {
				if (i->getBounds().contains(point)) {
					if (i->thisIsContainer()) {
						return dynamic_cast<FlowContainer*>(i);
					}
					else {
						return dynamic_cast<FlowGrid*>(i)->findAdsorbContainer(point - i->getPosition());
					}
				}
			}
			return nullptr;
		}

		bool FlowGrid::addUniqueUnit(FlowContainer* container) {
			if (this->units.size() > 0) {
				jassertfalse;
				return false;
			}

			this->units.add(container);
			this->addChildComponent(container);
			
			this->updateComponents();
			return true;
		}

		bool FlowGrid::releaseUniqueUnit(FlowContainer* container) {
			if (this->units.size() != 1) {
				jassertfalse;
				return false;
			}

			if (this->units.getUnchecked(0) != container) {
				jassertfalse;
				return false;
			}

			this->removeChildComponent(this->units.getUnchecked(0));
			this->units.removeAndReturn(0);

			this->updateComponents();
			return true;
		}

		void FlowGrid::decreaseLayer(FlowGrid* layer) {
			/** Unit Is In This Grid */
			int unitIndex = -1;
			for (int i = 0; i < this->units.size(); i++) {
				if (this->units.getUnchecked(i) == layer) {
					unitIndex = i;
					break;
				}
			}

			if (unitIndex >= 0 && unitIndex < this->units.size()) {
				/** Must Decrease Layer With Unique Unit ! */
				if (layer->units.size() != 1) {
					jassertfalse;
					return;
				}

				/** Get Size And Release */
				auto bounds = layer->getBounds();
				this->removeChildComponent(layer);
				auto child = layer->units.removeAndReturn(0);
				this->addChildComponent(child);
				child->setBounds(bounds);

				this->units.removeAndReturn(unitIndex);
				this->units.insert(unitIndex, child);
				delete layer;

				/** Refresh */
				this->updateComponents();
				return;
			}
		}

		void FlowGrid::resized() {
			if (this->boundsTemp != this->getLocalBounds()) {
				this->boundsTemp = this->getLocalBounds();
				this->updateComponents();
			}
		}

		void FlowGrid::updateComponents() {
			/** Component List */
			juce::Array<juce::Component*> compList;
			compList.addArray(this->units);

			/** Resizers */
			for (auto i : this->resizers) {
				this->removeChildComponent(i);
			}
			this->resizers.clear();
			for (int i = 0; i < this->units.size() - 1; i++) {
				auto resizer = new juce::StretchableLayoutResizerBar(
					this->manager.get(), 2 * i + 1, !this->isVertical);

				resizer->setLookAndFeel(this->resizerLookAndFeel.get());
				this->resizers.add(resizer);
				this->addChildComponent(resizer);
				compList.insert(i * 2 + 1, this->resizers.getUnchecked(i));
			}

			/** Sizes */
			auto screenSize = this->window->getScreenSize();
			float resizerSize = this->isVertical
				? (FlowStyle::getResizerHeight() * screenSize.getHeight())
				: (FlowStyle::getResizerWidth() * screenSize.getWidth());
			float unitMinSize = this->isVertical
				? (FlowStyle::getUnitMinimumHeight() * screenSize.getHeight())
				: (FlowStyle::getUnitMinimumWidth() * screenSize.getWidth());
			float unitMaxSize = this->isVertical
				? (FlowStyle::getUnitMaximumHeight() * screenSize.getHeight())
				: (FlowStyle::getUnitMaximumWidth() * screenSize.getWidth());

			/** Size Percent */
			float totalSize = 0;
			for (auto i : this->units) {
				totalSize += (this->isVertical ? i->getHeight() : i->getWidth());
			}
			juce::Array<float> sizeList;
			for (auto i : this->units) {
				sizeList.add((this->isVertical ? i->getHeight() : i->getWidth()) / totalSize);
			}

			/** Size Rule */
			this->manager->clearAllItems();
			for (int i = 0; i < compList.size(); i++) {
				this->manager->setItemLayout(i,
					(i % 2 == 0) ? unitMinSize : resizerSize,
					(i % 2 == 0) ? unitMaxSize : resizerSize,
					(i % 2 == 0) ? -sizeList[(int)(i / 2.)] : resizerSize
				);
			}

			/** Apply Size */
			this->manager->layOutComponents(compList.getRawDataPointer(), compList.size(),
				0, 0, this->getWidth(), this->getHeight(), this->isVertical, true);

			/** Show */
			for (auto i : compList) {
				i->setVisible(true);
			}
		}
	}
}
