#include "Actor.h"
#include "Render/Render.h"
#include "World/World.h"
#include "Game.h"


Actor::Actor(ISerializer& serializer) : Item(WorldField::ItemType::Actor), Serializable(serializer),  _inventory(new Inventory(serializer))
{
}



void Actor::Draw(IRender& render)
{
	
}

void Actor::AddInventoryItem(InventoryItem& item)
{
	_inventory->PushItem(item);
}


