#pragma once


class InventoryItem
{
public:
	enum class Type
	{
		Healt,
		Weapon,
		Shield,
	};

	InventoryItem(Type type);

	inline Type getType() const { return _type; }
private:
	Type _type;
};