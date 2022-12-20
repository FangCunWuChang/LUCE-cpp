require "luce.TitleBarButtons"
require "luce.Colours"
require "luce.Justification"
require "luce.Debug"

luce.initialise = function(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	mainWindow = luce.DocumentWindow.new(
		"LUCE-demo1", luce.Colours.pink,
		luce.TitleBarButtons.allButtons, true)
	mainComponent = luce.Component.new("LUCE-demo1")
	label = luce.Label.new("test label", "Hello World!")

	label:setJustificationType(luce.Justification.centred)

	luce.Component.bind("resized", function(self)
		local width = self:getWidth()
		local height = self:getHeight()

		luce.Component.cast(label, function()
			label:setBounds(0, 0, width, height)
		end)
	end)

	mainWindow:setUsingNativeTitleBar(true)
	mainWindow:setResizable(true, false)
	mainWindow:setContentNonOwned(mainComponent, false)

	mainWindow:centreWithSize(800, 600)

	luce.Component.cast(label, function()
		mainComponent:addChildComponent(label)
		label:setVisible(true)
	end)

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
