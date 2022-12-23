#include "../../LUCE.h"

LUCE_APPLICATION("appName", "appVersion", false, "demo2.lua", {
			luce::loadCore(L);
			luce::loadGUI(L);
			luce::loadGraphics(L);
			luce::loadQuickUI(L);
	});
