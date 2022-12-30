#include "../../LUCE.h"

LUCE_APPLICATION("appName", "appVersion", false, "demo3.lua", {
			luce::loadCore(L);
			luce::loadGUI(L);
			luce::loadGraphics(L);
			luce::loadFlowUI(L);
	});
