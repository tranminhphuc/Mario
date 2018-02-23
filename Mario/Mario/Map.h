#pragma once

#ifndef _MAP
#define _MAP

#include <fstream>
#include "Object.h"
#include "TileSet.h"
#include "Player.h"
#include "Mushroom.h"
#include "Flower.h"
#include "Star.h"
#include "Goombas.h"
#include "Koopa.h"
#include "Bowser.h"
#include "Toad.h"
#include "Squid.h"
#include "Cheep.h"
#include "Hammer.h"
#include "HammerBro.h"
#include "Lakito.h"
#include "Spikey.h"
#include "Vine.h"
#include "Fire.h"
#include "FireBall.h"

class Map
{
public:
	enum MapType
	{
		BanNgay, // 0
		HoangHon,
		BuoiToi, // 4
		BinhMinh,
		LongDat, // 1
		NuiLua, //3
		Bien, // 2
		Ho, // 7
		ThienDuong, // 5
		DiaNguc // 6
	};
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
private:
	vector<Object*> listBlock;
	vector<vector<TileSet*>> tile;

	vector<Object*> listMinion;
	vector<vector<Minion*>> minion;

	MapType mapType;
	Level level;

	Player* player;

	vector<string*> sourceMinion;

	vector<string*> sourceBlock;

	int mapWidth;
	int mapHeight;
	int mapTime;

	int xMap;
	int yMap;

	bool underWater;
	bool moveMap;

	void LoadImage(string file, vector<Object*>& object);
	void LoadFile(vector<string*> source, vector<Object*>& object);

	void Load(vector<string*>& source, string file, string link);

	void LoadSource();
	void LoadGameData();
	void LoadLevel();
	void CreateMap();
	void ClearMap();
	void ClearMinion();
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

	void LoadMinionLevel_1_1();
	void LoadMinionLevel_1_2();
	void LoadMinionLevel_1_3();
	void LoadMinionLevel_1_4();
	void LoadMinionLevel_2_1();
	void LoadMinionLevel_2_2();
	void LoadMinionLevel_2_3();
	void LoadMinionLevel_2_4();
	void LoadMinionLevel_3_1();
	void LoadMinionLevel_3_2();
	void LoadMinionLevel_3_3();
	void LoadMinionLevel_3_4();
	void LoadMinionLevel_4_1();
	void LoadMinionLevel_4_2();
	void LoadMinionLevel_4_3();
	void LoadMinionLevel_4_4();
	void LoadMinionLevel_5_1();
	void LoadMinionLevel_5_2();
	void LoadMinionLevel_5_3();
	void LoadMinionLevel_5_4();
	void LoadMinionLevel_6_1();
	void LoadMinionLevel_6_2();
	void LoadMinionLevel_6_3();
	void LoadMinionLevel_6_4();
	void LoadMinionLevel_7_1();
	void LoadMinionLevel_7_2();
	void LoadMinionLevel_7_3();
	void LoadMinionLevel_7_4();
	void LoadMinionLevel_8_1();
	void LoadMinionLevel_8_2();
	void LoadMinionLevel_8_3();
	void LoadMinionLevel_8_4();

	void AddGoombas(int x, int y, bool moveDirection);
	void AddKoppa(int x, int y, int minionState, bool moveDirection);
	void AddBowser(int x, int y, bool spawnHammer = false);
	void AddToad(int x, int y, bool peach);
	void AddSquid(int x, int y);
	void AddCheep(int x, int y, int minionType, int moveSpeed, bool moveDirection = false);
	void AddCheepSpawner(int x, int xEnd);
	void AddHammerBro(int x, int y);
	void AddHammer(int x, int y, bool moveDirection);
	void AddLakito(int x, int y, int maxX);
	void AddSpikey(int x, int y);

	void AddVine(int x, int y, int id, int minionState);

	void AddFire(float x, float y, int toY);
	void AddFireBall(int x, int y, int width, int id, bool left);

	void AddBubble(int x, int y);
	void AddBulletBillSpawner(int x, int y, int minionState);
	void AddBulletBill(int x, int y, int minionState, bool moveDirection);

	void DrawGND(int x, int y, int width, int height);
	void DrawGND2(int x, int y, int width, int height);
	void DrawGND2(int x, int y, int size, bool direction);
	void DrawBrick(int x, int y, int width, int height);
	void DrawBlockQ(int x, int y, int width);
	void DrawBlockQ2(int x, int y, int width);
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
	void DrawBonusEnd(int x);
	void DrawSeeSaw(int x, int y, int width);
	void DrawBulletBill(int x, int y, int height);
	void DrawPlatformLine(int x);

	int GetStartMap();
	int GetEndMap();

	int GetListID(int x);
public:
	Map();
	~Map();

	void Update();
	void UpdatePlayer();
	void UpdateBlock();
	void UpdateMinion();
	void UpdateMinionsCollision();

	void Draw(sf::RenderWindow& window);
	void DrawMap(sf::RenderWindow& window);
	void DrawMinion(sf::RenderWindow& window);
	void DrawGameLayout(sf::RenderWindow& window);

	void MoveMap(int x);
	void SetBackGroundColor(sf::RenderWindow& window);
	void SetBackGroundColor(sf::RenderWindow& window, int r, int g, int b, int a);

	void ResetGameData();

	int GetX();
	void SetX(int x);
	int GetY();
	void SetY(int y);

	int GetWidth();
	int GetHeight();

	bool CheckObject(int x, int y);

	int GetMapType();
	void SetMapType(MapType mapType);

	int GetMapTime();
	void SetMapTime(int time);

	bool GetMoveMap();
	void SetMoveMap(bool moveMap);
	
	bool GetUnderWater();
	void SetUnderWater(bool underWater);

	void SetLevel(int level);

	string GetLevelName();

	Player* GetPlayer();

	void Destroy(int x, int y, int id, int direction);
	void PlayerDeath();

	Object* GetObject(int id);
	TileSet* GetTile(int x, int y);
	sf::Vector2i getTilePosition(int x, int y);
};

#endif

