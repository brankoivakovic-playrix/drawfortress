#pragma once

#include "Common.h"

class ISerializer;

class Serializable
{
public:
	Serializable(ISerializer& serializer);
	
	virtual ~Serializable() = default;

	virtual  ID    GetId       () const = 0;

	virtual  string GetTypeName() const = 0;
	
protected:
	ISerializer& _serializer;
};
