#pragma once

#include "Common.h"

class Actor;
class InventoryItem;
class WorldField;


class WorldField
{
public:

	enum class ItemType
	{
		Empty,
		Actor,
		InventoryItem,
		StaticItem,
	};
	
#ifdef _DEBUG
	int x = 0;
	int y = 0;
#endif
	
	WorldField()                  = default;
	WorldField(const WorldField&) = delete;
	WorldField(WorldField&&)      = delete;
	
	~WorldField() = default;
	
	WorldField& operator = (const WorldField&) = delete;
	WorldField& operator = (WorldField&&)      = delete;
	
	struct Item
	{	
		explicit Item(const ItemType type) : type(type){}

		Item()            = delete;
		Item(const Item&) = delete;
		Item(Item&&)      = delete;

		virtual ~Item();

		Item& operator = (const Item& ) = delete;
		Item& operator = (      Item&&) = delete;
		
		const ItemType  type;
		
		WorldField* field = nullptr;
	};

	void ReleaseItem();
	
	void ReplaceItem(Item* newItem);

	void SwapItem(WorldField* toField);

	Vector2di GetPlace() const;


	ItemType Type() const { return _itemType; }

	void SetStaticItem();

	Actor*  GetActor() const;
	
	InventoryItem* GetInventoryItem() const;
	
private:

	ItemType _itemType = ItemType::Empty;
	Item*    _item     = nullptr;

};


struct PathFinderItem
{
	PathFinderItem(PathFinderItem&&)      = default;
	PathFinderItem(const PathFinderItem&) = default;
	
	~PathFinderItem() = default;
	
	int_t x, y, distance;
	
	WorldField*     field;
	
	const PathFinderItem* parent;
};
