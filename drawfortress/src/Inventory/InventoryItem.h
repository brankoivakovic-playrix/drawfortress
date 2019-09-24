#pragma once
#include "World/WorldField.h"
#include "Weapon/Weapon.h"


class InventoryItem : public WorldField::Item
{
public:
	enum class Type
	{
		Health,
		Weapon,
		Shield,
	};

	InventoryItem(Type type);

	Type getType() const { return _type; }
	
private:
	Type _type;
	
	union
	{
		float   _health;
		float   _shield;
		Weapon* _weapon;
	};
};
