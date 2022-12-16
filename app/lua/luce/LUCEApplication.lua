luce.exec = function(application)
	luce.APP_RET = application:exec(luce.APP_ARGC, luce.APP_ARGV)
end

return luce.LUCEApplication