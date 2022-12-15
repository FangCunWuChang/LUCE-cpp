luce.LUCEApplication = {}

function luce.LUCEApplication.new()
	o = luce.new(luce.LUCEApplication)
	luce.bind(o, luce.adapters.LUCEApplication.new())
	return o
end

function luce.LUCEApplication:exec()
	luce.APP_RET = self.__adapter:exec()
end

function luce.LUCEApplication:getApplicationName()
	return ""
end

function luce.LUCEApplication:getApplicationVersion()
	return ""
end

function luce.LUCEApplication:initialise(commandLineParameters)
end

function luce.LUCEApplication:shutdown()
end

function luce.LUCEApplication:suspended()
end

function luce.LUCEApplication:resumed()
end

function luce.LUCEApplication:memoryWarningReceived()
end

function luce.LUCEApplication:backButtonPressed()
	return false
end

return luce.LUCEApplication