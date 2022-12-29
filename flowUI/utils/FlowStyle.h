#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowStyle {
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
			static void setUnitMaximumHeight(float unitMaximumHeight);
			static void setUnitMaximumWidth(float unitMaximumWidth);
			static void setResizerColor(juce::Colour resizerColor);

			static float getResizerHeight();
			static float getResizerWidth();
			static float getUnitMinimumHeight();
			static float getUnitMinimumWidth();
			static float getUnitMaximumHeight();
			static float getUnitMaximumWidth();
			static const juce::Colour getResizerColor();



			static void setContainerDefaultHeight(float containerDefaultHeight);
			static void setContainerDefaultWidth(float containerDefaultWidth);

			static float getContainerDefaultHeight();
			static float getContainerDefaultWidth();



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
			float titleHeight = 0.05;						/**< Container title bar height (vertical mode) */
			float titleWidth = 0.05;						/**< Container title bar width (horizontal mode) */
			float titleBorderHeight = 0.005;				/**< Container title bar top border height (vertical mode) */
			float titleBorderWidth = 0.005;					/**< Container title bar left border width (horizontal mode) */
			float titleSplitWidth = 0.0025;					/**< Container title bar tab split line width (vertical mode) */
			float titleSplitHeight = 0.0025;				/**< Container title bar tab split line height (horizontal mode) */
			float titleSplitVLength = 0.04;					/**< Container title bar tab split line length (vertical mode) */
			float titleSplitHLength = 0.04;					/**< Container title bar tab split line length (horizontal mode) */
			float titleTextHeight = 0.25;					/**< Container title bar tab title text height (vertical mode) */
			float titleTextWidth = 0.25;					/**< Container title bar tab title text width (horizontal mode) */
			float titleTextPaddingWidth = 0.01;				/**< Container title bar tab title text padding width (vertical mode) */
			float titleTextPaddingHeight = 0.01;			/**< Container title bar tab title text padding height (horizontal mode) */
			juce::Colour titleBackgroundColor;				/**< Container title bar tab fill color (not active) */
			juce::Colour titleHighlightColor;				/**< Container title bar tab fill color (active) */
			juce::Colour titleBorderColor;					/**< Container title bar border color */
			juce::Colour titleSplitColor;					/**< Container title bar tab split line color */
			juce::Colour titleTextColor;					/**< Container title bar tab title text color (not active) */
			juce::Colour titleTextHighlightColor;			/**< Container title bar tab title text color (active) */



			float resizerHeight = 0.01;						/**< Grid resizer bar height (vertical mode) */
			float resizerWidth = 0.01;						/**< Grid resizer bar width (horizontal mode) */
			float unitMinimumHeight = 0.1;					/**< Grid unit minimum height (vertical mode) */
			float unitMinimumWidth = 0.1;					/**< Grid unit minimum width (horizontal mode) */
			float unitMaximumHeight = 1.0;					/**< Grid unit maximum height (vertical mode) */
			float unitMaximumWidth = 1.0;					/**< Grid unit maximum width (horizontal mode) */
			juce::Colour resizerColor;						/**< Grid resizer bar color */



			float containerDefaultHeight = 0.5;				/**< Default height of flow container */
			float containerDefaultWidth = 0.5;				/**< Default width of flow container */



			float buttonWidth = 0.025;						/**< Width of adsorb button */
			float buttonHeight = 0.025;						/**< Height of adsorb button */
			float buttonIconWidth = 0.02;					/**< Width of adsorb button icon */
			float buttonIconHeight = 0.02;					/**< Height of adsorb button icon */
			float buttonSplitWidth = 0.005;					/**< Width of adsorb button split */
			float buttonSplitHeight = 0.005;				/**< Height of adsorb button split */
			float buttonPaddingWidth = 0.01;				/**< Horizontal distance of the adsorb button from border */
			float buttonPaddingHeight = 0.01;				/**< Vertical distance of the adsorb button from border */
			float buttonCornerSize = 0.01;					/**< Corner width of adsorb button */
			float buttonBorderSize = 0.0025;				/**< Border line width of adsorb button */
			juce::Colour buttonIconColor;					/**< Adsorb button icon color */
			juce::Colour buttonIconBackgroundColor;			/**< Adsorb button icon background color */
			juce::Colour adsorbAreaColor;					/**< Container adsorb area color */



			juce::String buttonLeftIcon;					/**< Outside left adsorb button icon */
			juce::String buttonRightIcon;					/**< Outside right adsorb button icon */
			juce::String buttonTopIcon;						/**< Outside top adsorb button icon */
			juce::String buttonBottomIcon;					/**< Outside bottom adsorb button icon */
			juce::String buttonAdsorbCenterIcon;			/**< Center adsorb button icon */
			juce::String buttonAdsorbLeftIcon;				/**< Left adsorb button icon */
			juce::String buttonAdsorbRightIcon;				/**< Right adsorb button icon */
			juce::String buttonAdsorbTopIcon;				/**< Top adsorb button icon */
			juce::String buttonAdsorbBottomIcon;			/**< Bottom adsorb button icon */

			JUCE_DECLARE_SINGLETON(FlowStyle, false)
		};
	}
}
