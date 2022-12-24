require "luce.DocumentWindow"
require "luce.Justification"
require "luce.QuickComponent"
require "luce.Debug"

luce.initialise = function(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	mainWindow = luce.DocumentWindow.new(
		"LUCE-demo2",
		luce.Desktop.getInstance():getDefaultLookAndFeel():findColour(
			luce.ResizableWindow.ColourIds.backgroundColourId),
		luce.DocumentWindow.TitleBarButtons.allButtons, true)
	mainComponent = luce.QuickComponent.new("LUCE-demo2")
	mainComponent:setStyle("ui.demo2")
	
	mainWindow:setUsingNativeTitleBar(true)
	mainWindow:setResizable(true, false)
	luce.Component.cast(mainComponent, function()
		mainWindow:setContentNonOwned(mainComponent, false)
	end)
	
	mainWindow:centreWithSize(800, 600)
	
	mainComponent:setVisible(true)
	mainWindow:setVisible(true)
end

luce.shutdown = function()
	print("app shutdown")
	mainWindow = nil
end

luce.anotherInstanceStarted = function(commandLine)
	print("another command:", commandLine)
	print("another start")
end