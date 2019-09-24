#include "WorldField.h"

#include "Game.h"
#include "World.h"
#include "Actors/Actor.h"
#include "Inventory/InventoryItem.h"

void WorldField::ReleaseItem()
{
	if(_itemType != ItemType::Empty)
	{
		if(_itemType != ItemType::StaticItem)
		{
			_item->field = nullptr;
		}
		_itemType    = ItemType::Empty;
		_item        = nullptr;
	}
}

void WorldField::ReplaceItem(Item* newItem)
{
	ReleaseItem();
	if(newItem->field)
	{
		newItem->field->ReleaseItem();
	}
	_itemType  = newItem->type;
	_item      = newItem;
	newItem->field = this;
}

void WorldField::SwapItem(WorldField * toField)
{
	Item* myItem = _item;
	Item* item   = toField->_item;
	
	ReplaceItem(item);
	toField->ReplaceItem(myItem);
}

Vector2di WorldField::GetPlace() const
{
	return Game::Instance().GetWorld().GetFieldPlace(*this);
}

void WorldField::SetStaticItem()
{
	ReleaseItem();
	_itemType = ItemType::StaticItem;
}

Actor* WorldField::GetActor() const
{
	return dynamic_cast<Actor*>(_item);
}

InventoryItem* WorldField::GetInventoryItem() const
{
	return dynamic_cast<InventoryItem*>(_item);
}

WorldField::Item::~Item()
{
	if (field)
	{
		field->ReleaseItem();
	}
}
