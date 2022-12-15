require "luce.LUCEApplication"
require "luce.DocumentWindow"
require "luce.Colour"
require "luce.Flag"

app = luce.LUCEApplication.new()

function app:getApplicationName()
	return "testAppName"
end

function app:getApplicationVersion()
	return "testVersion"
end

function app:initialise(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	self.mainWindow = 
		luce.DocumentWindow.new("LUCE-demo1", luce.Colours.pink,
			luce.DocumentWindow.TitleBarButtons.allButtons, false)
	self.mainWindow:setVisible(true)
end

function app:shutdown()
	print("app shutdown")
end

function app:moreThanOneInstanceAllowed()
	return false
end

function app:anotherInstanceStarted(commandLine)
	print("another command:", commandLine)
	print("another start")
end

app:exec()