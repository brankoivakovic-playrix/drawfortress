#pragma once

#include "IRender.h"

class IRenderable
{
public:
	virtual void render(IRender& render) = 0;
};