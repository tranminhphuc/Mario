#include "TileSet.h"

TileSet::TileSet(int tileID)
{
	id = tileID;
}

TileSet::~TileSet()
{
}

void TileSet::SetID(int tileID)
{
	id = tileID;
}

int TileSet::GetID()
{
	return id;
}
