luce.Justification = {
	left = 1,								-- Indicates that the item should be aligned against the left edge of the available space.
	right = 2,								-- Indicates that the item should be aligned against the right edge of the available space.
	horizontallyCentred = 4,				-- Indicates that the item should be placed in the centre between the left and right sides of the available space.
	top = 8,								-- Indicates that the item should be aligned against the top edge of the available space.
	bottom = 16,							-- Indicates that the item should be aligned against the bottom edge of the available space.
	verticallyCentred = 32,					-- Indicates that the item should be placed in the centre between the top and bottom sides of the available space.
	horizontallyJustified = 64,				-- Indicates that lines of text should be spread out to fill the maximum width available, so that both margins are aligned vertically.



	centred = 36,							-- Indicates that the item should be centred vertically and horizontally.
											-- This is equivalent to (horizontallyCentred | verticallyCentred)

	centredLeft = 33,						-- Indicates that the item should be centred vertically but placed on the left hand side.
											-- This is equivalent to (left | verticallyCentred)

	centredRight = 34,						-- Indicates that the item should be centred vertically but placed on the right hand side.
											-- This is equivalent to (right | verticallyCentred)

	centredTop = 12,						-- Indicates that the item should be centred horizontally and placed at the top.
											-- This is equivalent to (horizontallyCentred | top)

	centredBottom = 20,						-- Indicates that the item should be centred horizontally and placed at the bottom.
											-- This is equivalent to (horizontallyCentred | bottom)

	topLeft = 9,							-- Indicates that the item should be placed in the top-left corner.
											-- This is equivalent to (left | top)

	topRight = 10,							-- Indicates that the item should be placed in the top-right corner.
											-- This is equivalent to (right | top)

	bottomLeft = 17,						-- Indicates that the item should be placed in the bottom-left corner.
											-- This is equivalent to (left | bottom)

	bottomRight = 18						-- Indicates that the item should be placed in the bottom-left corner.
											-- This is equivalent to (right | bottom)
}

return luce.Justification