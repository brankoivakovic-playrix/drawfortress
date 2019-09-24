#pragma once
#include "Common.h"

#include "Serializer/Serializable.h"
#include "InventoryItem.h"

class Inventory : public Serializable, public Entity
{
public:
	Inventory(ISerializer& serializer);
	
	void PushItem(InventoryItem& item);


	ID GetId() const override { return id; }


	string GetTypeName() const override { return "Inventory"; }

	
	
private:
	std::vector<InventoryItem*> _items;
};