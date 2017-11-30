#include "Object.h"

Object::Object(int objectID)
{
	id = objectID;
}

Object::~Object()
{

}

void Object::SetID(int objectID)
{
	id = objectID;
}

int Object::GetID()
{
	return id;
}
