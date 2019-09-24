#include "World.h"

#include  "Actors/MovingSystem.h"



World::World(Vector2di size, ISerializer& serializer) : Serializable(serializer),
	_size   ( size ),
	_fields ( new WorldField[ size.x * size.y ] ),
	_player ( new Player( serializer )  )
{

#ifdef _DEBUG
	for(auto y = 0; y < _size.y; y++)
	{
		for(auto x = 0; x < _size.x; x++)
		{
			auto& field = _fields[y * _size.x + x];
			field.x = x;
			field.y = y;
		}
	}
#endif
	
	_fields[3 + 3 * _size.x].ReplaceItem(_player.get());
	_player->Position() = {3, 3};

	for(auto i = 0; i < _size.x; ++i)
	{
		_fields[i].SetStaticItem();
		_fields[i + _size.x * (_size.y - 1)].SetStaticItem();
	}

	for(auto i = 0; i < _size.y; ++i)
	{
		_fields[i * _size.x].SetStaticItem();
		_fields[(_size.x - 1) + i * _size.x].SetStaticItem();
	}
	
	Rand rand;
	
	for(int_t i = 0; i < 30; i++)
	{
		CreateEnemy({rand() % _size.x, rand() % _size.y});
	}
}

void World::Draw(IRender&  render)
{

	const auto playerPos = _player->GetPosition();
	const auto viewSize  = render.GetViewSize();
	const auto maxOffset = viewSize / 3;
	
	Vector2di cameraPos = render.GetCameraPos();
	
	if(playerPos.x - cameraPos.x < maxOffset.x)
	{
		cameraPos.x = (playerPos.x - maxOffset.x);
	}
	else if(playerPos.x - cameraPos.x >= viewSize.x - maxOffset.x)
	{
		cameraPos.x = playerPos.x - (viewSize.x - maxOffset.x);
	}

	if(playerPos.y - cameraPos.y < maxOffset.y)
	{
		cameraPos.y = (playerPos.y - maxOffset.y);
	}
	else if(playerPos.y - cameraPos.y >= viewSize.y - maxOffset.y)
	{
		cameraPos.y = playerPos.y - (viewSize.y - maxOffset.y);
	}
	
	render.CameraPos(cameraPos);
	_player->Draw(render);
	
	for(auto& enemy : _enemies)
	{
		enemy->Draw(render);
	}

	for(auto x = 0; x < _size.x; ++x)
	{
		for(auto y = 0; y < _size.y; ++y)
		{
			auto& field = _fields[x + y * _size.x];
			if(field.Type() == WorldField::ItemType::StaticItem)
			{
				render.Draw(GetFieldPlace(field), Color::White, '#');
			}
		}
	}
}

void World::Update(time_span delta)
{
	
}

const Player& World::GetPlayer() const
{
	return *_player.get();
}

auto World::GetField(Vector2di place) const -> WorldField*
{
	if(place.x >= 0 && place.y >= 0 && place.x < _size.x && place.y < _size.y)
	{
		return &_fields[place.y * _size.x + place.x];
	}
	return nullptr;
}

void World::FindMovingPath(stack< WorldField* >& out, Vector2di start, Vector2di target, int_t radius) const
{
	
	static stack<PathFinderItem> rowPath;
	static queue<PathFinderItem> buffer;

	auto offsetX = start.x - (radius * 2 - abs(start.x - target.x)) / 2;
	auto offsetY = start.y - (radius * 2 - abs(start.y - target.y)) / 2;

	auto width  = radius * 2;
	auto height = radius * 2;

	if(offsetX < 0)
	{
		offsetX = 0;
	}
	if(width + offsetX > _size.x)
	{
		width =  _size.x - offsetX;
	}
	
	if(offsetY < 0)
	{
		offsetY = 0;
	}
	if(height + offsetY > _size.y)
	{
		height =  _size.y - offsetY;
	}
	
	const auto startX = start.x - offsetX;
	const auto startY = start.y - offsetY;

	const auto targetX = target.x - offsetX;
	const auto targetY = target.y - offsetY;
	
	const auto fieldsCount = width * height;
	
	const unique_ptr<bool[]> isVisited(new bool[fieldsCount]);
	
	const unique_ptr<WorldField*[]> fields(new WorldField*[fieldsCount]);
	
	
	for(int_t x = width - 1; x >= 0; --x)
	{
		for(int_t y = height - 1; y >= 0; --y)
		{
			auto& field = _fields[offsetX + x + (offsetY + y) * _size.x];

			fields[x + y * width] = &field;
			
			if(field.Type() == WorldField::ItemType::StaticItem)
			{
				isVisited[x + y * width] = true;
			}
			else
			{
				isVisited[x + y * width] = false;
			}
		}
	}

	isVisited[start.x - offsetX + (start.y - offsetY) * width] = true;


	buffer.push({startX, startY, 0,  fields[startX + startY * + width], nullptr});

	
	
	while(!buffer.empty())
	{
		auto p(buffer.front());

		rowPath.push(p);
		
		buffer.pop();

		if(p.x == targetX && p.y == targetY)
		{
			const PathFinderItem* item = &rowPath.top();


			for( ; item->parent ; item = item->parent)
			{
				out.push(item->field);
			}
			
			break;
		}

		auto x = p.x;
		auto y = p.y - 1;

		if(y >= 0 && !isVisited[y * width + x])
		{
			buffer.push({x,y, p.distance + 1, fields[x + y  * width], &rowPath.top()});
			isVisited[x + y  * width] = true;
		}

		y += 2;
		if(y < height && !isVisited[x + y  * width])
		{
			buffer.push({x,y, p.distance + 1, fields[x + y  * width], &rowPath.top()});
			isVisited[x + y  * width] = true;
		}

		--x;
		--y;
		if(x >= 0 && !isVisited[x + y  * width])
		{
			buffer.push({x,y, p.distance + 1, fields[x + y  * width], &rowPath.top()});
			isVisited[x + y  * width] = true;
		}

		x += 2;
		if(x < width && !isVisited[x + y  * width])
		{
			buffer.push({x,y, p.distance + 1, fields[x + y  * width], &rowPath.top()});
			isVisited[x + y  * width] = true;
		}
	}
	while(!rowPath.empty())
		rowPath.pop();

	while(!buffer.empty())
		buffer.pop();

	
}

auto World::GetFieldPlace(const WorldField& field) const -> Vector2di
{
	const auto* firstFieldAddress = &(_fields[0]);
	const int_t fieldIndex =  &field - firstFieldAddress;
	
	return { fieldIndex % _size.x, fieldIndex / _size.x };
}

auto World::CreateEnemy(Vector2di place) ->weak_ptr<Enemy>
{
	if(auto* field = GetField(place))
	{
		if(field->Type() != WorldField::ItemType::Empty)
		{
			return weak_ptr<Enemy>();
		}
		
		const auto enemy = make_shared<Enemy>(_serializer);
		
		auto* movingComponent = MovingSystem::RegisterEnemy(enemy);

		movingComponent->position  = place;
		movingComponent->homePoint = place;

		_enemies.push_back(enemy);

		field->ReplaceItem(enemy.get());

		return enemy;
	}
	return weak_ptr<Enemy>();
}

auto World::CreateInventoryItem(InventoryItem::Type type, Vector2di place) -> weak_ptr<InventoryItem>
{
	return weak_ptr<InventoryItem>();
}
