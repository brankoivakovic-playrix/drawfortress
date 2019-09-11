#pragma once
#include "Common.h"

#include "Serializer/ISerializable.h"
#include "InventoryItem.h"

class Inventory : public ISerializable
{
private:
	std::vector<InventoryItem> _items;
};