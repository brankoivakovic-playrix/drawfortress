#pragma once

#include "Common.h"

#include "Serializer/ISerializable.h"
#include "WorldField.h"


class World : public ISerializable
{
public:
	virtual bool Serialize(ISerializer& serilizer) override;

	void Update();

private:

	std::vector<WorldField> _fields;

	size_t _width;
	size_t _height;
};