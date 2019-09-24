#include "Serializer.h"
#include <fstream>



bool Serializer::SerializeIntT(Serializable& object, string key, int_t& value)
{
	_data[object.GetTypeName()][object.GetId()][key] = { VarType::IntT, &value };
	return true;
}

bool Serializer::SerializeString(Serializable& object, string key, string& value)
{
	_data[object.GetTypeName()][object.GetId()][key] = { VarType::String, &value };
	return true;
}

bool Serializer::SerializeBool(Serializable& object, string key, bool& value)
{
	_data[object.GetTypeName()][object.GetId()][key] = { VarType::Bool, &value };
	return true;
}

bool Serializer::SerializeFloat(Serializable& object, string key, float& value)
{
	_data[object.GetTypeName()][object.GetId()][key] = { VarType::Float, &value };
	return true;
}

bool Serializer::Save(string path)
{
	fstream file(path, ios::out | ios::trunc);

	file << "{" << endl;
	
	for(auto& objectByName : _data)
	{
		file << "  " << objectByName.first << "  : [ " << endl;
		
		for(auto& object : objectByName.second)
		{
			file << " ID : [" << get<0>(object.first) << ", " << get<1>(object.first) << " ]," << endl;

			for(auto& var : object.second)
			{
				file << get<0>(var) << " : " << get<0>(var) << "," << endl;
			}
		}

		file << "  ]" << endl;
	}

	file << "}" << endl;

	return true;
}

bool Serializer::Load(string path)
{
	return false;
}
