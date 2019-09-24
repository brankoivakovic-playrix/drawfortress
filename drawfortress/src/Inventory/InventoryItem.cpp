#include "InventoryItem.h"

InventoryItem::InventoryItem(Type type) : Item(WorldField::ItemType::InventoryItem), _type(type)
{
}
