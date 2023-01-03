#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowStyle final : public juce::DeletedAtShutdown{
		public:
			FlowStyle() = default;

			static void setTitleHeight(float titleHeight);
			static void setTitleWidth(float titleWidth);
			static void setTitleBorderHeight(float titleBorderHeight);
			static void setTitleBorderWidth(float titleBorderWidth);
			static void setTitleSplitWidth(float titleSplitWidth);
			static void setTitleSplitHeight(float titleSplitHeight);
			static void setTitleSplitVLength(float titleSplitVLength);
			static void setTitleSplitHLength(float titleSplitHLength);
			static void setTitleTextHeight(float titleTextHeight);
			static void setTitleTextWidth(float titleTextWidth);
			static void setTitleTextPaddingWidth(float titleTextPaddingWidth);
			static void setTitleTextPaddingHeight(float titleTextPaddingHeight);
			static void setTitleBackgroundColor(juce::Colour backgroundColor);
			static void setTitleHighlightColor(juce::Colour highlightColor);
			static void setTitleBorderColor(juce::Colour borderColor);
			static void setTitleSplitColor(juce::Colour splitColor);
			static void setTitleTextColor(juce::Colour textColor);
			static void setTitleTextHighlightColor(juce::Colour textHighlightColor);

			static float getTitleHeight();
			static float getTitleWidth();
			static float getTitleBorderHeight();
			static float getTitleBorderWidth();
			static float getTitleSplitWidth();
			static float getTitleSplitHeight();
			static float getTitleSplitVLength();
			static float getTitleSplitHLength();
			static float getTitleTextHeight();
			static float getTitleTextWidth();
			static float getTitleTextPaddingWidth();
			static float getTitleTextPaddingHeight();
			static const juce::Colour getTitleBackgroundColor();
			static const juce::Colour getTitleHighlightColor();
			static const juce::Colour getTitleBorderColor();
			static const juce::Colour getTitleSplitColor();
			static const juce::Colour getTitleTextColor();
			static const juce::Colour getTitleTextHighlightColor();



			static void setResizerHeight(float resizerHeight);
			static void setResizerWidth(float resizerWidth);
			static void setUnitMinimumHeight(float unitMinimumHeight);
			static void setUnitMinimumWidth(float unitMinimumWidth);
			static void setResizerColor(juce::Colour resizerColor);

			static float getResizerHeight();
			static float getResizerWidth();
			static float getUnitMinimumHeight();
			static float getUnitMinimumWidth();
			static const juce::Colour getResizerColor();



			static void setContainerResizerHeight(float containerResizerHeight);
			static void setContainerResizerWidth(float containerResizerWidth);
			static void setContainerDefaultHeight(float containerDefaultHeight);
			static void setContainerDefaultWidth(float containerDefaultWidth);
			static void setContainerBorderSize(float containerBorderSize);
			static void setContainerBorderColor(juce::Colour containerBorderColor);

			static float getContainerResizerHeight();
			static float getContainerResizerWidth();
			static float getContainerDefaultHeight();
			static float getContainerDefaultWidth();
			static float getContainerBorderSize();
			static juce::Colour getContainerBorderColor();



			static void setButtonWidth(float buttonWidth);
			static void setButtonHeight(float buttonHeight);
			static void setButtonIconWidth(float buttonIconWidth);
			static void setButtonIconHeight(float buttonIconHeight);
			static void setButtonSplitWidth(float buttonSplitWidth);
			static void setButtonSplitHeight(float buttonSplitHeight);
			static void setButtonPaddingWidth(float buttonPaddingWidth);
			static void setButtonPaddingHeight(float buttonPaddingHeight);
			static void setButtonCornerSize(float buttonCornerSize);
			static void setButtonBorderSize(float buttonBorderSize);
			static void setButtonIconColor(juce::Colour buttonIconColor);
			static void setButtonIconBackgroundColor(juce::Colour buttonIconBackgroundColor);
			static void setAdsorbColor(juce::Colour adsorbColor);

			static float getButtonWidth();
			static float getButtonHeight();
			static float getButtonIconWidth();
			static float getButtonIconHeight();
			static float getButtonSplitWidth();
			static float getButtonSplitHeight();
			static float getButtonPaddingWidth();
			static float getButtonPaddingHeight();
			static float getButtonCornerSize();
			static float getButtonBorderSize();
			static const juce::Colour getButtonIconColor();
			static const juce::Colour getButtonIconBackgroundColor();
			static const juce::Colour getAdsorbColor();



			static void setButtonLeftIcon(const juce::String& buttonLeftIcon);
			static void setButtonRightIcon(const juce::String& buttonRightIcon);
			static void setButtonTopIcon(const juce::String& buttonTopIcon);
			static void setButtonBottomIcon(const juce::String& buttonBottomIcon);
			static void setButtonAdsorbCenterIcon(const juce::String& buttonAdsorbCenterIcon);
			static void setButtonAdsorbLeftIcon(const juce::String& buttonAdsorbLeftIcon);
			static void setButtonAdsorbRightIcon(const juce::String& buttonAdsorbRightIcon);
			static void setButtonAdsorbTopIcon(const juce::String& buttonAdsorbTopIcon);
			static void setButtonAdsorbBottomIcon(const juce::String& buttonAdsorbBottomIcon);

			static const juce::String getButtonLeftIcon();
			static const juce::String getButtonRightIcon();
			static const juce::String getButtonTopIcon();
			static const juce::String getButtonBottomIcon();
			static const juce::String getButtonAdsorbCenterIcon();
			static const juce::String getButtonAdsorbLeftIcon();
			static const juce::String getButtonAdsorbRightIcon();
			static const juce::String getButtonAdsorbTopIcon();
			static const juce::String getButtonAdsorbBottomIcon();


		private:
			float titleHeight = 0.024;						/**< Container title bar height (vertical mode) */
			float titleWidth = 0.012;						/**< Container title bar width (horizontal mode) */
			float titleBorderHeight = 0.004;				/**< Container title bar top border height (vertical mode) */
			float titleBorderWidth = 0.0024;				/**< Container title bar left border width (horizontal mode) */
			float titleSplitWidth = 0.0005;					/**< Container title bar tab split line width (vertical mode) */
			float titleSplitHeight = 0.00065;				/**< Container title bar tab split line height (horizontal mode) */
			float titleSplitVLength = 0.0125;				/**< Container title bar tab split line length (vertical mode) */
			float titleSplitHLength = 0.00625;				/**< Container title bar tab split line length (horizontal mode) */
			float titleTextHeight = 0.016;					/**< Container title bar tab title text height (vertical mode) */
			float titleTextWidth = 0.008;					/**< Container title bar tab title text width (horizontal mode) */
			float titleTextPaddingWidth = 0.008;			/**< Container title bar tab title text padding width (vertical mode) */
			float titleTextPaddingHeight = 0.012;			/**< Container title bar tab title text padding height (horizontal mode) */
			juce::Colour titleBackgroundColor
				= juce::Colours::darkgrey;					/**< Container title bar tab fill color (not active) */
			juce::Colour titleHighlightColor
				= juce::Colours::grey;						/**< Container title bar tab fill color (active) */
			juce::Colour titleBorderColor
				= juce::Colours::rebeccapurple;				/**< Container title bar border color */
			juce::Colour titleSplitColor
				= juce::Colours::lightgrey;					/**< Container title bar tab split line color */
			juce::Colour titleTextColor
				= juce::Colours::white;						/**< Container title bar tab title text color (not active) */
			juce::Colour titleTextHighlightColor
				= juce::Colours::white;						/**< Container title bar tab title text color (active) */



			float resizerHeight = 0.0036;					/**< Grid resizer bar height (vertical mode) */
			float resizerWidth = 0.0021;					/**< Grid resizer bar width (horizontal mode) */
			float unitMinimumHeight = 0.05;					/**< Grid unit minimum height (vertical mode) */
			float unitMinimumWidth = 0.05;					/**< Grid unit minimum width (horizontal mode) */
			juce::Colour resizerColor
				= juce::Colours::black;						/**< Grid resizer bar color */



			float containerResizerHeight = 0.006;			/**< Height of the resizer of the free container */
			float containerResizerWidth = 0.0035;			/**< Width of the resizer of the free container */
			float containerDefaultHeight = 0.5;				/**< Default height of flow container */
			float containerDefaultWidth = 0.5;				/**< Default width of flow container */
			float containerBorderSize = 0.0008;				/**< Border line width of container */
			juce::Colour containerBorderColor
				= juce::Colours::darkgrey;					/**< Container border line color */



			float buttonWidth = 0.032;						/**< Width of adsorb button */
			float buttonHeight = 0.06;						/**< Height of adsorb button */
			float buttonIconWidth = 0.0192;					/**< Width of adsorb button icon */
			float buttonIconHeight = 0.036;					/**< Height of adsorb button icon */
			float buttonSplitWidth = 0.004;					/**< Width of adsorb button split */
			float buttonSplitHeight = 0.0075;				/**< Height of adsorb button split */
			float buttonPaddingWidth = 0.005;				/**< Horizontal distance of the adsorb button from border */
			float buttonPaddingHeight = 0.008;				/**< Vertical distance of the adsorb button from border */
			float buttonCornerSize = 0.004;					/**< Corner width of adsorb button */
			float buttonBorderSize = 0.0008;				/**< Border line width of adsorb button */
			juce::Colour buttonIconColor
				= juce::Colours::white;						/**< Adsorb button icon color */
			juce::Colour buttonIconBackgroundColor
				= juce::Colours::dimgrey;					/**< Adsorb button icon background color */
			juce::Colour adsorbAreaColor
				= juce::Colours::blue.withAlpha(.5f);		/**< Container adsorb area color */



			juce::String buttonLeftIcon;					/**< Outside left adsorb button icon */
			juce::String buttonRightIcon;					/**< Outside right adsorb button icon */
			juce::String buttonTopIcon;						/**< Outside top adsorb button icon */
			juce::String buttonBottomIcon;					/**< Outside bottom adsorb button icon */
			juce::String buttonAdsorbCenterIcon;			/**< Center adsorb button icon */
			juce::String buttonAdsorbLeftIcon;				/**< Left adsorb button icon */
			juce::String buttonAdsorbRightIcon;				/**< Right adsorb button icon */
			juce::String buttonAdsorbTopIcon;				/**< Top adsorb button icon */
			juce::String buttonAdsorbBottomIcon;			/**< Bottom adsorb button icon */

			private:
				static FlowStyle* getInstance();
				static FlowStyle* instance;
		};
	}
}
