#pragma once

#include "Common.h"


class Entity
{
public:
	Entity() : id(GenerateId()){}

	Entity(Entity&&) = default;

	Entity(const Entity&) = delete;

	~Entity() = default;

	Entity& operator = (Entity&&) = delete;
	Entity& operator = (const Entity&) = delete;
	
	explicit Entity(const ID id) : id(id){}

	const ID id;
	
private:
	static ID GenerateId()
	{
		static const auto baseId = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		static long long  lastId = 0;
		
		return { baseId, ++lastId};
	}
};