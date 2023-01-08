local ColourIds = {
	backgroundColourId = 0x1000700,			        -- A colour to use to fill the window's background.
    textColourId = 0x1000600,                       -- The colour for normal menu item text, (unless the colour is specified when the item is added).
    headerTextColourId = 0x1000601,                 -- The colour for section header item text (see the addSectionHeader() method).
    highlightedBackgroundColourId = 0x1000900,      -- The colour to fill the background of the currently highlighted menu item.
    highlightedTextColourId = 0x1000800             -- The colour to use for the text of the currently highlighted item.
}

luce.PopupMenu.set("ColourIds", ColourIds)

return luce.PopupMenu