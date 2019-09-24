#pragma once

#include "Common.h"

#include "Serializer/Serializer.h"

class ISerializer;
class IRender;
class World;


class Game
{
public:
	static Game& Instance();

	int Loop();

	void Serialize();

	void Draw();

	World& GetWorld() const;
	
private:

	Game();

	unique_ptr<ISerializer> _serializer;
	unique_ptr<World>       _world;
	time_point _startTime = chrono::steady_clock::now();
};