#pragma once

#include "Common.h"
#include "Serializable.h"



class ISerializer
{
public:
	virtual ~ISerializer() = default;

	virtual bool SerializeIntT  (Serializable& object, string key, int_t&  value) = 0;

	virtual bool SerializeString(Serializable& object, string key, string& value) = 0;

	virtual bool SerializeBool  (Serializable& object, string key, bool&   value) = 0;

	virtual bool SerializeFloat (Serializable& object, string key, float&  value) = 0;

	virtual bool Save(string path) = 0;

	virtual bool Load(string path) = 0;
};