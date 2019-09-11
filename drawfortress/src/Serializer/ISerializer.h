#pragma once

#include "Common.h"

class ISerializable;

class ISerializer
{
public:
	virtual bool SerializeObject(std::string Key, ISerializable& Value) = 0;

	virtual bool SerializeString(std::string Key, std::string& Value) = 0;

	virtual bool SerializeBool(std::string Key, bool& Value) = 0;
};