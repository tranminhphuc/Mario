#pragma once

#ifndef _MAP
#define _MAP

#include "Library.h"
#include "Animation.h"
#include "Object.h"

class Map
{
private:
	vector<Animation*> listBlock;
	vector<vector<Object*>> listObject;

	enum MapType
	{
		NgoaiTroiBanNgay, // 0
		NgoaiTroiBanDem, // 4
		LongDat, // 1
		NuiLua, //3
		Bien, // 2
		Ho, // 7
		ThienDuong, // 5
		DiaNguc // 6
	};
	MapType maptype;

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
	float Xmap;
	float Ymap;


	void LoadGameData();
	void LoadLevel();
	void CreateMap();
	void ClearMap();

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
	void DrawPiPe(int x, int y, int height);
	void DrawPiPeHorizontal(int x, int y, int width);
	void DrawPiPeVertical(int x, int y, int height);
	void DrawCoin(int x, int y, int width, int height);
	void DrawEnd(int x, int y, int height);
	void DrawCastleSmall(int x, int y);
	void DrawCastleBig(int x, int y);
	void DrawCastleWall(int x, int y, int width, int height);

	int GetStartMap();
	int GetEndMap();
public:
	Map();
	~Map();
	void Update(float time);
	void Draw(RenderWindow& window);
	void DrawMap(RenderWindow& window);
	void MoveMap(int x);
	void SetBackGroundColor(RenderWindow& window);
};

#endif

