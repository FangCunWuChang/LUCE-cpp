require "luce.ResizableWindow"

local TitleBarButtons = {
	minimiseButton = 1,
	maximiseButton = 2,
	closeButton = 4,

	allButtons = 7				-- A combination of all the buttons above.
}

luce.DocumentWindow.set("TitleBarButtons", TitleBarButtons);

return luce.DocumentWindow