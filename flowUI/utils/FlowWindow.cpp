#include "FlowWindow.h"
#include "FlowWindowHub.h"

namespace luce {
	namespace utils {
		FlowWindow::FlowWindow() 
			: DocumentWindow(
				juce::JUCEApplication::getInstance()->getApplicationName(),
				juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
					juce::ResizableWindow::ColourIds::backgroundColourId
				),
				juce::DocumentWindow::TitleBarButtons::allButtons
			) {
			this->setContentOwned(new FlowManager(this), false);
			this->setUsingNativeTitleBar(true);
			this->setResizable(true, false);
			this->centreWithSize(800, 600);

			FlowWindowHub::addWindow(this);

			this->getContentComponent()->setVisible(true);
			this->setVisible(true);
		}

		FlowWindow::~FlowWindow() {
			FlowWindowHub::closeWindow(this);

			if (FlowWindowHub::getSize() > 0) {
				auto window = FlowWindowHub::getWindow(0);
				if (window) {
					auto list = this->getManager()->getAllContainers();
					for (auto i : list) {
						if (this->getManager()->removeContainer(i)) {
							window->getManager()->addContainer(i);
							i->setWindow(window);
						}
					}
				}
			}
		}

		FlowManager* FlowWindow::getManager() const {
			return dynamic_cast<FlowManager*>(this->getContentComponent());
		}

		const juce::Rectangle<int> FlowWindow::getScreenSize() const {
			/** Get current screen */
			auto ptrScreen = juce::Desktop::getInstance().getDisplays()
				.getDisplayForRect(this->getScreenBounds());
			if (!ptrScreen) {
				return this->sizeTemp;
			}

			/** Hit temp */
			if (ptrScreen == this->ptrCurrentDisplay && ptrScreen->scale == this->currentScale) {
				return this->sizeTemp;
			}

			/** Base size */
			static juce::Rectangle<int> rect, rectTotal;
			rect = ptrScreen->userArea;
			rectTotal = ptrScreen->totalArea;
			static int width = 0, height = 0, widthT = 0, heightT = 0;
			width = rect.getWidth();
			height = rect.getHeight();
			widthT = rectTotal.getWidth();
			heightT = rectTotal.getHeight();

			/** Width is the longer side */
			if (width < height) {
				int temp = width;
				width = height;
				height = temp;
			}
			if (widthT < heightT) {
				int temp = widthT;
				widthT = heightT;
				heightT = temp;
			}

			/** Calculate aspect ratio */
			static double pNow = 9.0 / 16.0, pTotal = 9.0 / 16.0;
			pNow = static_cast<double>(height) / static_cast<double>(width);
			pTotal = static_cast<double>(heightT) / static_cast<double>(widthT);

			/** Scale to the standard */
			constexpr double proportion = 816.0 / 1536.0;
			constexpr double prop4Scale = 1080.0 / 1920.0;
			const double scaleM = 1.25 / 1920;
			const double scaleN = 1.0 / ((pTotal >= prop4Scale) ? widthT : (heightT / prop4Scale));
			const double scaleMN = scaleN / scaleM;

			/** Limit aspect ratio */
			if (pNow > proportion) {
				height = width * proportion;
			}
			else if (pNow < proportion) {
				width = height / proportion;
			}

			/** Result */
			juce::Rectangle<int> result;
			result.setWidth(width * scaleMN);
			result.setHeight(height * scaleMN);

			/** Record temp */
			this->sizeTemp = result;
			this->currentScale = ptrScreen->scale;
			this->ptrCurrentDisplay = ptrScreen;

			/** Return */
			return result;
		}

		void FlowWindow::openComponent(FlowComponent* comp, bool vertical) {
			this->getManager()->openComponent(comp, vertical);
		}

		void FlowWindow::closeComponent(FlowComponent* comp) {
			this->getManager()->closeComponent(comp);
		}

		bool FlowWindow::hasComponent(FlowComponent* comp) const {
			return this->getManager()->findComponent(comp);
		}

		void FlowWindow::autoLayout(const juce::var& grid, juce::Array<FlowComponent*> list) {
			this->getManager()->autoLayout(grid, list);
		}

		void FlowWindow::setOpenGL(bool openGLOn) {
			if (openGLOn) {
				this->openGLContext = std::make_unique<juce::OpenGLContext>();
				this->openGLContext->attachTo(*this);
			}
			else {
				this->openGLContext = nullptr;
			}
		}

		void FlowWindow::closeButtonPressed() {
			if (FlowWindowHub::getSize() <= 1) {
				juce::JUCEApplication::getInstance()->systemRequestedQuit();
			}
			else {
				delete this;
			}
		}

		void FlowWindow::moved() {
			/** Screen Temp */
			static auto screenTemp = juce::Desktop::getInstance().getDisplays()
				.getDisplayForRect(this->getScreenBounds());

			/** Current Screen */
			auto currentScreen = juce::Desktop::getInstance().getDisplays()
				.getDisplayForRect(this->getScreenBounds());

			/** Check Screen Changed */
			if (currentScreen != screenTemp) {
				screenTemp = currentScreen;

				/** Refresh Window */
				auto content = this->getContentComponent();
				if (content) {
					auto bounds = content->getBounds();
					content->setBounds(bounds.withSize(bounds.getWidth() * 2, bounds.getHeight() * 2));
					content->setBounds(bounds);
				}
			}
		}
	}
}
