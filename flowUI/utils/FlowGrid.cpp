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
			int baseIndex = this->units.indexOf(base);

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
					this->units.removeAndReturn(baseIndex);
					this->units.insert(baseIndex, newGrid);
					
					/** Grid Size */
					this->addChildComponent(newGrid);
					auto containerBounds = container->getBounds();
					auto baseBounds = base->getBounds();
					if (place == ContainerAddPlace::Left) {
						if (containerBounds.getWidth() <= baseBounds.getWidth() / 2) {
							newGrid->setBounds(baseBounds.withTrimmedLeft(containerBounds.getWidth()));
						}
						else {
							newGrid->setBounds(baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2));
							container->setBounds(baseBounds.withTrimmedRight(baseBounds.getWidth() / 2));
						}
					}
					else if (place == ContainerAddPlace::Right) {
						if (containerBounds.getWidth() <= baseBounds.getWidth() / 2) {
							newGrid->setBounds(baseBounds.withTrimmedRight(containerBounds.getWidth()));
						}
						else {
							newGrid->setBounds(baseBounds.withTrimmedRight(baseBounds.getWidth() / 2));
							container->setBounds(baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2));
						}
					}
					else if (place == ContainerAddPlace::Top) {
						if (containerBounds.getHeight() <= baseBounds.getHeight() / 2) {
							newGrid->setBounds(baseBounds.withTrimmedTop(containerBounds.getHeight()));
						}
						else {
							newGrid->setBounds(baseBounds.withTrimmedTop(baseBounds.getHeight() / 2));
							container->setBounds(baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2));
						}
					}
					else {
						if (containerBounds.getHeight() <= baseBounds.getHeight() / 2) {
							newGrid->setBounds(baseBounds.withTrimmedBottom(containerBounds.getHeight()));
						}
						else {
							newGrid->setBounds(baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2));
							container->setBounds(baseBounds.withTrimmedTop(baseBounds.getHeight() / 2));
						}
					}
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
						{
							auto baseBounds = base->getBounds();
							auto containerBounds = container->getBounds();
							if (place == ContainerAddPlace::Left) {
								if (containerBounds.getWidth() <= baseBounds.getWidth() / 2) {
									base->setBounds(baseBounds.withTrimmedLeft(containerBounds.getWidth()));
								}
								else {
									base->setBounds(baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2));
									container->setBounds(baseBounds.withTrimmedRight(baseBounds.getWidth() / 2));
								}
							}
							else {
								if (containerBounds.getHeight() <= baseBounds.getHeight() / 2) {
									base->setBounds(baseBounds.withTrimmedTop(containerBounds.getHeight()));
								}
								else {
									base->setBounds(baseBounds.withTrimmedTop(baseBounds.getHeight() / 2));
									container->setBounds(baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2));
								}
							}
						}
					}
					else {
						/** Insert */
						this->units.insert(baseIndex + 1, container);

						/** Resize */
						{
							auto baseBounds = base->getBounds();
							auto containerBounds = container->getBounds();
							if (place == ContainerAddPlace::Right) {
								if (containerBounds.getWidth() <= baseBounds.getWidth() / 2) {
									base->setBounds(baseBounds.withTrimmedRight(containerBounds.getWidth()));
								}
								else {
									base->setBounds(baseBounds.withTrimmedRight(baseBounds.getWidth() / 2));
									container->setBounds(baseBounds.withTrimmedLeft(baseBounds.getWidth() / 2));
								}
							}
							else {
								if (containerBounds.getHeight() <= baseBounds.getHeight() / 2) {
									base->setBounds(baseBounds.withTrimmedBottom(containerBounds.getHeight()));
								}
								else {
									base->setBounds(baseBounds.withTrimmedBottom(baseBounds.getHeight() / 2));
									container->setBounds(baseBounds.withTrimmedTop(baseBounds.getHeight() / 2));
								}
							}
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
							this->updateComponents();
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
				auto verticalStateTemp = this->isVertical;
				this->isVertical = (place == ContainerAddPlace::Top || place == ContainerAddPlace::Bottom);
				/** New Layer */
				auto newGrid = new FlowGrid(this->window);
				newGrid->isVertical = verticalStateTemp;
				/** Move Units In Current Layer To The New Layer */
				while (this->units.size() > 0) {
					auto subUnit = this->units.removeAndReturn(0);
					this->removeChildComponent(subUnit);
					newGrid->units.add(subUnit);
					newGrid->addChildComponent(subUnit);
				}
				/** Add Relative Of New Layer */
				this->units.add(newGrid);
				this->addChildComponent(newGrid);

				/** Grid Size */
				auto bounds = this->getLocalBounds();
				auto containerBounds = container->getBounds();
				/** Add Relative Of THe New Container */
				this->addChildComponent(container);
				/** Set The Size Of The New Layer And The Container */
				if (place == ContainerAddPlace::Left) {
					this->units.insert(0, container);
					if (containerBounds.getWidth() <= bounds.getWidth() / 2) {
						newGrid->setBounds(bounds.withTrimmedLeft(containerBounds.getWidth()));
					}
					else {
						newGrid->setBounds(bounds.withTrimmedLeft(bounds.getWidth() / 2));
						container->setBounds(bounds.withTrimmedRight(bounds.getWidth() / 2));
					}
				}
				else if (place == ContainerAddPlace::Right) {
					this->units.add(container);
					if (containerBounds.getWidth() <= bounds.getWidth() / 2) {
						newGrid->setBounds(bounds.withTrimmedRight(containerBounds.getWidth()));
					}
					else {
						newGrid->setBounds(bounds.withTrimmedRight(bounds.getWidth() / 2));
						container->setBounds(bounds.withTrimmedLeft(bounds.getWidth() / 2));
					}
				}
				else if (place == ContainerAddPlace::Top) {
					this->units.insert(0, container);
					if (containerBounds.getHeight() <= bounds.getHeight() / 2) {
						newGrid->setBounds(bounds.withTrimmedTop(containerBounds.getHeight()));
					}
					else {
						newGrid->setBounds(bounds.withTrimmedTop(bounds.getHeight() / 2));
						container->setBounds(bounds.withTrimmedBottom(bounds.getHeight() / 2));
					}
				}
				else {
					this->units.add(container);
					if (containerBounds.getHeight() <= bounds.getHeight() / 2) {
						newGrid->setBounds(bounds.withTrimmedBottom(containerBounds.getHeight()));
					}
					else {
						newGrid->setBounds(bounds.withTrimmedBottom(bounds.getHeight() / 2));
						container->setBounds(bounds.withTrimmedTop(bounds.getHeight() / 2));
					}
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
					/** Add Relative Of The Container */
					this->units.insert(0, container);
					this->addChildComponent(container);

					/** Set Container Size */
					auto bounds = this->getLocalBounds();
					auto containerBounds = container->getBounds();
					if (place == ContainerAddPlace::Left) {
						if (containerBounds.getWidth() <= bounds.getWidth() / 2) {
							for (int i = 1; i < this->units.size(); i++) {
								auto unit = this->units.getUnchecked(i);
								unit->setSize(
									unit->getWidth() - containerBounds.getWidth() * ((float)unit->getWidth() / bounds.getWidth()),
									unit->getHeight());
							}
						}
						else {
							container->setBounds(bounds);
						}
					}
					else {
						if (containerBounds.getHeight() <= bounds.getHeight() / 2) {
							for (int i = 1; i < this->units.size(); i++) {
								auto unit = this->units.getUnchecked(i);
								unit->setSize(
									unit->getWidth(),
									unit->getHeight() - containerBounds.getHeight() * ((float)unit->getHeight() / bounds.getHeight()));
							}
						}
						else {
							container->setBounds(bounds);
						}
					}
				}
				else {
					/** Add Relative Of The Container */
					this->units.add(container);
					this->addChildComponent(container);

					/** Set Container Size */
					auto bounds = this->getLocalBounds();
					auto containerBounds = container->getBounds();
					if (place == ContainerAddPlace::Right) {
						if (containerBounds.getWidth() <= bounds.getWidth() / 2) {
							for (int i = 1; i < this->units.size(); i++) {
								auto unit = this->units.getUnchecked(i);
								unit->setSize(
									unit->getWidth() - containerBounds.getWidth() * ((float)unit->getWidth() / bounds.getWidth()),
									unit->getHeight());
							}
						}
						else {
							container->setBounds(bounds);
						}
					}
					else {
						if (containerBounds.getHeight() <= bounds.getHeight() / 2) {
							for (int i = 1; i < this->units.size(); i++) {
								auto unit = this->units.getUnchecked(i);
								unit->setSize(
									unit->getWidth(),
									unit->getHeight() - containerBounds.getHeight() * ((float)unit->getHeight() / bounds.getHeight()));
							}
						}
						else {
							container->setBounds(bounds);
						}
					}
				}

				/** Refresh */
				this->updateComponents();
				return true;
			}
		}

		bool FlowGrid::releaseContainer(FlowContainer* container) {
			/** Unit Is In This Grid */
			int unitIndex = this->units.indexOf(container);

			if (unitIndex >= 0 && unitIndex < this->units.size()) {
				/** Remove Unique Child Should Use releaseUniqueUnit Method ! */
				if (this->units.size() == 1) {
					return this->releaseUniqueUnit(container);
				}

				/** Release */
				this->units.removeAndReturn(unitIndex);
				this->removeChildComponent(container);

				if (this->units.size() == 1) {
					/** Decrease Layer */
					this->decreaseLayer();
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
							this->updateComponents();
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

		const juce::Point<float> FlowGrid::getMinSize() const {
			auto screenSize = this->window->getScreenSize();
			auto unitMinWidth = FlowStyle::getUnitMinimumWidth() * screenSize.getWidth();
			auto unitMinHeight = FlowStyle::getUnitMinimumHeight() * screenSize.getHeight();
			auto resizerSize = this->isVertical
				? (FlowStyle::getResizerHeight() * screenSize.getHeight())
				: (FlowStyle::getResizerWidth() * screenSize.getWidth());

			if (this->units.size() == 0) {
				return juce::Point<float>(unitMinWidth, unitMinHeight);
			}

			float minWidth = 0, minHeight = 0;
			for (auto i : this->units) {
				auto unitMinSize = i->getMinSize();
				if (this->isVertical) {
					minWidth = juce::jmax(minWidth, unitMinSize.getX());
					minHeight += unitMinSize.getY();
				}
				else {
					minWidth += unitMinSize.getX();
					minHeight = juce::jmax(minHeight, unitMinSize.getY());
				}
			}
			if (this->isVertical) {
				minHeight += this->resizers.size() * resizerSize;
			}
			else {
				minWidth += this->resizers.size() * resizerSize;
			}
			return juce::Point<float>(minWidth, minHeight);
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

		const juce::Array<FlowContainer*> FlowGrid::getAllContainers() const {
			juce::Array<FlowContainer*> result;
			for (auto i : this->units) {
				if (auto ptr = dynamic_cast<FlowGrid*>(i)) {
					result.addArray(ptr->getAllContainers());
				}
				else {
					result.add(dynamic_cast<FlowContainer*>(i));
				}
			}
			return result;
		}

		void FlowGrid::autoLayout(const juce::var& grid, juce::Array<FlowComponent*> list) {
			/** Error */
			if (!grid.isObject()) { jassertfalse;  return; }
			
			/** Clear Units */
			for (auto i : this->units) {
				this->removeChildComponent(i);
			}
			this->units.clear();

			/** Get Units */
			this->isVertical = grid["vertical"];

			auto size = grid.getProperty("size", juce::var());
			if (!size.isArray()) {
				jassertfalse;
				this->updateComponents();
				return;
			}
			auto sizeList = size.getArray();

			auto unit = grid.getProperty("unit", juce::var());
			if (!unit.isArray()) {
				jassertfalse;
				this->updateComponents();
				return;
			}
			auto unitList = unit.getArray();

			if (unitList->size() != sizeList->size()) {
				jassertfalse;
				this->updateComponents();
				return;
			}

			for (int i = 0; i < unitList->size(); i++) {
				auto& unit = unitList->getReference(i);

				/** Error */
				if (!unit.isObject()) {
					jassertfalse;
					this->updateComponents();
					return;
				}

				/** Size */
				auto screenSize = this->window->getScreenSize();
				auto unitWidth = this->isVertical ? this->getWidth() : (float)sizeList->getReference(i) * this->getWidth();
				auto unitHeight = this->isVertical ? (float)sizeList->getReference(i) * this->getHeight() : this->getHeight();
				auto defaultWidth = FlowStyle::getContainerDefaultWidth() * screenSize.getWidth();
				auto defaultHeight = FlowStyle::getContainerDefaultHeight() * screenSize.getHeight();
				juce::Point<int> defaultSize(defaultWidth, defaultHeight);

				/** Container */
				if (unit.hasProperty("id")) {
					auto container = new FlowContainer(this->window);
					this->addChildComponent(container);
					this->units.add(container);
					container->setSize(unitWidth, unitHeight);
					
					container->autoLayout(unit, list);
				}
				/** Grid */
				else {
					auto grid = new FlowGrid(this->window);
					this->addChildComponent(grid);
					this->units.add(grid);
					grid->setSize(unitWidth, unitHeight);

					grid->autoLayout(unit, list);
				}
			}

			/** Refresh */
			this->updateComponents();
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

			/** GC Layer */
			auto parentLayer = dynamic_cast<FlowGrid*>(this->getParentComponent());
			if (parentLayer) {
				parentLayer->gcLayer(this);
			}
			else {
				this->updateComponents();
			}
			
			return true;
		}

		void FlowGrid::decreaseLayer() {
			/** This Layer Containers Only One Unit */
			if (this->units.size() != 1) {
				jassertfalse;
				this->updateComponents();
				return;
			}
			
			auto subLayer = dynamic_cast<FlowGrid*>(this->units.getUnchecked(0));
			if (subLayer) {
				/** Remove Relative Of SubLayer */
				this->removeChildComponent(subLayer);
				this->units.removeAndReturn(0);

				/** Move All Units In The SubLayer To Current Layer */
				this->isVertical = subLayer->isVertical;
				while (subLayer->units.size() > 0) {
					auto unit = subLayer->units.removeAndReturn(0);
					subLayer->removeChildComponent(unit);
					this->units.add(unit);
					this->addChildComponent(unit);
				}

				/** Delete SubLayer */
				delete subLayer;
				subLayer = nullptr;
			}

			/** Refresh */
			this->updateComponents();
			return;
		}

		void FlowGrid::gcLayer(FlowGrid* layer) {
			/** Layer Is Empty */
			if (layer->units.size() > 0) {
				jassertfalse;
				return;
			}

			/** Remove Unit */
			this->removeChildComponent(layer);
			this->units.removeObject(layer, true);
			layer = nullptr;

			/** Refresh */
			this->updateComponents();
			return;
		}

		void FlowGrid::resized() {
			juce::Array<juce::Component*> compList;
			compList.addArray(this->units);
			for (int i = 0; i < this->resizers.size(); i++) {
				compList.insert(i * 2 + 1, this->resizers.getUnchecked(i));
			}
			this->manager->layOutComponents(compList.getRawDataPointer(), compList.size(),
				0, 0, this->getWidth(), this->getHeight(), this->isVertical, true);
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
				auto unit = dynamic_cast<FlowGridableUnit*>(compList.getUnchecked(i));
				juce::Point<float> minSize;
				if (unit) {
					minSize = unit->getMinSize();
				}
				auto unitMinSize = this->isVertical ? minSize.getY() : minSize.getX();

				this->manager->setItemLayout(i,
					(i % 2 == 0) ? unitMinSize : resizerSize,
					(i % 2 == 0) ? -1.0 : resizerSize,
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
