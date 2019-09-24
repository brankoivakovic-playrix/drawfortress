#pragma once

#include "Actor.h"

enum class EnemyViewDirection
{
	North,
	East,
	South,
	West,
};



class Enemy : public Actor
{
public:
	Enemy(ISerializer& serializer);
	Enemy(Enemy&&) = delete;
	Enemy(const Enemy&) = delete;
	
	void StartBattle(){}

	void Draw(IRender& render) override;

	string GetTypeName() const override { return "Enemy"; }


	
	weak_ptr<stack< WorldField* > > MovingPath();
private:

	// smjer u koji gleda neprijatelj
	EnemyViewDirection _viewDirection;

	// sansa da ce neprijatelj krenuti u lov ili u bezanje
	float _courage = 1.f;

	shared_ptr<stack< WorldField* > > _movingPath;
};
