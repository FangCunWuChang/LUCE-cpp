#include "../Defs.h"
#include "utils/FlowStyle.h"

namespace luce {
	using utils::FlowStyle;
	using juce::Colour;

	LUCE_METHOD(setTitleHeight) {
		FlowStyle::setTitleHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleWidth) {
		FlowStyle::setTitleWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleBorderHeight) {
		FlowStyle::setTitleBorderHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleBorderWidth) {
		FlowStyle::setTitleBorderWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleSplitWidth) {
		FlowStyle::setTitleSplitWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleSplitHeight) {
		FlowStyle::setTitleSplitHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleSplitVLength) {
		FlowStyle::setTitleSplitVLength(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleSplitHLength) {
		FlowStyle::setTitleSplitHLength(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleTextHeight) {
		FlowStyle::setTitleTextHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleTextWidth) {
		FlowStyle::setTitleTextWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleTextPaddingWidth) {
		FlowStyle::setTitleTextPaddingWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleTextPaddingHeight) {
		FlowStyle::setTitleTextPaddingHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setTitleBackgroundColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setTitleBackgroundColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setTitleHighlightColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setTitleHighlightColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setTitleBorderColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setTitleBorderColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setTitleSplitColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setTitleSplitColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setTitleTextColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setTitleTextColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setTitleTextHighlightColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setTitleTextHighlightColor(*pColor);
		return 0;
	}


	LUCE_METHOD(getTitleHeight) {
		lua_pushnumber(L, FlowStyle::getTitleHeight());
		return 1;
	}

	LUCE_METHOD(getTitleWidth) {
		lua_pushnumber(L, FlowStyle::getTitleWidth());
		return 1;
	}

	LUCE_METHOD(getTitleBorderHeight) {
		lua_pushnumber(L, FlowStyle::getTitleBorderHeight());
		return 1;
	}

	LUCE_METHOD(getTitleBorderWidth) {
		lua_pushnumber(L, FlowStyle::getTitleBorderWidth());
		return 1;
	}

	LUCE_METHOD(getTitleSplitWidth) {
		lua_pushnumber(L, FlowStyle::getTitleSplitWidth());
		return 1;
	}

	LUCE_METHOD(getTitleSplitHeight) {
		lua_pushnumber(L, FlowStyle::getTitleSplitHeight());
		return 1;
	}

	LUCE_METHOD(getTitleSplitVLength) {
		lua_pushnumber(L, FlowStyle::getTitleSplitVLength());
		return 1;
	}

	LUCE_METHOD(getTitleSplitHLength) {
		lua_pushnumber(L, FlowStyle::getTitleSplitHLength());
		return 1;
	}

	LUCE_METHOD(getTitleTextHeight) {
		lua_pushnumber(L, FlowStyle::getTitleTextHeight());
		return 1;
	}

	LUCE_METHOD(getTitleTextWidth) {
		lua_pushnumber(L, FlowStyle::getTitleTextWidth());
		return 1;
	}

	LUCE_METHOD(getTitleTextPaddingWidth) {
		lua_pushnumber(L, FlowStyle::getTitleTextPaddingWidth());
		return 1;
	}

	LUCE_METHOD(getTitleTextPaddingHeight) {
		lua_pushnumber(L, FlowStyle::getTitleTextPaddingHeight());
		return 1;
	}

	LUCE_METHOD(getTitleBackgroundColor) {
		auto color = FlowStyle::getTitleBackgroundColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getTitleHighlightColor) {
		auto color = FlowStyle::getTitleHighlightColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getTitleBorderColor) {
		auto color = FlowStyle::getTitleBorderColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getTitleSplitColor) {
		auto color = FlowStyle::getTitleSplitColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getTitleTextColor) {
		auto color = FlowStyle::getTitleTextColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getTitleTextHighlightColor) {
		auto color = FlowStyle::getTitleTextHighlightColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}



	LUCE_METHOD(setResizerHeight) {
		FlowStyle::setResizerHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setResizerWidth) {
		FlowStyle::setResizerWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setUnitMinimumHeight) {
		FlowStyle::setUnitMinimumHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setUnitMinimumWidth) {
		FlowStyle::setUnitMinimumWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setResizerColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setResizerColor(*pColor);
		return 0;
	}


	LUCE_METHOD(getResizerHeight) {
		lua_pushnumber(L, FlowStyle::getResizerHeight());
		return 1;
	}

	LUCE_METHOD(getResizerWidth) {
		lua_pushnumber(L, FlowStyle::getResizerWidth());
		return 1;
	}

	LUCE_METHOD(getUnitMinimumHeight) {
		lua_pushnumber(L, FlowStyle::getUnitMinimumHeight());
		return 1;
	}

	LUCE_METHOD(getUnitMinimumWidth) {
		lua_pushnumber(L, FlowStyle::getUnitMinimumWidth());
		return 1;
	}

	LUCE_METHOD(getResizerColor) {
		auto color = FlowStyle::getResizerColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}



	LUCE_METHOD(setContainerResizerHeight) {
		FlowStyle::setContainerResizerHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setContainerResizerWidth) {
		FlowStyle::setContainerResizerWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setContainerDefaultHeight) {
		FlowStyle::setContainerDefaultHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setContainerDefaultWidth) {
		FlowStyle::setContainerDefaultWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setContainerBorderSize) {
		FlowStyle::setContainerBorderSize(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setContainerBorderColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setContainerBorderColor(*pColor);
		return 0;
	}


	LUCE_METHOD(getContainerResizerHeight) {
		lua_pushnumber(L, FlowStyle::getContainerResizerHeight());
		return 1;
	}

	LUCE_METHOD(getContainerResizerWidth) {
		lua_pushnumber(L, FlowStyle::getContainerResizerWidth());
		return 1;
	}

	LUCE_METHOD(getContainerDefaultHeight) {
		lua_pushnumber(L, FlowStyle::getContainerDefaultHeight());
		return 1;
	}

	LUCE_METHOD(getContainerDefaultWidth) {
		lua_pushnumber(L, FlowStyle::getContainerDefaultWidth());
		return 1;
	}

	LUCE_METHOD(getContainerBorderSize) {
		lua_pushnumber(L, FlowStyle::getContainerBorderSize());
		return 1;
	}

	LUCE_METHOD(getContainerBorderColor) {
		auto color = FlowStyle::getContainerBorderColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}



	LUCE_METHOD(setButtonWidth) {
		FlowStyle::setButtonWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonHeight) {
		FlowStyle::setButtonHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonIconWidth) {
		FlowStyle::setButtonIconWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonIconHeight) {
		FlowStyle::setButtonIconHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonSplitWidth) {
		FlowStyle::setButtonSplitWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonSplitHeight) {
		FlowStyle::setButtonSplitHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonPaddingWidth) {
		FlowStyle::setButtonPaddingWidth(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonPaddingHeight) {
		FlowStyle::setButtonPaddingHeight(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonCornerSize) {
		FlowStyle::setButtonCornerSize(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonBorderSize) {
		FlowStyle::setButtonBorderSize(luaL_checknumber(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonIconColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setButtonIconColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setButtonIconBackgroundColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setButtonIconBackgroundColor(*pColor);
		return 0;
	}

	LUCE_METHOD(setAdsorbColor) {
		auto& pColor = LUCE_CHECK_USERDATA(L, 1, Colour);
		FlowStyle::setAdsorbColor(*pColor);
		return 0;
	}


	LUCE_METHOD(getButtonWidth) {
		lua_pushnumber(L, FlowStyle::getButtonWidth());
		return 1;
	}

	LUCE_METHOD(getButtonHeight) {
		lua_pushnumber(L, FlowStyle::getButtonHeight());
		return 1;
	}

	LUCE_METHOD(getButtonIconWidth) {
		lua_pushnumber(L, FlowStyle::getButtonIconWidth());
		return 1;
	}

	LUCE_METHOD(getButtonIconHeight) {
		lua_pushnumber(L, FlowStyle::getButtonIconHeight());
		return 1;
	}

	LUCE_METHOD(getButtonSplitWidth) {
		lua_pushnumber(L, FlowStyle::getButtonSplitWidth());
		return 1;
	}

	LUCE_METHOD(getButtonSplitHeight) {
		lua_pushnumber(L, FlowStyle::getButtonSplitHeight());
		return 1;
	}

	LUCE_METHOD(getButtonPaddingWidth) {
		lua_pushnumber(L, FlowStyle::getButtonPaddingWidth());
		return 1;
	}

	LUCE_METHOD(getButtonPaddingHeight) {
		lua_pushnumber(L, FlowStyle::getButtonPaddingHeight());
		return 1;
	}

	LUCE_METHOD(getButtonCornerSize) {
		lua_pushnumber(L, FlowStyle::getButtonCornerSize());
		return 1;
	}

	LUCE_METHOD(getButtonBorderSize) {
		lua_pushnumber(L, FlowStyle::getButtonBorderSize());
		return 1;
	}

	LUCE_METHOD(getButtonIconColor) {
		auto color = FlowStyle::getButtonIconColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getButtonIconBackgroundColor) {
		auto color = FlowStyle::getButtonIconBackgroundColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}

	LUCE_METHOD(getAdsorbColor) {
		auto color = FlowStyle::getAdsorbColor();
		LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, Colour, pColor, color);
		return 1;
	}



	LUCE_METHOD(setButtonLeftIcon) {
		FlowStyle::setButtonLeftIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonRightIcon) {
		FlowStyle::setButtonRightIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonTopIcon) {
		FlowStyle::setButtonTopIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonBottomIcon) {
		FlowStyle::setButtonBottomIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonAdsorbCenterIcon) {
		FlowStyle::setButtonAdsorbCenterIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonAdsorbLeftIcon) {
		FlowStyle::setButtonAdsorbLeftIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonAdsorbRightIcon) {
		FlowStyle::setButtonAdsorbRightIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonAdsorbTopIcon) {
		FlowStyle::setButtonAdsorbTopIcon(luaL_checkstring(L, 1));
		return 0;
	}

	LUCE_METHOD(setButtonAdsorbBottomIcon) {
		FlowStyle::setButtonAdsorbBottomIcon(luaL_checkstring(L, 1));
		return 0;
	}


	LUCE_METHOD(getButtonLeftIcon) {
		lua_pushstring(L, FlowStyle::getButtonLeftIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonRightIcon) {
		lua_pushstring(L, FlowStyle::getButtonRightIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonTopIcon) {
		lua_pushstring(L, FlowStyle::getButtonTopIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonBottomIcon) {
		lua_pushstring(L, FlowStyle::getButtonBottomIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonAdsorbCenterIcon) {
		lua_pushstring(L, FlowStyle::getButtonAdsorbCenterIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonAdsorbLeftIcon) {
		lua_pushstring(L, FlowStyle::getButtonAdsorbLeftIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonAdsorbRightIcon) {
		lua_pushstring(L, FlowStyle::getButtonAdsorbRightIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonAdsorbTopIcon) {
		lua_pushstring(L, FlowStyle::getButtonAdsorbTopIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD(getButtonAdsorbBottomIcon) {
		lua_pushstring(L, FlowStyle::getButtonAdsorbBottomIcon().toStdString().c_str());
		return 1;
	}

	LUCE_METHOD_LIST(FlowStyle);
	LUCE_STATIC_METHOD_LIST(FlowStyle,
		setTitleHeight,
		setTitleWidth,
		setTitleBorderHeight,
		setTitleBorderWidth,
		setTitleSplitWidth,
		setTitleSplitHeight,
		setTitleSplitVLength,
		setTitleSplitHLength,
		setTitleTextHeight,
		setTitleTextWidth,
		setTitleTextPaddingWidth,
		setTitleTextPaddingHeight,
		setTitleBackgroundColor,
		setTitleHighlightColor,
		setTitleBorderColor,
		setTitleSplitColor,
		setTitleTextColor,
		setTitleTextHighlightColor,

		getTitleHeight,
		getTitleWidth,
		getTitleBorderHeight,
		getTitleBorderWidth,
		getTitleSplitWidth,
		getTitleSplitHeight,
		getTitleSplitVLength,
		getTitleSplitHLength,
		getTitleTextHeight,
		getTitleTextWidth,
		getTitleTextPaddingWidth,
		getTitleTextPaddingHeight,
		getTitleBackgroundColor,
		getTitleHighlightColor,
		getTitleBorderColor,
		getTitleSplitColor,
		getTitleTextColor,
		getTitleTextHighlightColor,



		setResizerHeight,
		setResizerWidth,
		setUnitMinimumHeight,
		setUnitMinimumWidth,
		setResizerColor,

		getResizerHeight,
		getResizerWidth,
		getUnitMinimumHeight,
		getUnitMinimumWidth,
		getResizerColor,



		setContainerResizerHeight,
		setContainerResizerWidth,
		setContainerDefaultHeight,
		setContainerDefaultWidth,
		setContainerBorderSize,
		setContainerBorderColor,

		getContainerResizerHeight,
		getContainerResizerWidth,
		getContainerDefaultHeight,
		getContainerDefaultWidth,
		getContainerBorderSize,
		getContainerBorderColor,



		setButtonWidth,
		setButtonHeight,
		setButtonIconWidth,
		setButtonIconHeight,
		setButtonSplitWidth,
		setButtonSplitHeight,
		setButtonPaddingWidth,
		setButtonPaddingHeight,
		setButtonCornerSize,
		setButtonBorderSize,
		setButtonIconColor,
		setButtonIconBackgroundColor,
		setAdsorbColor,

		getButtonWidth,
		getButtonHeight,
		getButtonIconWidth,
		getButtonIconHeight,
		getButtonSplitWidth,
		getButtonSplitHeight,
		getButtonPaddingWidth,
		getButtonPaddingHeight,
		getButtonCornerSize,
		getButtonBorderSize,
		getButtonIconColor,
		getButtonIconBackgroundColor,
		getAdsorbColor,



		setButtonLeftIcon,
		setButtonRightIcon,
		setButtonTopIcon,
		setButtonBottomIcon,
		setButtonAdsorbCenterIcon,
		setButtonAdsorbLeftIcon,
		setButtonAdsorbRightIcon,
		setButtonAdsorbTopIcon,
		setButtonAdsorbBottomIcon,

		getButtonLeftIcon,
		getButtonRightIcon,
		getButtonTopIcon,
		getButtonBottomIcon,
		getButtonAdsorbCenterIcon,
		getButtonAdsorbLeftIcon,
		getButtonAdsorbRightIcon,
		getButtonAdsorbTopIcon,
		getButtonAdsorbBottomIcon
	);

	LUCE_NEW(FlowStyle) {
		return 0;
	}
}
