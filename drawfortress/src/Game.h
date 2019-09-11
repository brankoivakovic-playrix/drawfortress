#pragma once

#include "Common.h"

class ISerializer;
class IRender;
class World;



class Game
{
public:
	static Game* instance();

	int Loop();

	void Pause();

	void Resume();

	void Serialize();
private:

	Game();

	std::shared_ptr<IRender>     _render;
	std::shared_ptr<World>       _world;
	std::shared_ptr<ISerializer> _serializer;
	//std::vector<std::week_ptr
};