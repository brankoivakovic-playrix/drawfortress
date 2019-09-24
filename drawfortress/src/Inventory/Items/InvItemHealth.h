#pragma once

#include "Inventory/InventoryItem.h"

class InvItemHealth : public InventoryItem
{
public:
	InvItemHealth();

private:
	float _value = 100.f;
};