#include "MovingSystem.h"
#include "Player.h"
#include "Game.h"
#include "World/World.h"

std::mutex g_movingSystemLock;



map<ID, tuple<weak_ptr<Enemy>, MovingComponent> > _components;


void MovingSystem::Update()
{
	//const Player& player = Game::Instance().GetWorld().GetPlayer();

	//World& world = Game::Instance().GetWorld();



	for(auto it = _components.begin(); it != _components.end(); ++it)
	{
		weak_ptr<Enemy> enemyWeakPtr = get<0>(it->second);

		if(enemyWeakPtr.expired())
		{
			_components.erase(it);
			//--it;
			continue;
		}

		auto& enemy = *enemyWeakPtr.lock().get();

		if(!enemy.field)
		{
			continue;
		}
		
		MovingComponent& movingComp  = get<1>(it->second);

		

		switch (movingComp.movingType)
		{
			case MovingType::Static:
				break;
			
			case MovingType::MovingAround:
				{
					auto movingPathWeakPtr = enemy.MovingPath();
					
					if(!movingPathWeakPtr.expired())
					{
						shared_ptr<stack<WorldField*>> movingPathPtr = movingPathWeakPtr.lock();
						
						WorldField* nextField = movingPathPtr->top();
						
						if(nextField->Type() != WorldField::ItemType::Actor)
						{
							if(nextField->Type() == WorldField::ItemType::InventoryItem)
							{
								enemy.AddInventoryItem(*nextField->GetInventoryItem());
							}
							
							nextField->ReplaceItem(&enemy);
							
							movingComp.position = nextField->GetPlace();
							
							movingPathPtr->pop();
						}
						else
						{
							if(auto* enemy2 = dynamic_cast<Enemy*>(nextField->GetActor()))
							{
								auto movingPathWeakPtr2 = enemy2->MovingPath();
								if(!movingPathWeakPtr2.expired())
								{
									shared_ptr<stack<WorldField*>> movingPathPtr2 = movingPathWeakPtr2.lock();

									WorldField* field2 = movingPathPtr2->top();
									
									if(field2 == enemy.field)
									{
										nextField->SwapItem(enemy.field);

										movingComp.position = nextField->GetPlace();
										get<1>(_components[enemy2->id]).position = field2->GetPlace();
										
										movingPathPtr->pop();
										movingPathPtr2->pop();
									}
									else
									{
										movingPathPtr->pop();
									}
								}
							}
						}
					}
				}
				break;
			
			case MovingType::Hunting:
				break;
			
			case MovingType::Escaping:
				break;
		}
	}
}

MovingComponent& MovingSystem::Get(const Enemy& key)
{
	return get<1>(_components[key.id]);
}

MovingComponent* MovingSystem::RegisterEnemy(weak_ptr<Enemy> enemy)
{
	if(!enemy.expired())
	{
		const shared_ptr<Enemy> enemyPtr = enemy.lock();
		_components[enemyPtr->id] = { enemy, MovingComponent() };
		return &Get(  *enemyPtr.get()  );
	}
	return nullptr;
}


