#include "../../LUCE.h"

LUCE_APPLICATION("appName", "appVersion", false, "demo1.lua", {
			luce::loadCore(L);
			luce::loadGUI(L);
			luce::loadGraphics(L);
	});
