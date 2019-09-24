#pragma once
#include "Common.h"
#include "Actor.h"

#include "Input/ConsoleInputHandler.h"


class Player : public Actor
{
public:
	Player(ISerializer& serializer);

	void Draw(IRender& render) override;

	void MovePlayer(Vector2di place);

	Vector2di GetPosition() const;

	Vector2di& Position();

	string  GetTypeName() const override { return "Player"; }
	
private:

	Vector2di _position;

	std::shared_ptr<ConsoleInputHandler<Player>> _onKeyDown;
};
