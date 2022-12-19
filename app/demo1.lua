require "luce.DocumentWindow"
require "luce.Colours"
require "luce.Debug"

luce.initialise = function(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	mainWindow = luce.DocumentWindow.new(
		"LUCE-demo1", luce.Colours.pink,
		luce.TitleBarButtons.allButtons, true)
	mainComponent = luce.Component.new("LUCE-demo1")

	mainWindow:setUsingNativeTitleBar(true)
	mainWindow:setResizable(true, false)
	mainWindow:setContentNonOwned(mainComponent, false)

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
