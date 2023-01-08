local ColourIds = {
	backgroundColourId = 0x1001800,			        -- The background colour for the window.
    textColourId = 0x1001810,                       -- The colour for the text.
    outlineColourId = 0x1001820                     -- An optional colour to use to draw a border around the window.
}

luce.AlertWindow.set("ColourIds", ColourIds)

return luce.AlertWindow