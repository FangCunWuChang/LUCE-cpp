require "luce.Colours"

luce.QuickComponent.bind("init", function(self)
	local data = self:data()

	data.QuickComponent = {}

	data.QuickComponent.enabled = true
	data.QuickComponent.mouseIn = false
	data.QuickComponent.mouseDown = false
	data.QuickComponent.toggled = false
	data.QuickComponent.toggleable = false

	-- [1] normal		enabled = true, mouseIn = false, mouseDown = false, toggled = false
	-- [2] hovered		enabled = true, mouseIn = true, mouseDown = false, toggled = false
	-- [3] pressed		enabled = true, mouseDown = true, toggled = false
	-- [4] disabled		enabled = false, toggled = false
	-- [5] toggled		enabled = true, mouseIn = false, mouseDown = false, toggled = true
	-- [6] hoveredT		enabled = true, mouseIn = true, mouseDown = false, toggled = true
	-- [7] pressedT		enabled = true, mouseDown = true, toggled = true
	-- [8] disabledT	enabled = false, toggled = true
	data.QuickComponent.list = {}
	data.QuickComponent.style = {}
	data.QuickComponent.elements = {}

	data.QuickComponent.areaFunc = function() return self:getArea() end
	data.QuickComponent.screenFunc = function() return self:getScreen() end

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

	data.QuickComponent.stateChanged = function(self)
		local getIDFunc = function()
			local id = 0
			if self.toggled then id = 5 else id = 1 end
			if not self.enabled then
				id = id + 3
				return id
			end
			if self.mouseDown then
				id = id + 2
				return id
			end
			if self.mouseIn then
				id = id + 1
				return id
			end
			return id
		end
		
		local baseMap = {
			[1] = {},
			[2] = { 1 },
			[3] = { 1 },
			[4] = { 1 },
			[5] = { 1 },
			[6] = { 2, 5, 1 },
			[7] = { 3, 5, 1 },
			[8] = { 4, 5, 1 }
		}

		local stateID = getIDFunc()
		local styleSheet = self.list[stateID]
		if styleSheet == nil then
			local map = baseMap[stateID]
			if map ~= nil then
				for i, v in ipairs(map) do
					if self.list[v] ~= nil then
						styleSheet = self.list[v]
						break
					end
				end
			end
		end
		if styleSheet ~= nil then
			self.style = require(styleSheet)() or {}
			self:update()
		end
	end

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

luce.QuickComponent.bind("setStyle", function(self, ...)
	local data = self:data()

	if data.QuickComponent == nil then
		self:init()
	end

	data.QuickComponent.list = { ... }
	data.QuickComponent:stateChanged()

	self:repaint()
end)

luce.QuickComponent.bind("setEnabled", function(self, enabled)
	local data = self:data()

	if data.QuickComponent == nil then
		self:init()
	end

	data.QuickComponent.enabled = enabled
	data.QuickComponent:stateChanged()

	self:repaint()
end)

luce.QuickComponent.bind("setToggled", function(self, toggled)
	local data = self:data()

	if data.QuickComponent == nil then
		self:init()
	end

	data.QuickComponent.toggled = toggled
	data.QuickComponent:stateChanged()

	self:repaint()
end)

luce.QuickComponent.bind("setToggleable", function(self, toggleable)
	local data = self:data()

	if data.QuickComponent == nil then
		self:init()
	end

	data.QuickComponent.toggleable = toggleable
end)

return luce.QuickComponent