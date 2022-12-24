require "luce.Colours"

luce.QuickComponent.bind("init", function(self)
	local data = self:data()

	data.QuickComponent = {}
	data.QuickComponent.style = {}
	data.QuickComponent.elements = {}

	data.QuickComponent.areaFunc = function() return luce.RectangleInt.new() end
	data.QuickComponent.screenFunc = function() return luce.RectangleInt.new() end

	data.QuickComponent.temp = {
		size = {
			margin = {
				left = 0,
				right = 0,
				top = 0,
				bottom = 0
			},
			border = {
				line = 0,
				corner = 0
			},
			padding = {
				left = 0,
				right = 0,
				top = 0,
				bottom = 0
			}
		},
		color = {
			border = 0,
			context = 0,
			background = 0
		}
	}

	data.QuickComponent.update = function(self)
		-- The box model
		local margin = self.style.margin or {}
		local border = self.style.border or {}
		local padding = self.style.padding or {}
		local context = self.style.context or {}

		-- Margin size
		local marginWidth = margin.width or 0
		local marginHeight = margin.height or 0

		self.temp.size.margin.left = margin.left or marginWidth
		self.temp.size.margin.right = margin.right or marginWidth
		self.temp.size.margin.top = margin.top or marginHeight
		self.temp.size.margin.bottom = margin.bottom or marginHeight

		-- Border size
		self.temp.size.border.line = border.line or 0
		self.temp.size.border.corner = border.corner or 0

		-- Padding size
		local paddingWidth = padding.width or 0
		local paddingHeight = padding.height or 0

		self.temp.size.padding.left = padding.left or paddingWidth
		self.temp.size.padding.right = padding.right or paddingWidth
		self.temp.size.padding.top = padding.top or paddingHeight
		self.temp.size.padding.bottom = padding.bottom or paddingHeight

		-- Border color
		self.temp.color.border = border.color or luce.Colours.black

		-- Color
		self.temp.color.context = self.style.color or luce.Colours.black
		self.temp.color.background = self.style.background or luce.Colours.black
	end

	data.QuickComponent.paint = function(self, g)
		-- Get paint area
		local area = self.areaFunc()
		local screen = self.screenFunc()

		-- Get box size
		local border = luce.RectangleFloat.new(
			self.temp.size.margin.left * screen:getWidth()
				+ self.temp.size.border.line * screen:getWidth() * 0.5,
			self.temp.size.margin.top * screen:getHeight()
				+ self.temp.size.border.line * screen:getWidth() * 0.5,
			area:getWidth() 
				- self.temp.size.margin.left * screen:getWidth()
				- self.temp.size.margin.right * screen:getWidth()
				- self.temp.size.border.line * screen:getWidth(),
			area:getHeight() 
				- self.temp.size.margin.top * screen:getHeight()
				- self.temp.size.margin.bottom * screen:getHeight()
				- self.temp.size.border.line * screen:getHeight()
		)
		local context = luce.RectangleFloat.new(
			self.temp.size.margin.left * screen:getWidth()
				+ self.temp.size.border.line * screen:getWidth()
				+ self.temp.size.padding.left * screen:getWidth(),
			self.temp.size.margin.top * screen:getHeight()
				+ self.temp.size.border.line * screen:getWidth()
				+ self.temp.size.padding.top * screen:getHeight(),
			area:getWidth() 
				- self.temp.size.margin.left * screen:getWidth()
				- self.temp.size.margin.right * screen:getWidth()
				- self.temp.size.border.line * screen:getWidth()
				- self.temp.size.border.line * screen:getWidth()
				- self.temp.size.padding.left * screen:getWidth()
				- self.temp.size.padding.right * screen:getWidth(),
			area:getHeight() 
				- self.temp.size.margin.top * screen:getHeight()
				- self.temp.size.margin.bottom * screen:getHeight()
				- self.temp.size.border.line * screen:getWidth()
				- self.temp.size.border.line * screen:getWidth()
				- self.temp.size.padding.top * screen:getHeight()
				- self.temp.size.padding.bottom * screen:getHeight()
		)
		local line = self.temp.size.border.line * screen:getWidth()
		local corner = self.temp.size.border.corner * screen:getWidth()

		-- Check size
		if (border:getWidth() > 0) and (border:getHeight() > 0) then
			-- Fill background
			g:setColour(self.temp.color.background)
			g:fillRoundedRectangle(border, corner)

			-- Draw border
			g:setColour(self.temp.color.border)
			g:drawRoundedRectangle(border, corner, line)
		end
	end

	return data.QuickComponent
end)

luce.QuickComponent.bind("setStyle", function(self, styleName)
	local data = self:data()

	if data.QuickComponent == nil then
		self:init()
	end

	data.QuickComponent.style = require(styleName)
	data.QuickComponent.areaFunc = function() return self:getArea() end
	data.QuickComponent.screenFunc = function() return self:getScreen() end
	data.QuickComponent:update()

	self:repaint()
end)

return luce.QuickComponent