#pragma once
#include "Common.h"

#include "Inventory/Inventory.h"
#include "Render/IRenderable.h"
#include "World/WorldField.h"
#include "Serializer/Serializable.h"

enum class MovingType
{
	Static,
	MovingAround,
	Hunting,
	Escaping,
};



class Actor : public Serializable, public IRenderable, public WorldField::Item, public Entity
{
public:
	Actor(ISerializer& serializer);

	void Draw(IRender& render) override;

	void AddInventoryItem(InventoryItem& item);
	
	ID GetId() const override { return id; }

	
protected:

	shared_ptr<Inventory>  _inventory;

	//stanje zdravlja, maksimalna vrednost je 1
	float _health = 1.f;

	//stanje stita, maksimalna vrednost je 1
	float _shield = 1.f;

	
};