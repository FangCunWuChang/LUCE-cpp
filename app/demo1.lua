
require "luce.LUCEApplication"

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

luce.APP_RET = app:exec()