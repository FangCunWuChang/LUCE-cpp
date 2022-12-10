print(luce.APP_ARGC)
print(luce.APP_ARGV)

print(luce)
print(luce.adapters)
print(luce.adapters.LUCEApplication)
print(luce.adapters.LUCEApplication.new)

local app1 = luce.adapters.LUCEApplication:new()
print(app1.test)
app1:test("message1")

local app2 = luce.adapters.LUCEApplication:new()
print(app2.test)
app2:test("message2")

luce.APP_RET = 114514