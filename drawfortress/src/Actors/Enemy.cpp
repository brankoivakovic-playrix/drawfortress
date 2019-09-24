#include "Enemy.h"
#include "MovingSystem.h"
#include "Game.h"
#include "World/World.h"


Enemy::Enemy(ISerializer& serializer) : Actor(serializer)
{
}

void Enemy::Draw(IRender& render)
{
	const auto& comp = MovingSystem::Get(*this);

	render.Draw(comp.position, Color::Red, 'O');
}

weak_ptr<stack< WorldField* > > Enemy::MovingPath()
{
	if(!_movingPath)
	{
		_movingPath = make_shared< stack< WorldField* > >();
	}
	
	if(!_movingPath || _movingPath->empty())
	{
		static default_random_engine rand;
		
		const MovingComponent& comp = MovingSystem::Get(*this);
		
		while(true)
		{
			const int_t x = rand() % comp.movingRadius + comp.homePoint.x;
			const int_t y = rand() % comp.movingRadius + comp.homePoint.y;

			const WorldField* targetField = Game::Instance().GetWorld().GetField({x, y});

			if(targetField && targetField->Type() != WorldField::ItemType::StaticItem)
			{
				Game::Instance().GetWorld().FindMovingPath(*_movingPath.get(), field->GetPlace(), targetField->GetPlace(), comp.movingRadius);
				
				if(_movingPath && !_movingPath->empty())
				{
					break;
				}
			}
		}
	}
	return _movingPath;
}