require "luce.DocumentWindow"
require "luce.Colours"
require "luce.Justification"
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

	mainWindow:setUsingNativeTitleBar(true)
	mainWindow:setResizable(true, false)
	luce.Component.cast(mainComponent, function()
		mainWindow:setContentNonOwned(mainComponent, false)
	end)

	mainWindow:centreWithSize(800, 600)

	luce.Component.cast(mainComponent, function()
		mainComponent:setVisible(true)
	end)
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