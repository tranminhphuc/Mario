#pragma once

#ifndef _OBJECT
#define _OBJECT

class Object
{
private:
	int id;
public:
	Object(int objectID);
	~Object();
	void SetID(int objectID);
	int GetID();
};

#endif
