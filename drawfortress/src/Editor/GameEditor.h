#pragma once

#include "Common.h"

#include "Input/ConsoleInputHandler.h"

class GameEditor
{
public:
private:
	std::shared_ptr<ConsoleInputHandler<GameEditor>> _onKeyDown;
	std::shared_ptr<ConsoleInputHandler<GameEditor>> _onClick;
	std::shared_ptr<ConsoleInputHandler<GameEditor>> _onRightClick;
	std::shared_ptr<ConsoleInputHandler<GameEditor>> _onMouseMove;
};
