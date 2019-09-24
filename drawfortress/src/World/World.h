#pragma once

#include "Common.h"

#include "Serializer/Serializable.h"
#include "WorldField.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"


class World final : public Serializable, public IRenderable, public Entity
{
public:	
	explicit World(Vector2di size, ISerializer& serializer);

	World(             ) = delete;
	World(const World& ) = delete;
	World(      World&&) = delete;

	~World() = default;

	World& operator = (const World& ) = delete;
	World& operator = (      World&&) = delete;



	auto GetId() const -> ID override { return id; }

	auto GetTypeName() const -> string override { return "World"; };
	
	void Draw(IRender& render) override;

	void Update(time_span delta);

	auto GetPlayer() const ->const Player&;

	auto GetField(Vector2di place) const ->WorldField*;

	void FindMovingPath(stack< WorldField* >& out, Vector2di start, Vector2di target, int_t radius) const;

	auto GetFieldPlace(const WorldField& field) const -> Vector2di;

	auto CreateEnemy(Vector2di place) -> weak_ptr<Enemy>;

	auto CreateInventoryItem(InventoryItem::Type type, Vector2di place) -> weak_ptr<InventoryItem>;
	
private:
	const Vector2di _size;
	
	unique_ptr< WorldField[] > _fields;
	
	list< shared_ptr<Enemy> >  _enemies;

	unique_ptr< Player >       _player;
};
