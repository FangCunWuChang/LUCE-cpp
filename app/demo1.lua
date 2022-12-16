require "luce.LUCEApplication"
require "luce.DocumentWindow"
require "luce.Colours"
require "luce.Flag"

app = luce.LUCEApplication.new()

luce.LUCEApplication.bind("getApplicationName", function(self)
	return "testAppName"
end)

luce.LUCEApplication.bind("getApplicationVersion", function(self)
	return "testVersion"
end)

luce.LUCEApplication.bind("initialise", function(self, commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")

	luce.LUCEApplication.bind("mainWindow", 
		luce.DocumentWindow.new(
			"LUCE-demo1", luce.Colours.pink,
			luce.TitleBarButtons.allButtons, false))
	self.mainWindow:setVisible(true)
end)

luce.LUCEApplication.bind("shutdown", function(self)
	print("app shutdown")
end)

luce.LUCEApplication.bind("moreThanOneInstanceAllowed", function(self)
	return false
end)

luce.LUCEApplication.bind("anotherInstanceStarted", function(self, commandLine)
	print("another command:", commandLine)
	print("another start")
end)

luce.exec(app)