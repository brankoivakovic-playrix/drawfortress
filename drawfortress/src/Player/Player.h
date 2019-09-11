#pragma once

#include "Common.h"

#include "Inventory/Inventory.h"
#include "Render/IRenderable.h"


class Player : public IRenderable
{
public:
	virtual void render(IRender& render) override;

private:
	std::shared_ptr<Inventory> _inventory;

	float _healt  = 100.f;
	float _shield = 100.f;
};