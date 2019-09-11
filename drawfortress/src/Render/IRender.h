#pragma once

#include "Common.h"

class IRender
{
public:
	virtual void DrawRect() = 0;

	virtual void flush() = 0;
};