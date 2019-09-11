#pragma once

#include "../InventoryItem.h"

class InvItemWeapon : public InventoryItem
{
public:
	InvItemWeapon();

private:
	float _value;
};