require "luce.Debug"
require "luce.Colours"
require "luce.FlowComponent"

luce.initialise = function(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	luce.FlowStyle.setButtonLeftIcon("./icons/layout-left-2-line.svg")
	luce.FlowStyle.setButtonRightIcon("./icons/layout-right-2-line.svg")
	luce.FlowStyle.setButtonTopIcon("./icons/layout-top-2-line.svg")
	luce.FlowStyle.setButtonBottomIcon("./icons/layout-bottom-2-line.svg")
	luce.FlowStyle.setButtonAdsorbCenterIcon("./icons/link.svg")
	luce.FlowStyle.setButtonAdsorbLeftIcon("./icons/layout-left-2-line.svg")
	luce.FlowStyle.setButtonAdsorbRightIcon("./icons/layout-right-2-line.svg")
	luce.FlowStyle.setButtonAdsorbTopIcon("./icons/layout-top-2-line.svg")
	luce.FlowStyle.setButtonAdsorbBottomIcon("./icons/layout-bottom-2-line.svg")

	local mainWindow = luce.FlowWindow.new()

	comp1 = luce.FlowComponent.new("comp1")
	comp2 = luce.FlowComponent.new("comp2")
	comp3 = luce.FlowComponent.new("comp3")
	comp4 = luce.FlowComponent.new("comp4")
	comp5 = luce.FlowComponent.new("comp5")

	local paintFunc = function(self, g)
		g:fillAll(luce.Colours.dimgrey)
	end

	comp1:data().paint = paintFunc
	comp2:data().paint = paintFunc
	comp3:data().paint = paintFunc
	comp4:data().paint = paintFunc
	comp5:data().paint = paintFunc

	mainWindow:openComponent(comp1)
	mainWindow:openComponent(comp2, false)
	mainWindow:openComponent(comp3)
	mainWindow:openComponent(comp4)
	mainWindow:openComponent(comp5)
end

luce.shutdown = function()
	print("app shutdown")
	luce.FlowWindow.shutdown()
end

luce.anotherInstanceStarted = function(commandLine)
	print("another command:", commandLine)
	print("another start")
end