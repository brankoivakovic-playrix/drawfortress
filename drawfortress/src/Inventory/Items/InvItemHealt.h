#pragma once

#include "Inventory/InventoryItem.h"

class InvItemHealt : public InventoryItem
{
public:
	InvItemHealt();

private:
	float _value = 100.f;
};