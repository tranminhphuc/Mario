#pragma once

#ifndef _TILESET
#define _TILESET

class TileSet
{
private:
	int id;
public:
	TileSet(int tileID);
	~TileSet();
	void SetID(int tileID);
	int GetID();
};

#endif
