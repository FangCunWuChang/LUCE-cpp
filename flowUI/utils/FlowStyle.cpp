#include "FlowStyle.h"

namespace luce {
	namespace utils {
		JUCE_IMPLEMENT_SINGLETON(FlowStyle)

		void FlowStyle::setTitleHeight(float titleHeight) {
			FlowStyle::getInstance()->titleHeight = titleHeight;
		}

		void FlowStyle::setTitleWidth(float titleWidth) {
			FlowStyle::getInstance()->titleWidth = titleWidth;
		}

		void FlowStyle::setTitleBorderHeight(float titleBorderHeight) {
			FlowStyle::getInstance()->titleBorderHeight = titleBorderHeight;
		}

		void FlowStyle::setTitleBorderWidth(float titleBorderWidth) {
			FlowStyle::getInstance()->titleBorderWidth = titleBorderWidth;
		}

		void FlowStyle::setTitleSplitWidth(float titleSplitWidth) {
			FlowStyle::getInstance()->titleSplitWidth = titleSplitWidth;
		}

		void FlowStyle::setTitleSplitHeight(float titleSplitHeight) {
			FlowStyle::getInstance()->titleSplitHeight = titleSplitHeight;
		}

		void FlowStyle::setTitleSplitVLength(float titleSplitVLength) {
			FlowStyle::getInstance()->titleSplitVLength = titleSplitVLength;
		}

		void FlowStyle::setTitleSplitHLength(float titleSplitHLength) {
			FlowStyle::getInstance()->titleSplitHLength = titleSplitHLength;
		}

		void FlowStyle::setTitleTextHeight(float titleTextHeight) {
			FlowStyle::getInstance()->titleTextHeight = titleTextHeight;
		}

		void FlowStyle::setTitleTextWidth(float titleTextWidth) {
			FlowStyle::getInstance()->titleTextWidth = titleTextWidth;
		}

		void FlowStyle::setTitleTextPaddingWidth(float titleTextPaddingWidth) {
			FlowStyle::getInstance()->titleTextPaddingWidth = titleTextPaddingWidth;
		}

		void FlowStyle::setTitleTextPaddingHeight(float titleTextPaddingHeight) {
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

		float FlowStyle::getTitleHeight() {
			return FlowStyle::getInstance()->titleHeight;
		}

		float FlowStyle::getTitleWidth() {
			return FlowStyle::getInstance()->titleWidth;
		}

		float FlowStyle::getTitleBorderHeight() {
			return FlowStyle::getInstance()->titleBorderHeight;
		}

		float FlowStyle::getTitleBorderWidth() {
			return FlowStyle::getInstance()->titleBorderWidth;
		}

		float FlowStyle::getTitleSplitWidth() {
			return FlowStyle::getInstance()->titleSplitWidth;
		}

		float FlowStyle::getTitleSplitHeight() {
			return FlowStyle::getInstance()->titleSplitHeight;
		}

		float FlowStyle::getTitleSplitVLength() {
			return FlowStyle::getInstance()->titleSplitVLength;
		}

		float FlowStyle::getTitleSplitHLength() {
			return FlowStyle::getInstance()->titleSplitHLength;
		}

		float FlowStyle::getTitleTextHeight() {
			return FlowStyle::getInstance()->titleTextHeight;
		}

		float FlowStyle::getTitleTextWidth() {
			return FlowStyle::getInstance()->titleTextWidth;
		}

		float FlowStyle::getTitleTextPaddingWidth() {
			return FlowStyle::getInstance()->titleTextPaddingWidth;
		}

		float FlowStyle::getTitleTextPaddingHeight() {
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

		void FlowStyle::setResizerHeight(float resizerHeight) {
			FlowStyle::getInstance()->resizerHeight = resizerHeight;
		}

		void FlowStyle::setResizerWidth(float resizerWidth) {
			FlowStyle::getInstance()->resizerWidth = resizerWidth;
		}

		void FlowStyle::setUnitMinimumHeight(float unitMinimumHeight) {
			FlowStyle::getInstance()->unitMinimumHeight = unitMinimumHeight;
		}

		void FlowStyle::setUnitMinimumWidth(float unitMinimumWidth) {
			FlowStyle::getInstance()->unitMinimumWidth = unitMinimumWidth;
		}

		void FlowStyle::setUnitMaximumHeight(float unitMaximumHeight) {
			FlowStyle::getInstance()->unitMaximumHeight = unitMaximumHeight;
		}

		void FlowStyle::setUnitMaximumWidth(float unitMaximumWidth) {
			FlowStyle::getInstance()->unitMaximumWidth = unitMaximumWidth;
		}

		void FlowStyle::setResizerColor(juce::Colour resizerColor) {
			FlowStyle::getInstance()->resizerColor = resizerColor;
		}

		float FlowStyle::getResizerHeight() {
			return FlowStyle::getInstance()->resizerHeight;
		}

		float FlowStyle::getResizerWidth() {
			return FlowStyle::getInstance()->resizerWidth;
		}

		float FlowStyle::getUnitMinimumHeight() {
			return FlowStyle::getInstance()->unitMinimumHeight;
		}

		float FlowStyle::getUnitMinimumWidth() {
			return FlowStyle::getInstance()->unitMinimumWidth;
		}

		float FlowStyle::getUnitMaximumHeight() {
			return FlowStyle::getInstance()->unitMaximumHeight;
		}

		float FlowStyle::getUnitMaximumWidth() {
			return FlowStyle::getInstance()->unitMaximumWidth;
		}

		const juce::Colour FlowStyle::getResizerColor() {
			return FlowStyle::getInstance()->resizerColor;
		}

		void FlowStyle::setContainerDefaultHeight(float containerDefaultHeight) {
			FlowStyle::getInstance()->containerDefaultHeight = containerDefaultHeight;
		}

		void FlowStyle::setContainerDefaultWidth(float containerDefaultWidth) {
			FlowStyle::getInstance()->containerDefaultWidth = containerDefaultWidth;
		}

		float FlowStyle::getContainerDefaultHeight() {
			return FlowStyle::getInstance()->containerDefaultHeight;
		}

		float FlowStyle::getContainerDefaultWidth() {
			return FlowStyle::getInstance()->containerDefaultWidth;
		}
	}
}
