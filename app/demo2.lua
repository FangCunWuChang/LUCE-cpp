require "luce.DocumentWindow"
require "luce.Colours"
require "luce.Justification"
require "luce.Debug"

luce.initialise = function(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")
end

luce.shutdown = function()
	print("app shutdown")
end

luce.anotherInstanceStarted = function(commandLine)
	print("another command:", commandLine)
	print("another start")
end