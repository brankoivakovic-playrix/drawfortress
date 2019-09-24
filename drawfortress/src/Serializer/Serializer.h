#pragma once

#include "Common.h"

#include "ISerializer.h"

#include <fstream>


class Serializer final : public ISerializer
{
public:
	Serializer() = default;
	

	Serializer(const Serializer& ) = delete;
	Serializer(      Serializer&&) = delete;
	
	Serializer& operator = (const Serializer& ) = delete;
	Serializer& operator = (      Serializer&&) = delete;


	bool SerializeIntT  (Serializable& object, string key, int_t&  value) override;
	
	bool SerializeString(Serializable& object, string key, string& value) override;
	
	bool SerializeBool  (Serializable& object, string key, bool&   value) override;
	
	bool SerializeFloat (Serializable& object, string key, float&  value) override;
	
	bool Save(string path) override;
	
	bool Load(string path) override;
	
private:
	enum class VarType
	{
		Bool,
		IntT,
		String,
		Float,
	};

	
	using var         = tuple< VarType, void*>;
	using object_data = map<string, var >;
	using objects     = map<ID, object_data>;
	using object_name = string;
	
	map<object_name, objects> _data;
};
