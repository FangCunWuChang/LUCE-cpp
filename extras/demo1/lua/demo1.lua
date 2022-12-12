function luce:APP_NAME_FUNC()
	return "testAppName"
end

function luce:APP_VER_FUNC()
	return "testVersion"
end

function luce:APP_INIT_FUNC(commandLineParameters)
	print("command:", commandLineParameters)
	print("app init")
end

function luce:APP_SHUTDOWN_FUNC()
	print("app shutdown")
end

function luce:APP_ALLOW_MULTI_FUNC()
	return false
end

function luce:APP_ANOTHER_START_FUNC(commandLine)
	print("another command:", commandLine)
	print("another start")
end

app = luce.adapters.LUCEApplication.new()
luce.APP_RET = app:exec()