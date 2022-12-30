require "luce.Debug"

luce.initialise = function(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	mainWindow = luce.FlowWindow.new()

	comp1 = luce.FlowComponent.new("comp1")
	comp2 = luce.FlowComponent.new("comp2")
	comp3 = luce.FlowComponent.new("comp3")
	comp4 = luce.FlowComponent.new("comp4")
	comp5 = luce.FlowComponent.new("comp5")

	mainWindow:openComponent(comp1)
	mainWindow:openComponent(comp2, false)
	mainWindow:openComponent(comp3)
	mainWindow:openComponent(comp4)
	mainWindow:openComponent(comp5)
end

luce.shutdown = function()
	print("app shutdown")
	mainWindow = nil
end

luce.anotherInstanceStarted = function(commandLine)
	print("another command:", commandLine)
	print("another start")
end