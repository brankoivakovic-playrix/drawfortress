#include "Serializable.h"
#include "ISerializer.h"


Serializable::Serializable(ISerializer& serializer) : _serializer(serializer)
{

}
