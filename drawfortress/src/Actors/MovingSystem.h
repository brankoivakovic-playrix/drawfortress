#pragma once

#include "Common.h"
#include "Enemy.h"

struct MovingComponent
{
	Vector2di    position;
	Vector2di    homePoint;
	unsigned int movingRadius = 10;
	
	MovingType   movingType = MovingType::MovingAround;
};

class MovingSystem
{
public:
	static void Update();

	static MovingComponent& Get(const Enemy& key);

	static MovingComponent* RegisterEnemy(weak_ptr<Enemy> enemy);
};
