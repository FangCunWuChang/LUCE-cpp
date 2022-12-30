#include "FlowStyle.h"

namespace luce {
	namespace utils {
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

		void FlowStyle::setButtonWidth(float buttonWidth) {
			FlowStyle::getInstance()->buttonWidth = buttonWidth;
		}

		void FlowStyle::setButtonHeight(float buttonHeight) {
			FlowStyle::getInstance()->buttonHeight = buttonHeight;
		}

		void FlowStyle::setButtonIconWidth(float buttonIconWidth) {
			FlowStyle::getInstance()->buttonIconWidth = buttonIconWidth;
		}

		void FlowStyle::setButtonIconHeight(float buttonIconHeight) {
			FlowStyle::getInstance()->buttonIconHeight = buttonIconHeight;
		}

		void FlowStyle::setButtonSplitWidth(float buttonSplitWidth) {
			FlowStyle::getInstance()->buttonSplitWidth = buttonSplitWidth;
		}

		void FlowStyle::setButtonSplitHeight(float buttonSplitHeight) {
			FlowStyle::getInstance()->buttonSplitHeight = buttonSplitHeight;
		}

		void FlowStyle::setButtonPaddingWidth(float buttonPaddingWidth) {
			FlowStyle::getInstance()->buttonPaddingWidth = buttonPaddingWidth;
		}

		void FlowStyle::setButtonPaddingHeight(float buttonPaddingHeight) {
			FlowStyle::getInstance()->buttonPaddingHeight = buttonPaddingHeight;
		}

		void FlowStyle::setButtonCornerSize(float buttonCornerSize) {
			FlowStyle::getInstance()->buttonCornerSize = buttonCornerSize;
		}

		void FlowStyle::setButtonBorderSize(float buttonBorderSize) {
			FlowStyle::getInstance()->buttonBorderSize = buttonBorderSize;
		}

		void FlowStyle::setButtonIconColor(juce::Colour buttonIconColor) {
			FlowStyle::getInstance()->buttonIconColor = buttonIconColor;
		}

		void FlowStyle::setButtonIconBackgroundColor(juce::Colour buttonIconBackgroundColor) {
			FlowStyle::getInstance()->buttonIconBackgroundColor = buttonIconBackgroundColor;
		}

		void FlowStyle::setAdsorbColor(juce::Colour adsorbColor) {
			FlowStyle::getInstance()->adsorbAreaColor = adsorbColor;
		}

		float FlowStyle::getButtonWidth() {
			return FlowStyle::getInstance()->buttonWidth;
		}

		float FlowStyle::getButtonHeight() {
			return FlowStyle::getInstance()->buttonHeight;
		}

		float FlowStyle::getButtonIconWidth() {
			return FlowStyle::getInstance()->buttonIconWidth;
		}

		float FlowStyle::getButtonIconHeight() {
			return FlowStyle::getInstance()->buttonIconHeight;
		}

		float FlowStyle::getButtonSplitWidth() {
			return FlowStyle::getInstance()->buttonSplitWidth;
		}

		float FlowStyle::getButtonSplitHeight() {
			return FlowStyle::getInstance()->buttonSplitHeight;
		}

		float FlowStyle::getButtonPaddingWidth() {
			return FlowStyle::getInstance()->buttonPaddingWidth;
		}

		float FlowStyle::getButtonPaddingHeight() {
			return FlowStyle::getInstance()->buttonPaddingHeight;
		}

		float FlowStyle::getButtonCornerSize() {
			return FlowStyle::getInstance()->buttonCornerSize;
		}

		float FlowStyle::getButtonBorderSize() {
			return FlowStyle::getInstance()->buttonBorderSize;
		}

		const juce::Colour FlowStyle::getButtonIconColor() {
			return FlowStyle::getInstance()->buttonIconColor;
		}

		const juce::Colour FlowStyle::getButtonIconBackgroundColor() {
			return FlowStyle::getInstance()->buttonIconBackgroundColor;
		}

		const juce::Colour FlowStyle::getAdsorbColor() {
			return FlowStyle::getInstance()->adsorbAreaColor;
		}

		void FlowStyle::setButtonLeftIcon(const juce::String& buttonLeftIcon) {
			FlowStyle::getInstance()->buttonLeftIcon = buttonLeftIcon;
		}

		void FlowStyle::setButtonRightIcon(const juce::String& buttonRightIcon) {
			FlowStyle::getInstance()->buttonRightIcon = buttonRightIcon;
		}

		void FlowStyle::setButtonTopIcon(const juce::String& buttonTopIcon) {
			FlowStyle::getInstance()->buttonTopIcon = buttonTopIcon;
		}

		void FlowStyle::setButtonBottomIcon(const juce::String& buttonBottomIcon) {
			FlowStyle::getInstance()->buttonBottomIcon = buttonBottomIcon;
		}

		void FlowStyle::setButtonAdsorbCenterIcon(const juce::String& buttonAdsorbCenterIcon) {
			FlowStyle::getInstance()->buttonAdsorbCenterIcon = buttonAdsorbCenterIcon;
		}

		void FlowStyle::setButtonAdsorbLeftIcon(const juce::String& buttonAdsorbLeftIcon) {
			FlowStyle::getInstance()->buttonAdsorbLeftIcon = buttonAdsorbLeftIcon;
		}

		void FlowStyle::setButtonAdsorbRightIcon(const juce::String& buttonAdsorbRightIcon) {
			FlowStyle::getInstance()->buttonAdsorbRightIcon = buttonAdsorbRightIcon;
		}

		void FlowStyle::setButtonAdsorbTopIcon(const juce::String& buttonAdsorbTopIcon) {
			FlowStyle::getInstance()->buttonAdsorbTopIcon = buttonAdsorbTopIcon;
		}

		void FlowStyle::setButtonAdsorbBottomIcon(const juce::String& buttonAdsorbBottomIcon) {
			FlowStyle::getInstance()->buttonAdsorbBottomIcon = buttonAdsorbBottomIcon;
		}

		const juce::String FlowStyle::getButtonLeftIcon() {
			return FlowStyle::getInstance()->buttonLeftIcon;
		}

		const juce::String FlowStyle::getButtonRightIcon() {
			return FlowStyle::getInstance()->buttonRightIcon;
		}

		const juce::String FlowStyle::getButtonTopIcon() {
			return FlowStyle::getInstance()->buttonTopIcon;
		}

		const juce::String FlowStyle::getButtonBottomIcon() {
			return FlowStyle::getInstance()->buttonBottomIcon;
		}

		const juce::String FlowStyle::getButtonAdsorbCenterIcon() {
			return FlowStyle::getInstance()->buttonAdsorbCenterIcon;
		}

		const juce::String FlowStyle::getButtonAdsorbLeftIcon() {
			return FlowStyle::getInstance()->buttonAdsorbLeftIcon;
		}

		const juce::String FlowStyle::getButtonAdsorbRightIcon() {
			return FlowStyle::getInstance()->buttonAdsorbRightIcon;
		}

		const juce::String FlowStyle::getButtonAdsorbTopIcon() {
			return FlowStyle::getInstance()->buttonAdsorbTopIcon;
		}

		const juce::String FlowStyle::getButtonAdsorbBottomIcon() {
			return FlowStyle::getInstance()->buttonAdsorbBottomIcon;
		}

		FlowStyle* FlowStyle::getInstance() {
			return FlowStyle::instance;
		}

		FlowStyle* FlowStyle::instance = new FlowStyle();
	}
}
