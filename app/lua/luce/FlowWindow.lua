local function layout(filePath, ...)
	local list = {...}
	luce.FlowWindow.autoLayout(filePath, list)
end

luce.FlowWindow.set("layout", layout)

return luce.FlowWindow