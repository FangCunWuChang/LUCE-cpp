print(luce.APP_ARGC)
print(luce.APP_ARGV)

local app = luce.adapters.LUCEApplication.new("testName", "testVersion")

luce.APP_RET = app:exec()