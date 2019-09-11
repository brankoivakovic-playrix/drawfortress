#pragma once

#include "ISerializer.h"



class ISerializable
{
public:
	virtual bool Serialize(ISerializer& serilizer) = 0;

private:
	size_t _id;
};
