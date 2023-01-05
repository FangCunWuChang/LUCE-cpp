luce.FlowComponent.bind("paint", function(self, g)
	local data = self:data()
	if data.paint then
		data.paint(self, g)
	end
end)

luce.FlowComponent.bind("paintOverChildren", function(self, g)
	local data = self:data()
	if data.paintOverChildren then
		data.paintOverChildren(self, g)
	end
end)

luce.FlowComponent.bind("mouseMove", function(self, event)
	local data = self:data()
	if data.mouseMove then
		data.mouseMove(self, event)
	end
end)

luce.FlowComponent.bind("mouseEnter", function(self, event)
	local data = self:data()
	if data.mouseEnter then
		data.mouseEnter(self, event)
	end
end)

luce.FlowComponent.bind("mouseExit", function(self, event)
	local data = self:data()
	if data.mouseExit then
		data.mouseExit(self, event)
	end
end)

luce.FlowComponent.bind("mouseDown", function(self, event)
	local data = self:data()
	if data.mouseDown then
		data.mouseDown(self, event)
	end
end)

luce.FlowComponent.bind("mouseDrag", function(self, event)
	local data = self:data()
	if data.mouseDrag then
		data.mouseDrag(self, event)
	end
end)

luce.FlowComponent.bind("mouseUp", function(self, event)
	local data = self:data()
	if data.mouseUp then
		data.mouseUp(self, event)
	end
end)

luce.FlowComponent.bind("mouseDoubleClick", function(self, event)
	local data = self:data()
	if data.mouseDoubleClick then
		data.mouseDoubleClick(self, event)
	end
end)

luce.FlowComponent.bind("mouseWheelMove", function(self, event, wheel)
	local data = self:data()
	if data.mouseWheelMove then
		data.mouseWheelMove(self, event, wheel)
	end
end)

luce.FlowComponent.bind("resized", function(self)
	local data = self:data()
	if data.resized then
		data.resized(self)
	end
end)

luce.FlowComponent.bind("moved", function(self)
	local data = self:data()
	if data.moved then
		data.moved(self)
	end
end)

return luce.FlowComponent