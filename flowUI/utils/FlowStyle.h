#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils {
		class FlowStyle {
		public:
			FlowStyle() = default;

			static void setTitleHeight(double titleHeight);
			static void setTitleWidth(double titleWidth);
			static void setTitleBorderHeight(double titleBorderHeight);
			static void setTitleBorderWidth(double titleBorderWidth);
			static void setTitleSplitWidth(double titleSplitWidth);
			static void setTitleSplitHeight(double titleSplitHeight);
			static void setTitleSplitVLength(double titleSplitVLength);
			static void setTitleSplitHLength(double titleSplitHLength);
			static void setTitleTextHeight(double titleTextHeight);
			static void setTitleTextWidth(double titleTextWidth);
			static void setTitleTextPaddingWidth(double titleTextPaddingWidth);
			static void setTitleTextPaddingHeight(double titleTextPaddingHeight);
			static void setTitleBackgroundColor(juce::Colour backgroundColor);
			static void setTitleHighlightColor(juce::Colour highlightColor);
			static void setTitleBorderColor(juce::Colour borderColor);
			static void setTitleSplitColor(juce::Colour splitColor);
			static void setTitleTextColor(juce::Colour textColor);
			static void setTitleTextHighlightColor(juce::Colour textHighlightColor);

			static double getTitleHeight();
			static double getTitleWidth();
			static double getTitleBorderHeight();
			static double getTitleBorderWidth();
			static double getTitleSplitWidth();
			static double getTitleSplitHeight();
			static double getTitleSplitVLength();
			static double getTitleSplitHLength();
			static double getTitleTextHeight();
			static double getTitleTextWidth();
			static double getTitleTextPaddingWidth();
			static double getTitleTextPaddingHeight();
			static const juce::Colour getTitleBackgroundColor();
			static const juce::Colour getTitleHighlightColor();
			static const juce::Colour getTitleBorderColor();
			static const juce::Colour getTitleSplitColor();
			static const juce::Colour getTitleTextColor();
			static const juce::Colour getTitleTextHighlightColor();

		private:
			double titleHeight = 0;						/**< Container title bar height (vertical mode) */
			double titleWidth = 0;						/**< Container title bar width (horizontal mode) */
			double titleBorderHeight = 0;				/**< Container title bar top border height (vertical mode) */
			double titleBorderWidth = 0;				/**< Container title bar left border width (horizontal mode) */
			double titleSplitWidth = 0;					/**< Container title bar tab split line width (vertical mode) */
			double titleSplitHeight = 0;				/**< Container title bar tab split line height (horizontal mode) */
			double titleSplitVLength = 0;				/**< Container title bar tab split line length (vertical mode) */
			double titleSplitHLength = 0;				/**< Container title bar tab split line length (horizontal mode) */
			double titleTextHeight = 0;					/**< Container title bar tab title text height (vertical mode) */
			double titleTextWidth = 0;					/**< Container title bar tab title text width (horizontal mode) */
			double titleTextPaddingWidth = 0;			/**< Container title bar tab title text padding width (vertical mode) */
			double titleTextPaddingHeight = 0;			/**< Container title bar tab title text padding height (horizontal mode) */
			juce::Colour titleBackgroundColor;			/**< Container title bar tab fill color (not active) */
			juce::Colour titleHighlightColor;			/**< Container title bar tab fill color (active) */
			juce::Colour titleBorderColor;				/**< Container title bar border color */
			juce::Colour titleSplitColor;				/**< Container title bar tab split line color */
			juce::Colour titleTextColor;				/**< Container title bar tab title text color (not active) */
			juce::Colour titleTextHighlightColor;		/**< Container title bar tab title text color (active) */

			JUCE_DECLARE_SINGLETON(FlowStyle, false)
		};
	}
}
