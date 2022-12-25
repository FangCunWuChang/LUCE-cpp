require "luce.Colours"

return function()
	local base = require("ui.demo2")()
	base.background = luce.Colours.grey
	return base
end
