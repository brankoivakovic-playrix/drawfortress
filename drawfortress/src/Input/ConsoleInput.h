#pragma once

#include <utility>
#include "Common.h"




struct ConsoleInput
{
	enum class Type
	{
		Focus,
		Resize,

		KeyDown,
		KeyUp,
		
		Click,
		
		LeftButtonDown,
		LeftButtonUp,
		
		RightButtonDown,
		RightButtonUp,
		
		MouseMove,
		DragStart,
		Drag,
		DragEnd,
	};
	
	Type type;

	unsigned short virtualKey = 0;
	
	char character = 0;

	bool isAlt   = false;
	bool isCtrl  = false;
	bool isShift = false;

	Vector2di mousePos;
	Vector2di prevMousePos;
};

