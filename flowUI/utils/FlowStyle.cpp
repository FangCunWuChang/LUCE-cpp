#include "FlowStyle.h"

namespace luce {
	namespace utils {
		JUCE_IMPLEMENT_SINGLETON(FlowStyle)

		void FlowStyle::setTitleHeight(double titleHeight) {
			FlowStyle::getInstance()->titleHeight = titleHeight;
		}

		void FlowStyle::setTitleWidth(double titleWidth) {
			FlowStyle::getInstance()->titleWidth = titleWidth;
		}

		void FlowStyle::setTitleBorderHeight(double titleBorderHeight) {
			FlowStyle::getInstance()->titleBorderHeight = titleBorderHeight;
		}

		void FlowStyle::setTitleBorderWidth(double titleBorderWidth) {
			FlowStyle::getInstance()->titleBorderWidth = titleBorderWidth;
		}

		void FlowStyle::setTitleSplitWidth(double titleSplitWidth) {
			FlowStyle::getInstance()->titleSplitWidth = titleSplitWidth;
		}

		void FlowStyle::setTitleSplitHeight(double titleSplitHeight) {
			FlowStyle::getInstance()->titleSplitHeight = titleSplitHeight;
		}

		void FlowStyle::setTitleSplitVLength(double titleSplitVLength) {
			FlowStyle::getInstance()->titleSplitVLength = titleSplitVLength;
		}

		void FlowStyle::setTitleSplitHLength(double titleSplitHLength) {
			FlowStyle::getInstance()->titleSplitHLength = titleSplitHLength;
		}

		void FlowStyle::setTitleTextHeight(double titleTextHeight) {
			FlowStyle::getInstance()->titleTextHeight = titleTextHeight;
		}

		void FlowStyle::setTitleTextWidth(double titleTextWidth) {
			FlowStyle::getInstance()->titleTextWidth = titleTextWidth;
		}

		void FlowStyle::setTitleTextPaddingWidth(double titleTextPaddingWidth) {
			FlowStyle::getInstance()->titleTextPaddingWidth = titleTextPaddingWidth;
		}

		void FlowStyle::setTitleTextPaddingHeight(double titleTextPaddingHeight) {
			FlowStyle::getInstance()->titleTextPaddingHeight = titleTextPaddingHeight;
		}

		void FlowStyle::setTitleBackgroundColor(juce::Colour backgroundColor) {
			FlowStyle::getInstance()->titleBackgroundColor = backgroundColor;
		}

		void FlowStyle::setTitleHighlightColor(juce::Colour highlightColor) {
			FlowStyle::getInstance()->titleHighlightColor = highlightColor;
		}

		void FlowStyle::setTitleBorderColor(juce::Colour borderColor) {
			FlowStyle::getInstance()->titleBorderColor = borderColor;
		}

		void FlowStyle::setTitleSplitColor(juce::Colour splitColor) {
			FlowStyle::getInstance()->titleSplitColor = splitColor;
		}

		void FlowStyle::setTitleTextColor(juce::Colour textColor) {
			FlowStyle::getInstance()->titleTextColor = textColor;
		}

		void FlowStyle::setTitleTextHighlightColor(juce::Colour textHighlightColor) {
			FlowStyle::getInstance()->titleTextHighlightColor = textHighlightColor;
		}

		double FlowStyle::getTitleHeight() {
			return FlowStyle::getInstance()->titleHeight;
		}

		double FlowStyle::getTitleWidth() {
			return FlowStyle::getInstance()->titleWidth;
		}

		double FlowStyle::getTitleBorderHeight() {
			return FlowStyle::getInstance()->titleBorderHeight;
		}

		double FlowStyle::getTitleBorderWidth() {
			return FlowStyle::getInstance()->titleBorderWidth;
		}

		double FlowStyle::getTitleSplitWidth() {
			return FlowStyle::getInstance()->titleSplitWidth;
		}

		double FlowStyle::getTitleSplitHeight() {
			return FlowStyle::getInstance()->titleSplitHeight;
		}

		double FlowStyle::getTitleSplitVLength() {
			return FlowStyle::getInstance()->titleSplitVLength;
		}

		double FlowStyle::getTitleSplitHLength() {
			return FlowStyle::getInstance()->titleSplitHLength;
		}

		double FlowStyle::getTitleTextHeight() {
			return FlowStyle::getInstance()->titleTextHeight;
		}

		double FlowStyle::getTitleTextWidth() {
			return FlowStyle::getInstance()->titleTextWidth;
		}

		double FlowStyle::getTitleTextPaddingWidth() {
			return FlowStyle::getInstance()->titleTextPaddingWidth;
		}

		double FlowStyle::getTitleTextPaddingHeight() {
			return FlowStyle::getInstance()->titleTextPaddingHeight;
		}

		const juce::Colour FlowStyle::getTitleBackgroundColor() {
			return FlowStyle::getInstance()->titleBackgroundColor;
		}

		const juce::Colour FlowStyle::getTitleHighlightColor() {
			return FlowStyle::getInstance()->titleHighlightColor;
		}

		const juce::Colour FlowStyle::getTitleBorderColor() {
			return FlowStyle::getInstance()->titleBorderColor;
		}

		const juce::Colour FlowStyle::getTitleSplitColor() {
			return FlowStyle::getInstance()->titleSplitColor;
		}

		const juce::Colour FlowStyle::getTitleTextColor() {
			return FlowStyle::getInstance()->titleTextColor;
		}

		const juce::Colour FlowStyle::getTitleTextHighlightColor() {
			return FlowStyle::getInstance()->titleTextHighlightColor;
		}
	}
}
