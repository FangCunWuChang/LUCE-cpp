local ColourIds = {
    backgroundColourId = 0x1000b00,			        -- The background colour to fill the box with.
    textColourId = 0x1000a00,                       -- The colour for the text in the box.
    outlineColourId = 0x1000c00,                    -- The colour for an outline around the box.
    buttonColourId = 0x1000d00,                     -- The base colour for the button (a LookAndFeel class will probably use variations on this).
    arrowColourId = 0x1000e00,                      -- The colour for the arrow shape that pops up the menu.
    focusedOutlineColourId = 0x1000f00              -- The colour that will be used to draw a box around the edge of the component when it has focus.
}

luce.ComboBox.set("ColourIds", ColourIds)

return luce.ComboBox