luce.DocumentWindow = {}

function luce.DocumentWindow.new(name, backgroundColour, requiredButtons, addToDesktop)
	o = luce.new(luce.DocumentWindow)
	luce.bind(o, luce.adapters.DocumentWindow.new(name, backgroundColour.__adapter, requiredButtons, addToDesktop))
	return o
end

luce.DocumentWindow.TitleBarButtons = {
	minimiseButton = 1,
	maximiseButton = 2,
	closeButton = 4,

	allButtons = 7
}

function luce.DocumentWindow:setVisible(visible)
	self.__adapter:setVisible(visible)
end

return luce.DocumentWindow