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



			float containerDefaultHeight = 0.5;			/**< Default height of flow container */
			float containerDefaultWidth = 0.5;			/**< Default width of flow container */

			JUCE_DECLARE_SINGLETON(FlowStyle, false)
		};
	}
}
