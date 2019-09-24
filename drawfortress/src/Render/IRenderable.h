#pragma once

#include "IRender.h"

class IRenderable
{
public:
	virtual void Draw(IRender& render) = 0;
};
