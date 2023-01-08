local ColourIds = {
    buttonColourId = 0x1000100,			        -- The colour used to fill the button shape (when the button is toggled 'off').
                                                -- The look-and-feel class might re-interpret this to add effects, etc.
    buttonOnColourId = 0x1000101,               -- The colour used to fill the button shape (when the button is toggled 'on').
                                                -- The look-and-feel class might re-interpret this to add effects, etc.
    textColourOffId = 0x1000102,                -- The colour to use for the button's text when the button's toggle state is "off".
    textColourOnId = 0x1000103                  -- The colour to use for the button's text.when the button's toggle state is "on".
}

luce.TextButton.set("ColourIds", ColourIds)

return luce.TextButton