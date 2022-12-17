luce.Debug = {}

luce.Debug.printObjectInformation = function(obj)
	print("")
	print("=====================LUCE Object=====================")

	print("address: ", obj)

	meta = getmetatable(obj)
	print("meta table: ", meta)

	for k, v in pairs(meta)
	do
		print("\t", k, "\t\t", v)
	end

	print("")
	print("Total ", #meta, " objects in the meta table.")
	print("=====================================================")
	print("")
end

luce.Debug.printObjectRefs = function(obj)
	print("")
	print("===================LUCE Object Refs===================")

	print("object address: ", obj)
	print("__refs table: ", luce.__refs)

	count = 0
	for k, v in pairs(luce.__refs)
	do
		if v == obj
		then
			print("\t", k, "\t\t", v)
			count = count + 1
		end
	end

	print("")
	print("Total ", #luce.__refs, " objects in the __refs table. ", count, " is the ref of current object.")
	print("======================================================")
	print("")
end

luce.Debug.printAllObjectRefs = function()
	print("")
	print("=================LUCE All Object Refs=================")

	print("__refs table: ", luce.__refs)

	for k, v in pairs(luce.__refs)
	do
		print("\t", k, "\t\t", v)
	end

	print("")
	print("Total ", #luce.__refs, " objects in the __refs table.")
	print("======================================================")
	print("")
end

return luce.Debug