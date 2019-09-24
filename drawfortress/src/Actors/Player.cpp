#include "Player.h"
#include <windows.h>
#include "Input/ConsoleInputManager.h"
#include "Game.h"
#include "World/World.h"
#include "MovingSystem.h"
#include "Render/Render.h"

Player::Player(ISerializer& serializer) : Actor(serializer)
{
	_onKeyDown = std::make_shared<ConsoleInputHandler<Player>>(
	ConsoleInput::Type::KeyDown, 
	this, [&](const ConsoleInput* ev)
	{
		const auto e = reinterpret_cast<const ConsoleInput*>(ev);

		switch(e->virtualKey)
		{
			case 'W': case VK_UP:
				MovePlayer({_position.x, _position.y - 1});
				break;
			case 'D': case VK_RIGHT:
				MovePlayer({_position.x + 1, _position.y});
				break;
			case 'S': case VK_DOWN:
				MovePlayer({_position.x, _position.y + 1});
				break;
			case 'A': case VK_LEFT:
				MovePlayer({_position.x - 1, _position.y});
				break;
			default:
				break;
		}
	});

	ConsoleInputManager::Instance().AddEventHandler(_onKeyDown);
}



void Player::Draw(IRender& render)
{
	render.Draw(_position, Color::Green, 'O');
}

void Player::MovePlayer(Vector2di place)
{
	World& world = Game::Instance().GetWorld();
	
	WorldField* nextField = world.GetField(place);

	if(nextField)
	{
		switch(nextField->Type())
		{
			case WorldField::ItemType::Empty:
				nextField->ReplaceItem(this);
				_position = place;
				break;
			
			case WorldField::ItemType::Actor:
				break;
			
			case WorldField::ItemType::InventoryItem:
				_inventory->PushItem(*nextField->GetInventoryItem());
				nextField->ReplaceItem(this);
				_position = place;
				break;
			
			case WorldField::ItemType::StaticItem:
				break;
			
		}
	}
	MovingSystem::Update();
	//Render::Instance().Clear();
	Game::Instance().Draw();
}

Vector2di Player::GetPosition() const
{
	return _position;
}

Vector2di& Player::Position()
{
	return _position;
}
