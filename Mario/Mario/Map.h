#pragma once

#ifndef _MAP
#define _MAP

#include "Object.h"
#include "TileSet.h"

class Map
{
private:
	vector<Object*> listBlock;
	vector<vector<TileSet*>> tile;

	enum MapType
	{
		NgoaiTroiBanNgay, // 0
		NgoaiTroiBuoiTrua,
		NgoaiTroiBanDem, // 4
		NgoaiTroiNuaDem,
		LongDat, // 1
		NuiLua, //3
		Bien, // 2
		Ho, // 7
		ThienDuong, // 5
		DiaNguc // 6
	};
	MapType mapType;

	enum Level
	{
		Level_1_1,
		Level_1_2,
		Level_1_3,
		Level_1_4,
		Level_2_1,
		Level_2_2,
		Level_2_3,
		Level_2_4,
		Level_3_1,
		Level_3_2,
		Level_3_3,
		Level_3_4,
		Level_4_1,
		Level_4_2,
		Level_4_3,
		Level_4_4,
		Level_5_1,
		Level_5_2,
		Level_5_3,
		Level_5_4,
		Level_6_1,
		Level_6_2,
		Level_6_3,
		Level_6_4,
		Level_7_1,
		Level_7_2,
		Level_7_3,
		Level_7_4,
		Level_8_1,
		Level_8_2,
		Level_8_3,
		Level_8_4
	};
	Level level;

	int mapWidth;
	int mapHeight;
	int mapTime;
	float xMap;
	float yMap;
	bool underWater;

	void LoadImage(string image, bool collision = true);
	void LoadImage(string image1, string image2, string image3, string image4, bool collision = true);
	void LoadImage(string image1, string image2, string image3, bool collision = true);
	void LoadGameData();
	void LoadLevel();
	void CreateMap();
	void ClearMap();
	void SetTileID(int x, int y, int id);

	void LoadLevel_1_1();
	void LoadLevel_1_2();
	void LoadLevel_1_3();
	void LoadLevel_1_4();
	void LoadLevel_2_1();
	void LoadLevel_2_2();
	void LoadLevel_2_3();
	void LoadLevel_2_4();
	void LoadLevel_3_1();
	void LoadLevel_3_2();
	void LoadLevel_3_3();
	void LoadLevel_3_4();
	void LoadLevel_4_1();
	void LoadLevel_4_2();
	void LoadLevel_4_3();
	void LoadLevel_4_4();
	void LoadLevel_5_1();
	void LoadLevel_5_2();
	void LoadLevel_5_3();
	void LoadLevel_5_4();
	void LoadLevel_6_1();
	void LoadLevel_6_2();
	void LoadLevel_6_3();
	void LoadLevel_6_4();
	void LoadLevel_7_1();
	void LoadLevel_7_2();
	void LoadLevel_7_3();
	void LoadLevel_7_4();
	void LoadLevel_8_1();
	void LoadLevel_8_2();
	void LoadLevel_8_3();
	void LoadLevel_8_4();

	void DrawGND(int x, int y, int width, int height);
	void DrawGND2(int x, int y, int width, int height);
	void DrawGND2(int x, int y, int size, bool direction);
	void DrawBrick(int x, int y, int width, int height);
	void DrawBlockQ(int x, int y, int width);
	void DrawPipe(int x, int y, int height);
	void DrawPipeHorizontal(int x, int y, int width);
	void DrawPipeVertical(int x, int y, int height);
	void DrawCoins(int x, int y, int width, int height);
	void DrawEnd(int x, int y, int height);
	void DrawCastleSmall(int x, int y);
	void DrawCastleBig(int x, int y);
	void DrawCastleWall(int x, int y, int width, int height);
	void DrawT(int x, int y, int width, int height);
	void DrawTMush(int x, int y, int width, int height);
	void DrawWater(int x, int y, int width, int height);
	void DrawLava(int x, int y, int width, int height);
	void DrawBridge(int x, int y, int width);
	void DrawBridge2(int x, int y, int width);
	void DrawBonus(int x, int y, int width);

	int GetStartMap();
	int GetEndMap();
public:
	Map();
	~Map();
	void Update(float time);

	void Draw(sf::RenderWindow& window);
	void DrawMap(sf::RenderWindow& window);

	void MoveMap(int x);
	void SetBackGroundColor(sf::RenderWindow& window);

	float GetX();
	void SetX(float x);
	float GetY();
	void SetY(float y);

	int GetWidth();
	int GetHeight();

	bool CheckObject(int x, int y);

	int GetMapType();
	void SetMapType(MapType mapType);

	int GetMapTime();
	void SetMapTime(int time);
	
	bool GetUnderWater();
	void SetUnderWater(bool underWater);

	Object* GetObject(int id);
	TileSet* GetTile(int x, int y);
	sf::Vector2i getTilePosition(int x, int y);
};

#endif

