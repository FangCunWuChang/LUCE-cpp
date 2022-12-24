#include "QuickComponent.h"

namespace luce {
	namespace utils {
		using juce::Graphics;

		QuickComponent::QuickComponent(const juce::String& name)
			: Component(name) {}

		void QuickComponent::paint(juce::Graphics& g) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::paint(g);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());
			LUCE_PUSH_DATA(LUCE_GET_STATE(), -1);
			
			if (!lua_istable(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::paint(g);
				return;
			}

			lua_getfield(LUCE_GET_STATE(), -1, "QuickComponent");
			if (!lua_istable(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 3);
				this->juce::Component::paint(g);
				return;
			}
			
			lua_getfield(LUCE_GET_STATE(), -1, "paint");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 4);
				this->juce::Component::paint(g);
				return;
			}
			
			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), Graphics, pg, g);
			lua_pcall(LUCE_GET_STATE(), 2, 0, 0);
			
			lua_pop(LUCE_GET_STATE(), 3);
		}

		void QuickComponent::paintOverChildren(juce::Graphics& g) {

		}

		void QuickComponent::mouseMove(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseEnter(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseExit(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseDown(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseDrag(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseUp(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseDoubleClick(const juce::MouseEvent& event) {

		}

		void QuickComponent::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) {

		}

		void QuickComponent::resized() {

		}

		void QuickComponent::moved() {

		}

		const juce::Rectangle<int> QuickComponent::getScreenSize() const {
			/** Temp */
			static const juce::Displays::Display* ptrCurrentDisplay = nullptr;
			static juce::Rectangle<int> sizeTemp;
			static double currentScale = 1.;

			/** Get current screen */
			auto ptrScreen = juce::Desktop::getInstance().getDisplays()
				.getDisplayForRect(this->getScreenBounds());
			if (!ptrScreen) {
				return sizeTemp;
			}

			/** Hit temp */
			if (ptrScreen == ptrCurrentDisplay && ptrScreen->scale == currentScale) {
				return sizeTemp;
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
			sizeTemp = result;
			currentScale = ptrScreen->scale;
			ptrCurrentDisplay = ptrScreen;

			/** Return */
			return result;
		}
	}
}
