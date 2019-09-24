#include "Inventory.h"


Inventory::Inventory(ISerializer & serializer) : Serializable(serializer)
{
}

void Inventory::PushItem(InventoryItem& item)
{
	_items.push_back(&item);
}
