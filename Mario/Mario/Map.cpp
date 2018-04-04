#include "Map.h"
#include "Windows.h"

Map::Map()
{
	player = new Player(84, 384);

	xMap = 0;
	yMap = 0;
	mapType = BanNgay;
	level = Level_1_1;

	Window::GetText()->SetFont("Source/images/font.bmp");

	LoadSource();
	LoadGameData();
	LoadLevel();
}

Map::~Map() { }

void Map::Update()
{
	UpdateBlock();
	UpdateMinion();
	UpdatePlayer();
}

void Map::UpdatePlayer()
{
	player->Update();
}

void Map::UpdateBlock()
{
	listBlock[13]->GetAnimation()->Update();
	listBlock[15]->GetAnimation()->Update();
	listBlock[70]->GetAnimation()->Update();
	listBlock[71]->GetAnimation()->Update();
	listBlock[72]->GetAnimation()->Update();
}

void Map::UpdateMinion()
{
	for (int i = 0; i < minion.size(); i++)
	{
		for (int j = 0; j < minion[i].size(); j++)
		{
			if (minion[i][j]->UpdateMinion())
				minion[i][j]->Update();
		}
	}

	for (int i = 0; i < minion.size(); i++)
	{
		for (int j = 0; j < minion[i].size(); i++)
		{
			if (minion[i][j]->minionSpawned)
			{
				if (minion[i][j]->minionState == -1)
				{
					delete minion[i][j];
					minion[i].erase(minion[i].begin() + j);
					continue;
				}

				if (floor(minion[i][j]->xMinion / 160) != i)
				{
					//minion[floor(minion[i][j]->xMinion / 160)].push_back(minion[i][j]);
					//minion[i].erase(minion[i].begin() + j);
				}
			}
		}
	}
}

void Map::UpdateMinionsCollision()
{
	for (int i = 0; i < minion.size(); i++)
	{
		for (int j = 0; j < minion[i].size(); i++)
		{
			for (int k = j + 1; k < minion[i].size(); k++)
			{
				if (!minion[i][k]->collisionOnlyWithPlayer && minion[i][k]->deadTime < 0)
				{
					if (minion[i][j]->GetX() < minion[i][k]->GetX())
					{
						if (minion[i][j]->GetX() + minion[i][i]->width >= minion[i][k]->GetX() && minion[i][j]->GetX() + minion[i][j]->width <= minion[i][k]->GetX() + minion[i][k]->width && (minion[i][j]->GetY() <= minion[i][k]->GetY() + minion[i][k]->height && minion[i][j]->GetY() + minion[i][j]->height >= minion[i][k]->GetY() + minion[i][k]->height) || (minion[i][k]->GetY() <= minion[i][j]->GetY() + minion[i][j]->height && minion[i][k]->GetY() + minion[i][k]->height >= minion[i][j]->GetY() + minion[i][j]->height))
						{

						}
					}
				}
			}
		}
	}
}

void Map::Draw(sf::RenderWindow& window)
{
	DrawMap(window);
	DrawMinion(window);

	player->Draw(window);
}

void Map::DrawMap(sf::RenderWindow & window)
{
	SetBackGroundColor(window);

	for (int i = GetStartMap(), iEnd = GetEndMap(); i < iEnd && i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if (tile[i][j]->GetID() != 0)
			{
				listBlock[tile[i][j]->GetID()]->Draw(window, sf::Vector2f(32.0f * i + xMap, j * 32.0f));
			}
		}
	}
}

void Map::DrawMinion(sf::RenderWindow& window)
{
	for (int i = 0; i < minion.size(); i++)
	{
		for (int j = 0; j < minion[i].size(); j++)
		{
			minion[i][j]->Draw(window, listMinion[minion[i][j]->GetID()]->GetAnimation()->getTexture());
		}
	}
}

void Map::DrawGameLayout(sf::RenderWindow & window)
{
	Window::GetText()->Draw(window, "MARIO", 54, 16);

	if (player->GetScore() < 100)
		Window::GetText()->Draw(window, "0000" + to_string(player->GetScore()), 54, 32);
	else if(player->GetScore() < 1000)
		Window::GetText()->Draw(window, "000" + to_string(player->GetScore()), 54, 32);
	else if (player->GetScore() < 10000)
		Window::GetText()->Draw(window, "00" + to_string(player->GetScore()), 54, 32);
	else if (player->GetScore() < 100000)
		Window::GetText()->Draw(window, "0" + to_string(player->GetScore()), 54, 32);
	else
		Window::GetText()->Draw(window, to_string(player->GetScore()), 54, 32);

	Window::GetText()->Draw(window, "WORLD", 462, 16);
}

void Map::SetBackGroundColor(sf::RenderWindow & window)
{
	switch (mapType)
	{
	case BanNgay:
		window.clear(sf::Color(93, 148, 252, 255));
		break;
	case BanDem:
		window.clear(sf::Color(0, 0, 0, 255));
		break;
	default:
		window.clear(sf::Color(0, 0, 0, 255));
		break;
	}
}

void Map::SetBackGroundColor(sf::RenderWindow & window, int r, int g, int b, int a)
{
	window.clear(sf::Color(r, g, b, a));
}

void Map::ResetGameData()
{
	level = Level_1_1;

	player->SetCoin(0);
	player->ResetLevel();
	player->SetLive(3);

	LoadLevel();
}

float Map::GetX()
{
	return xMap;
}

void Map::SetX(float x)
{
	this->xMap = x;
}

float Map::GetY()
{
	return yMap;
}

void Map::SetY(float y)
{
	this->yMap = y;
}

int Map::GetWidth()
{
	return mapWidth;
}

int Map::GetHeight()
{
	return mapHeight;
}

bool Map::CheckObject(int x, int y)
{
	if (x < 0 || x >= Window::gameWidth || y < 0 || y >= Window::gameHeight / 32)
	{
		return false;
	}
	else
	{
		TileSet* tileset = GetTile(x, y);
		return listBlock[tileset->GetID()]->GetCollision();
	}
}

int Map::GetMapType()
{
	return mapType;
}

void Map::SetMapType(MapType mapType)
{
	this->mapType = mapType;
}

int Map::GetMapTime()
{
	return mapTime;
}

void Map::SetMapTime(int time)
{
	this->mapTime = time;
}

bool Map::GetMoveMap()
{
	return moveMap;
}

void Map::SetMoveMap(bool moveMap)
{
	this->moveMap = moveMap;
}

bool Map::GetUnderWater()
{
	return underWater;
}

void Map::SetUnderWater(bool underWater)
{
	this->underWater = underWater;
}

sf::Vector2f Map::GetObjectID(int x, int y)
{
	return sf::Vector2f((float)(x < 0 ? 0 : x) / 32, (float)(y > Window::gameHeight ? 0 : Window::gameHeight - y + 32) / 32);
}

int Map::GetObjectX(int x)
{
	return (x < 0 ? 0 : x) / 32;
}

int Map::GetObjectY(int y)
{
	return (y > Window::gameHeight ? 0 : Window::gameHeight - y + 32) / 32;
}

int Map::GetLevel()
{
	return level;
}

void Map::SetLevel(int level)
{
	if (this->level != level)
	{
		this->level = (Level)level;
		LoadLevel();
	}
}

string Map::GetLevelName()
{
	return to_string(level / 4 + 1) + "-" + to_string(level % 4 + 1);
}

Player* Map::GetPlayer()
{
	return player;
}

void Map::CollectItem(int x, int y)
{
	if (tile[x][y]->GetPowerUp())
	{
		if (player->GetLevel() == 0)
			minion[GetListID(32 * x)].push_back(new Mushroom(32 * x, Window::gameHeight - 32 * y, true, x, y));
		else
			minion[GetListID(32 * x)].push_back(new Flower(32 * x, Window::gameHeight - 32 * y, x, y));
	}
	else
	{
		minion[GetListID(32 * x)].push_back(new Mushroom(32 * x, Window::gameHeight - 32 * y, false, x, y));
	}
}

void Map::CollectCoin(int x, int y)
{
	player->CollectCoin();
	tile[x][y]->SetNumberOfCoin(tile[x][y]->getNumberOfCoin() - 1);

	if (tile[x][y]->getNumberOfCoin() == 0)
	{
		tile[x][y]->SetNumberOfCoin(0);
		SetTileID(x, y, mapType == BanNgay ? 14 : 16);
	}
}

bool Map::Destroy(int x, int y, int id, int direction)
{
	if (direction == 0)
	{
		switch (id)
		{
		case 13: case 15:
			if (tile[x][y]->GetMushroom())
				CollectItem(x, y);
			else if (tile[x][y]->getNumberOfCoin() > 0)
				CollectCoin(x, y);
			break;
		case 10: case 11: case 12:
			if (tile[x][y]->GetStar())
			{
				SetTileID(x, y, mapType == BanNgay ? 14 : 17);
				minion[GetListID(32 * x)].push_back(new Star(32 * x, Window::gameHeight - 32 * y, x, y));
			}
			else if (tile[x][y]->GetMushroom())
			{
				SetTileID(x, y, mapType == BanNgay ? 14 : 17);
				CollectItem(x, y);
			}
			else if (tile[x][y]->getNumberOfCoin() > 0)
			{
				CollectCoin(x, y);
			}
			else if (player->GetLevel() > 0)
			{
				SetTileID(x, y, 0);
			}
			break;
		case 117:
			if (tile[x][y]->GetMushroom())
				CollectItem(x, y);
			else
				player->CollectCoin();

			tile[x][y]->SetID(mapType == BanNgay || mapType == BanDem ? 14 : mapType == LongDat ? 16 : 17);
		default:
			break;
		}
	}
	else if (direction == 1)
	{
		/*switch (id)
		{
		default:
			break;
		}*/
	}

	return true;
}

void Map::PlayerDeath()
{
}

Object* Map::GetObject(int id)
{
	return listBlock[id];
}

TileSet* Map::GetTile(int x, int y)
{
	return tile[x][y];
}

sf::Vector2i Map::GetTilePosition(int x, int y)
{
	return sf::Vector2i((int)(x < 0 ? 0 : x), (int)(y > 480 ? 0 : y));
}

void Map::MoveMap(int x)
{
	if (xMap + x > 0)
	{
		player->MoveX((int)(x - xMap));
		xMap = 0;
	}
	else
	{
		xMap += x;
	}
}

void Map::LoadImage(string file, vector<Object*>& object)
{
	bool collision, canDestroy, visible;

	vector<string> name;
	vector<unsigned int> time;

	string text;
	unsigned int delay;

	fstream f;
	f.open(file);

	f >> text >> collision;
	f >> text >> canDestroy;
	f >> text >> visible;

	while(!f.eof())
	{
		f >> text;
		f >> delay;
		name.push_back("Source/images/" + text);
		time.push_back(delay);
	}
	
	f.close();
	object.push_back(new Object(new Animation(name, time), collision, canDestroy, visible));
}

void Map::LoadFile(vector<string*> source, vector<Object*>& object)
{
	for (int i = 0; i < source.size(); i++)
	{
		LoadImage(*source[i], object);
	}
}

void Map::Load(vector<string*>& source, string file, string folder)
{
	fstream f;
	f.open(file);

	string name;

	while (!f.eof())
	{
		string text;
		f >> text;

		f >> name;
		name = folder + name;

		source.push_back(new string(name));
	}

	f.close();
}

void Map::LoadSource()
{
	Load(sourceBlock, "Source/files/fileBlock.txt", "Source/files/blocks/");
	Load(sourceMinion, "Source/files/fileMinion.txt", "Source/files/minions/");
}

void Map::LoadGameData()
{
	LoadFile(sourceBlock, listBlock);
	LoadFile(sourceMinion, listMinion);
}

void Map::LoadLevel()
{
	switch (level)
	{
		case Level_1_1:
			LoadLevel_1_1();
			break;
		case Level_1_2:
			LoadLevel_1_2();
			break;
		case Level_1_3:
			LoadLevel_1_3();
			break;
		case Level_1_4:
			LoadLevel_1_4();
			break;
		case Level_2_1:
			LoadLevel_2_1();
			break;
		case Level_2_2:
			LoadLevel_2_2();
			break;
		case Level_2_3:
			LoadLevel_2_3();
			break;
		case Level_2_4:
			LoadLevel_2_4();
			break;
		case Level_3_1:
			LoadLevel_3_1();
			break;
		case Level_3_2:
			LoadLevel_3_2();
			break;
		case Level_3_3:
			LoadLevel_3_3();
			break;
		case Level_3_4:
			LoadLevel_3_4();
			break;
		case Level_4_1:
			LoadLevel_4_1();
			break;
		case Level_4_2:
			LoadLevel_4_2();
			break;
		case Level_4_3:
			LoadLevel_4_3();
			break;
		case Level_4_4:
			LoadLevel_4_4();
			break;
		case Level_5_1:
			LoadLevel_5_1();
			break;
		case Level_5_2:
			LoadLevel_5_2();
			break;
		case Level_5_3:
			LoadLevel_5_3();
			break;
		case Level_5_4:
			LoadLevel_5_4();
			break;
		case Level_6_1:
			LoadLevel_6_1();
			break;
		case Level_6_2:
			LoadLevel_6_2();
			break;
		case Level_6_3:
			LoadLevel_6_3();
			break;
		case Level_6_4:
			LoadLevel_6_4();
			break;
		case Level_7_1:
			LoadLevel_7_1();
			break;
		case Level_7_2:
			LoadLevel_7_2();
			break;
		case Level_7_3:
			LoadLevel_7_3();
			break;
		case Level_7_4:
			LoadLevel_7_4();
			break;
		case Level_8_1:
			LoadLevel_8_1();
			break;
		case Level_8_2:
			LoadLevel_8_2();
			break;
		case Level_8_3:
			LoadLevel_8_3();
			break;
		case Level_8_4:
			LoadLevel_8_4();
			break;
		default:
			break;
	}
}

void Map::ReadMap(string file)
{
	vector<vector<int>> maps;
	fstream f(file);

	for (int i = 0; i < mapHeight; i++)
	{
		vector<int> a;

		for (int j = 0; j < mapWidth; j++)
		{
			int n;
			f >> n;
			a.push_back(n);
		}

		maps.push_back(a);
	}

	f.close();

	for (int i = 0; i < maps.size(); i++)
	{
		for (int j = 0; j < maps[i].size(); j++)
		{
			if (maps[i][j] != 0)
			{
				SetTileID(j, i, maps[i][j]);
			}
		}
	}
}

void Map::CreateMap()
{
	for (int i = 0; i < mapWidth; i += 5)
	{
		vector<Minion*> object;
		minion.push_back(object);
	}

	for (int i = 0; i < mapWidth; i++)
	{
		vector<TileSet*> object;

		for (int j = 0; j < mapHeight; j++)
		{
			object.push_back(new TileSet(0));
		}

		tile.push_back(object);
	}

	
}

void Map::ClearMap()
{
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			delete tile[i][j];
		}
		tile[i].clear();
	}
	tile.clear();
}

void Map::ClearMinion()
{
	for (int i = 0; i < minion.size(); i++)
	{
		for (int j = 0; j < minion[i].size(); j++)
		{
			delete minion[i][j];
		}
		minion[i].clear();
	}
}

void Map::SetTileID(int x, int y, int id)
{
	if (x >= 0 && x <= mapWidth)
	{
		tile[x][y]->SetID(id);
	}
}

void Map::LoadLevel_1_1()
{
	ClearMap();

	mapWidth = 260;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_1_1();

	ReadMap("Source/maps/Level1_1.map");
	
	tile[21][5]->SetMustroom(true);
	tile[78][9]->SetMustroom(true);
	tile[109][5]->SetMustroom(true);
	tile[78][9]->SetPowerUp(false);

	tile[101][9]->SetStar(true);

	tile[94][9]->SetNumberOfCoin(4);
}

void Map::LoadLevel_1_2()
{
	ClearMap();

	mapWidth = 330;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_1_2();

	ReadMap("Source/maps/Level1_2.map");

	tile[10][9]->SetMustroom(true);
	tile[69][8]->SetMustroom(true);
	tile[89][2]->SetMustroom(true);
	tile[150][8]->SetMustroom(true);
	tile[89][2]->SetPowerUp(false);

	tile[46][7]->SetStar(true);

	tile[29][8]->SetNumberOfCoin(10);
	tile[73][8]->SetNumberOfCoin(8);
	tile[252][9]->SetNumberOfCoin(10);
}

void Map::LoadLevel_1_3()
{
	ClearMap();

	mapWidth = 270;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_1_3();

	ReadMap("Source/maps/Level1_3.map");

	tile[59][10]->SetMustroom(true);
}

void Map::LoadLevel_1_4()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_1_4();

	ReadMap("Source/maps/Level1_4.map");
}

void Map::LoadLevel_2_1()
{
	ClearMap();

	mapWidth = 365;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_2_1();

	ReadMap("Source/maps/Level2_1.map");

	tile[16][9]->SetMustroom(true);
	tile[28][5]->SetMustroom(true);
	tile[53][9]->SetMustroom(true);
	tile[125][5]->SetMustroom(true);
	tile[172][5]->SetMustroom(true);
	tile[28][5]->SetPowerUp(false);

	tile[69][5]->SetStar(true);

	tile[161][9]->SetNumberOfCoin(7);
}

void Map::LoadLevel_2_2()
{
	ClearMap();

	mapWidth = 320;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	underWater = true;

	LoadMinionLevel_2_2();

	ReadMap("Source/maps/Level2_2.map");
}

void Map::LoadLevel_2_3()
{
	ClearMap();

	mapWidth = 250;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_2_3();

	ReadMap("Source/maps/Level2_3.map");

	tile[102][5]->SetMustroom(true);
}

void Map::LoadLevel_2_4()
{
	ClearMap();

	mapWidth = 190;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_2_4();

	ReadMap("Source/maps/Level2_4.map");
}

void Map::LoadLevel_3_1()
{
	ClearMap();

	mapWidth = 375;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_3_1();

	ReadMap("Source/maps/Level3_1.map");

	tile[22][8]->SetMustroom(true);
	tile[82][5]->SetMustroom(true);
	tile[117][5]->SetMustroom(true);
	tile[156][9]->SetMustroom(true);
	tile[82][5]->SetPowerUp(false);

	tile[90][5]->SetStar(true);

	tile[167][9]->SetNumberOfCoin(8);
}

void Map::LoadLevel_3_2()
{
	ClearMap();

	mapWidth = 230;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_3_2();

	ReadMap("Source/maps/Level3_2.map");

	tile[60][6]->SetMustroom(true);
	tile[77][5]->SetStar(true);
	tile[77][9]->SetNumberOfCoin(10);
}

void Map::LoadLevel_3_3()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_3_3();

	ReadMap("Source/maps/Level3_3.map");

	tile[49][3]->SetMustroom(true);
}

void Map::LoadLevel_3_4()
{
	ClearMap();

	mapWidth = 225;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_3_4();

	ReadMap("Source/maps/Level3_4.map");
}

void Map::LoadLevel_4_1()
{
	ClearMap();

	mapWidth = 325;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_4_1();

	ReadMap("Source/maps/Level4_1.map");

	tile[25][9]->SetMustroom(true);
	tile[92][5]->SetMustroom(true);
	tile[263][9]->SetMustroom(true);
	tile[148][9]->SetMustroom(true);
	tile[92][5]->SetPowerUp(false);

	tile[220][9]->SetNumberOfCoin(6);
}

void Map::LoadLevel_4_2()
{
	ClearMap();

	mapWidth = 435;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_4_2();

	ReadMap("Source/maps/Level4_2.map");

	tile[28][9]->SetMustroom(true);
	tile[55][9]->SetMustroom(true);
	tile[120][5]->SetMustroom(true);
	tile[161][9]->SetMustroom(true);

	tile[81][9]->SetStar(true);

	tile[43][4]->SetNumberOfCoin(8);
	tile[77][9]->SetNumberOfCoin(6);
	tile[284][7]->SetNumberOfCoin(8);
}

void Map::LoadLevel_4_3()
{
	ClearMap();

	mapWidth = 171;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_4_3();

	ReadMap("Source/maps/Level4_3.map");

	tile[43][2]->SetMustroom(true);
}

void Map::LoadLevel_4_4()
{
	ClearMap();

	mapWidth = 200;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_4_4();

	ReadMap("Source/maps/Level4_4.map");
}

void Map::LoadLevel_5_1()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_5_1();

	ReadMap("Source/maps/Level5_1.map");

	tile[148][9]->SetMustroom(true);
	tile[91][5]->SetStar(true);

	tile[242][7]->SetNumberOfCoin(8);
}

void Map::LoadLevel_5_2()
{
	ClearMap();

	mapWidth = 415;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_5_2();

	ReadMap("Source/maps/Level5_2.map");

	tile[114][5]->SetMustroom(true);
	tile[222][11]->SetMustroom(true);
	tile[248][9]->SetMustroom(true);
	tile[205][5]->SetStar(true);

	tile[221][11]->SetNumberOfCoin(6);
}

void Map::LoadLevel_5_3()
{
	ClearMap();

	mapWidth = 270;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_5_3();

	ReadMap("Source/maps/Level5_3.map");

	tile[59][10]->SetMustroom(true);
}

void Map::LoadLevel_5_4()
{
	ClearMap();

	mapWidth = 190;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_5_4();

	ReadMap("Source/maps/Level5_4.map");
}

void Map::LoadLevel_6_1()
{
	ClearMap();

	mapWidth = 210;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_6_1();

	ReadMap("Source/maps/Level6_1.map");

	tile[36][5]->SetMustroom(true);
	tile[90][8]->SetMustroom(true);
	tile[130][8]->SetMustroom(true);
	tile[90][8]->SetPowerUp(false);

	tile[43][9]->SetNumberOfCoin(7);
	tile[152][9]->SetNumberOfCoin(8);
}

void Map::LoadLevel_6_2()
{
	ClearMap();

	mapWidth = 495;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_6_2();

	ReadMap("Source/maps/Level6_2.map");

	tile[137][9]->SetMustroom(true);
	tile[373][9]->SetMustroom(true);
	tile[225][5]->SetStar(true);
	tile[109][5]->SetNumberOfCoin(8);
	tile[344][7]->SetNumberOfCoin(8);
}

void Map::LoadLevel_6_3()
{
	ClearMap();

	mapWidth = 200;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_6_3();

	ReadMap("Source/maps/Level6_3.map");

	tile[55][3]->SetMustroom(true);
}

void Map::LoadLevel_6_4()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_6_4();

	ReadMap("Source/maps/Level6_4.map");

	tile[30][6]->SetMustroom(true);
}

void Map::LoadLevel_7_1()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_7_1();

	ReadMap("Source/maps/Level7_1.map");

	tile[27][5]->SetMustroom(true);
	tile[93][5]->SetMustroom(true);
	tile[151][2]->SetMustroom(true);
	tile[93][5]->SetPowerUp(false);
	tile[65][9]->SetNumberOfCoin(8);
}

void Map::LoadLevel_7_2()
{
	ClearMap();

	mapWidth = 320;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_7_2();

	ReadMap("Source/maps/Level7_2.map");
}

void Map::LoadLevel_7_3()
{
	ClearMap();

	mapWidth = 250;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_7_3();

	ReadMap("Source/maps/Level7_3.map");

	tile[102][5]->SetMustroom(true);
}

void Map::LoadLevel_7_4()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_7_4();

	ReadMap("Source/maps/Level7_4.map");
}

void Map::LoadLevel_8_1()
{
	ClearMap();

	mapWidth = 440;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_8_1();

	ReadMap("Source/maps/Level8_1.map");

	tile[80][8]->SetMustroom(true);
	tile[186][8]->SetStar(true);
	tile[158][5]->SetNumberOfCoin(8);
	tile[422][9]->SetNumberOfCoin(10);
}

void Map::LoadLevel_8_2()
{
	ClearMap();

	mapWidth = 400;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanNgay;
	
	CreateMap();
	LoadMinionLevel_8_2();

	ReadMap("Source/maps/Level8_2.map");

	tile[44][5]->SetMustroom(true);
	tile[100][9]->SetMustroom(true);
	tile[44][9]->SetPowerUp(false);
	tile[120][9]->SetNumberOfCoin(8);
	tile[254][7]->SetNumberOfCoin(8);
}

void Map::LoadLevel_8_3()
{
	ClearMap();

	mapWidth = 240;
	mapHeight = 15;
	mapTime = 300;
	mapType = BanNgay;

	CreateMap();
	LoadMinionLevel_8_3();

	ReadMap("Source/maps/Level8_3.map");

	tile[66][5]->SetMustroom(true);
	tile[116][5]->SetMustroom(true);
}

void Map::LoadLevel_8_4()
{
	ClearMap();

	mapWidth = 480;
	mapHeight = 15;
	mapTime = 400;
	mapType = BanDem;

	CreateMap();
	LoadMinionLevel_8_4();

	ReadMap("Source/maps/Level8_4.map");
}

void Map::LoadMinionLevel_1_1()
{
	ClearMinion();

	AddGoombas(22 * 32, 383, 5, true);
	AddGoombas(40 * 32, 383, 5, true);
	AddGoombas(51 * 32, 383, 5, true);
	AddGoombas(52 * 32 + 16, 383, 5, true);
	AddGoombas(80 * 32, 127, 5, true);
	AddGoombas(82 * 32, 127, 5, true);
	AddGoombas(97 * 32, 383, 5, true);
	AddGoombas(98 * 32 + 16, 383, 5, true);
	AddGoombas(114 * 32, 383, 5, true);
	AddGoombas(115 * 32 + 16, 383, 5, true);
	AddGoombas(124 * 32, 383, 5, true);
	AddGoombas(125 * 32 + 16, 383, 5, true);
	AddGoombas(128 * 32, 383, 5, true);
	AddGoombas(129 * 32 + 16, 383, 5, true);
	AddGoombas(174 * 32, 383, 5, true);
	AddGoombas(175 * 32 + 12, 383, 5, true);

	AddKoppa(107 * 32, 383, 11, 1, true);
}

void Map::LoadMinionLevel_1_2()
{
	ClearMinion();

	AddGoombas(16 * 32, 383, 7, true);
	AddGoombas(17 * 32 + 8, 351, 7, true);
	AddGoombas(29 * 32, 383, 7, true);
	AddGoombas(62 * 32, 383, 7, true);
	AddGoombas(64 * 32, 383, 7, true);
	AddGoombas(73 * 32, 383 - 8 * 32, 7, true);
	AddGoombas(76 * 32, 383 - 4 * 32, 7, true);
	AddGoombas(77 * 32 + 16, 368 - 4 * 32, 7, true);
	AddGoombas(99 * 32, 383, 7, true);
	AddGoombas(100 * 32 + 16, 383, 7, true);
	AddGoombas(102 * 32, 383, 7, true);
	AddGoombas(113 * 32, 383, 7, true);
	AddGoombas(135 * 32, 383 - 3 * 32, 7, true);
	AddGoombas(136 * 32 + 16, 383 - 4 * 32, 7, true);

	AddKoppa(44 * 32, 383, 14, 1, true);
	AddKoppa(45 * 32 + 16, 383, 14, 1, true);
	AddKoppa(59 * 32, 383, 14, 1, true);

	AddKoppa(146 * 32, 383, 14, 1, true);
}

void Map::LoadMinionLevel_1_3()
{
	ClearMinion();

	AddGoombas(44 * 32, Window::gameHeight - 32 - 11 * 32, 5, true);
	AddGoombas(46 * 32, Window::gameHeight - 32 - 11 * 32, 5, true);
	AddGoombas(80 * 32, Window::gameHeight - 32 - 9 * 32, 5, true);

	AddKoppa(30 * 32 - 8, Window::gameHeight - 32 - 10 * 32, 11, 1, true);
	AddKoppa(74 * 32 - 8, Window::gameHeight - 32 - 10 * 32, 11, 3, false);
	AddKoppa(110 * 32 - 8, Window::gameHeight - 32 - 8 * 32, 11, 1, true);
	AddKoppa(114 * 32 - 8, Window::gameHeight - 32 - 9 * 32, 11, 3, false);
	AddKoppa(133 * 32 - 8, Window::gameHeight - 32 - 2 * 32, 11, 1, true);
	mapType = BanNgay;
}

void Map::LoadMinionLevel_1_4()
{
	ClearMinion();

	AddBowser(135 * 32, Window::gameHeight - 7 * 32);
	AddToad(153 * 32, Window::gameHeight - 4 * 32, false);

	AddFireBall(30 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, true);
	AddFireBall(49 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(60 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(67 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(76 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(84 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(88 * 32, Window::gameHeight - 11 * 32, 6, rand() % 360, false);
}

void Map::LoadMinionLevel_2_1()
{
	ClearMinion();

	AddGoombas(24 * 32, Window::gameHeight - 8 * 32, 5, true);
	AddGoombas(42 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(43 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(59 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(60 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(68 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(69 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(71 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(87 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(88 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(90 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(102 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(114 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(120 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(162 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(163 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(32 * 32 - 2, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(33 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(55 * 32, Window::gameHeight - 7 * 32, 11, 1, true);
	AddKoppa(66 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(137 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(151 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(169 * 32, Window::gameHeight - 3 * 32, 12, 0, true);
	AddKoppa(171 * 32, Window::gameHeight - 3 * 32, 12, 0, true);
	AddKoppa(185 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
}

void Map::LoadMinionLevel_2_2()
{
	ClearMinion();

	AddSquid(22 * 32, Window::gameHeight - 4 * 32);
	AddSquid(46 * 32, Window::gameHeight - 6 * 32);
	AddSquid(55 * 32, Window::gameHeight - 5 * 32);
	AddSquid(83 * 32, Window::gameHeight - 7 * 32);
	AddSquid(94 * 32, Window::gameHeight - 12 * 32);
	AddSquid(105 * 32, Window::gameHeight - 4 * 32);

	AddCheep(75 * 32 + 28, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(78 * 32 + 28, Window::gameHeight - 8 * 32, 0, 1);
	AddCheep(81 * 32 + 28, Window::gameHeight - 3 * 32 - 28, 0, 1);
	AddCheep(94 * 32 + 14, Window::gameHeight - 9 * 32, 0, 1);
	AddCheep(101 * 32 + 28, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(97 * 32 + 8, Window::gameHeight - 12 * 32, 0, 1);
	AddCheep(117 * 32 + 8, Window::gameHeight - 11 * 32, 0, 1);
	AddCheep(127 * 32 + 24, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(131 * 32 + 8, Window::gameHeight - 4 * 32 - 4, 0, 1);
	AddCheep(136 * 32 + 16, Window::gameHeight - 7 * 32, 0, 1);
	AddCheep(145 * 32 + 8, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(149 * 32 + 28, Window::gameHeight - 9 * 32 - 4, 0, 1);
	AddCheep(164 * 32, Window::gameHeight - 12 * 32, 0, 1);
	AddCheep(167 * 32, Window::gameHeight - 4 * 32, 0, 1);
	AddCheep(175 * 32, Window::gameHeight - 7 * 32 - 4, 0, 1);
	AddCheep(183 * 32, Window::gameHeight - 11 * 32, 0, 1);
	AddCheep(186 * 32 + 16, Window::gameHeight - 8 * 32, 0, 1);
}

void Map::LoadMinionLevel_2_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_2_4()
{
	ClearMinion();

	AddBowser(135 * 32, Window::gameHeight - 7 * 32);
	AddToad(153 * 32, Window::gameHeight - 4 * 32, false);

	AddFireBall(49 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, true);
	AddFireBall(55 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(61 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, true);
	AddFireBall(73 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, true);
	AddFireBall(82 * 32, Window::gameHeight - 8 * 32, 6, rand() % 360, true);
	AddFireBall(92 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, false);
}

void Map::LoadMinionLevel_3_1()
{
	ClearMinion();

	AddGoombas(37 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(53 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(54 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(56 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(82 * 32, Window::gameHeight - 7 * 32, 5, true);
	AddGoombas(83 * 32 + 16, Window::gameHeight - 7 * 32, 5, true);
	AddGoombas(85 * 32, Window::gameHeight - 7 * 32, 5, true);
	AddGoombas(94 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(95 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(139 * 32 - 4, Window::gameHeight - 7 * 32, 5, true);
	AddGoombas(140 * 32, Window::gameHeight - 8 * 32, 5, true);
	AddGoombas(154 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(155 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(157 * 32, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(25 * 32, Window::gameHeight - 3 * 32, 18, 0, true);
	AddKoppa(28 * 32, Window::gameHeight - 4 * 32, 18, 0, true);
	AddKoppa(65 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(101 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(149 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(152 * 32, Window::gameHeight - 11 * 32, 17, 1, true);
	AddKoppa(165 * 32, Window::gameHeight - 3 * 32, 18, 0, true);
	AddKoppa(168 * 32, Window::gameHeight - 4 * 32, 18, 0, true);
	AddKoppa(170 * 32, Window::gameHeight - 7 * 32, 17, 1, true);
	AddKoppa(171 * 32, Window::gameHeight - 3 * 32, 18, 0, true);
	AddKoppa(188 * 32, Window::gameHeight - 9 * 32, 17, 1, true);
	AddKoppa(191 * 32, Window::gameHeight - 11 * 32, 17, 1, true);

	AddHammerBro(113 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(116 * 32, Window::gameHeight - 4 * 32);
}

void Map::LoadMinionLevel_3_2()
{
	ClearMinion();

	AddGoombas(24 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(25 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(27 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(71 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(72 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(74 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(119 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(120 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(122 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(179 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(180 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(182 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(188 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(189 * 32 + 16, Window::gameHeight  - 3 * 32, 5, true);
	AddGoombas(191 * 32, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(17 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(33 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(34 * 32 + 16, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(36 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(43 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(44 * 32 + 16, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(66 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(78 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(98 * 32, Window::gameHeight - 3 * 32, 18, 0, true);
	AddKoppa(111 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(134 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(140 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(141 * 32 + 16, Window::gameHeight - 2 * 32, 17, 1, true);
	AddKoppa(143 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(150 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(151 * 32 + 16, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(162 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(163 * 32 + 16, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(165 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(175 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
}

void Map::LoadMinionLevel_3_3()
{
	ClearMinion();

	AddGoombas(26 * 32, Window::gameHeight - 9 * 32, 5, true);

	AddKoppa(52 * 32, Window::gameHeight - 9 * 32, 17, 1, true);
	AddKoppa(54 * 32, Window::gameHeight - 5 * 32, 17, 1, true);
	AddKoppa(73 * 32, Window::gameHeight - 3 * 32, 17, 1, true);
	AddKoppa(114 * 32 - 8, Window::gameHeight - 10 * 32, 18, 3, false);
	AddKoppa(124 * 32, Window::gameHeight - 6 * 32, 17, 1, true);
	AddKoppa(126 * 32, Window::gameHeight - 6 * 32, 17, 1, true);
}

void Map::LoadMinionLevel_3_4()
{
	ClearMinion();

	AddBowser(135 * 32, Window::gameHeight - 7 * 32);
	AddToad(153 * 32, Window::gameHeight - 4 * 32, false);

	AddFireBall(19 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(24 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(29 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(54 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(54 * 32, Window::gameHeight - 10 * 32, 6, rand() % 360, false);
	AddFireBall(64 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(64 * 32, Window::gameHeight - 10 * 32, 6, rand() % 360, false);
	AddFireBall(80 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(80 * 32, Window::gameHeight - 10 * 32, 6, rand() % 360, false);
}

void Map::LoadMinionLevel_4_1()
{
	ClearMinion();

	AddLakito(26 * 32, Window::gameHeight - 12 * 32, 207 * 32);
}

void Map::LoadMinionLevel_4_2()
{
	ClearMinion();

	AddGoombas(43 * 32, Window::gameHeight - 7 * 32, 7, true);
	AddGoombas(44 * 32 + 16, Window::gameHeight - 7 * 32, 7, true);
	AddGoombas(46 * 32, Window::gameHeight - 7 * 32, 7, true);

	AddKoppa(77 * 32, Window::gameHeight - 3 * 32, 14, 1, true);
	AddKoppa(100 * 32, Window::gameHeight - 3 * 32, 14, 1, true);
	AddKoppa(101 * 32 + 16, Window::gameHeight - 3 * 32, 14, 1, true);
	AddKoppa(137 * 32, Window::gameHeight - 3 * 32, 14, 1, true);
	AddKoppa(168 * 32, Window::gameHeight - 3 * 32, 14, 1, true);
	AddKoppa(169 * 32 + 16, Window::gameHeight - 3 * 32, 14, 1, true);

	AddBeetle(83 * 32, Window::gameHeight - 3 * 32, 55, true);
	AddBeetle(88 * 32, Window::gameHeight - 3 * 32, 55, true);
	AddBeetle(154 * 32, Window::gameHeight - 6 * 32, 55, true);
	AddBeetle(179 * 32, Window::gameHeight - 3 * 32, 55, true);
}

void Map::LoadMinionLevel_4_3()
{
	ClearMinion();

	AddKoppa(28 * 32 - 2, Window::gameHeight - 7 * 32, 11, 1, true);
	AddKoppa(29 * 32, Window::gameHeight - 7 * 32, 11, 1, true);
	AddKoppa(35 * 32, Window::gameHeight - 12 * 32, 12, 3, false);
	AddKoppa(39 * 32, Window::gameHeight - 4 * 32, 11, 1, true);
	AddKoppa(68 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(78 * 32, Window::gameHeight - 11 * 32, 11, 1, true);
}

void Map::LoadMinionLevel_4_4()
{
	ClearMinion();

	AddBowser(167 * 32, Window::gameHeight - 7 * 32);
	AddToad(186 * 32, Window::gameHeight - 4 * 32, false);

	AddFireBall(53 * 32, Window::gameHeight - 8 * 32, 6, rand() % 360, true);
	AddFireBall(60 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, false);
	AddFireBall(115 * 32, Window::gameHeight - 8 * 32, 6, rand() % 360, true);
	AddFireBall(122 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
	AddFireBall(162 * 32, Window::gameHeight - 4 * 32, 6, rand() % 360, true);
}

void Map::LoadMinionLevel_5_1()
{
	ClearMinion();

	AddGoombas(19 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(20 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(22 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(30 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(31 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(33 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(65 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(66 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(68 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(76 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(77 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(103 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(104 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(106 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(121 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(122 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(124 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(135 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(136 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(138 * 32, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(16 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(41 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(42 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(61 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(87 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(127 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(144 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(145 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(178 * 32, Window::gameHeight - 3 * 32, 12, 0, true);
	AddKoppa(182 * 32, Window::gameHeight - 7 * 32, 11, 1, true);
}

void Map::LoadMinionLevel_5_2()
{
	ClearMinion();

	AddGoombas(143 * 32, Window::gameHeight - 5 * 32, 5, true);
	AddGoombas(145 * 32, Window::gameHeight - 7 * 32, 5, true);
	AddGoombas(235 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(236 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(103 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(120 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(186 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(237 * 32, Window::gameHeight - 11 * 32, 11, 1, true);
	AddKoppa(243 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(246 * 32, Window::gameHeight - 3 * 32, 12, 0, true);
	AddKoppa(266 * 32, Window::gameHeight - 8 * 32, 12, 0, true);

	AddBeetle(216 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(217 * 32 + 4, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(218 * 32 + 8, Window::gameHeight - 3 * 32, 53, true);

	AddHammerBro(126 * 32, Window::gameHeight - 7 * 32);
	AddHammerBro(161 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(200 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(204 * 32, Window::gameHeight - 12 * 32);

	AddSquid(17 * 32, Window::gameHeight - 4 * 32);
	AddSquid(34 * 32, Window::gameHeight - 4 * 32);
	AddSquid(43 * 32 + 16, Window::gameHeight - 4 * 32);
	
	AddCheep(27 * 32 + 16, Window::gameHeight - 9 * 32, 0, 1);
	AddCheep(38 * 32 + 28, Window::gameHeight - 4 * 32, 0, 1);
	AddCheep(48 * 32 + 16, Window::gameHeight - 6 * 32, 0, 1);
	AddCheep(53 * 32 + 16, Window::gameHeight - 11 * 32, 0, 1);
}

void Map::LoadMinionLevel_5_3()
{
	ClearMinion();

	AddGoombas(44 * 32, Window::gameHeight - 12 * 32, 5, true);
	AddGoombas(46 * 32, Window::gameHeight - 12 * 32, 5, true);
	AddGoombas(80 * 32, Window::gameHeight - 10 * 32, 5, true);

	AddKoppa(30 * 32 - 8, Window::gameHeight - 11 * 32, 11, 1, true);
	AddKoppa(74 * 32 - 8, Window::gameHeight - 11 * 32, 12, 3, false);
	AddKoppa(110 * 32 - 8, Window::gameHeight - 9 * 32, 11, 1, true);
	AddKoppa(114 * 32 - 8, Window::gameHeight - 10 * 32, 12, 3, false);
	AddKoppa(133 * 32 - 8, Window::gameHeight - 3 * 32, 11, 1, true);
	mapType = BanNgay;
}

void Map::LoadMinionLevel_5_4()
{
	ClearMinion();

	AddBowser(135 * 32, Window::gameHeight - 7 * 32);
	AddToad(153 * 32, Window::gameHeight - 4 * 32, false);

	AddFireBall(23 * 32, Window::gameHeight - 7 * 32, 12, rand() % 360, true);
	AddFireBall(43 * 32, Window::gameHeight - 1 * 32, 6, rand() % 360, false);
	AddFireBall(49 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(55 * 32, Window::gameHeight - 1 * 32, 6, rand() % 360, false);
	AddFireBall(55 * 32, Window::gameHeight - 10 * 32, 6, rand() % 360, true);
	AddFireBall(61 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(67 * 32, Window::gameHeight - 1 * 32, 6, rand() % 360, true);
	AddFireBall(73 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(82 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(92 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, false);
	AddFireBall(103 * 32, Window::gameHeight - 3 * 32, 6, rand() % 360, true);
}

void Map::LoadMinionLevel_6_1()
{
	ClearMinion();

	AddLakito(23 * 32, Window::gameHeight - 12 * 32, 176 * 32);
}

void Map::LoadMinionLevel_6_2()
{
	ClearMinion();

	AddGoombas(152 * 32, Window::gameHeight - 11 * 32, 5, true);
	AddGoombas(254 * 32, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(111 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(128 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(291 * 32, Window::gameHeight - 12 * 32, 12, 0, true);

	AddBeetle(139 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(177 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(205 * 32, Window::gameHeight - 11 * 32, 53, true);
	AddBeetle(248 * 32, Window::gameHeight - 3 * 32, 53, true);

	AddSquid(17 * 32, Window::gameHeight  - 5 * 32);
	AddSquid(34 * 32, Window::gameHeight  - 5 * 32);
	AddSquid(43 * 32 + 16, Window::gameHeight - 5 * 32);

	AddCheep(27 * 32 + 16, Window::gameHeight - 10 * 32, 0, 1);
	AddCheep(38 * 32 + 28, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(48 * 32 + 16, Window::gameHeight - 7 * 32, 0, 1);
	AddCheep(53 * 32 + 16, Window::gameHeight - 12 * 32, 0, 1);
}

void Map::LoadMinionLevel_6_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_6_4()
{
	ClearMinion();

	AddBowser(135 * 32, Window::gameHeight - 7 * 32, true);
	AddToad(153 * 32, Window::gameHeight - 7 * 32, false);

	AddFireBall(23 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(30 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, true);
	AddFireBall(37 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(49 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(60 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(67 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(76 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(80 * 32, Window::gameHeight - 11 * 32, 6, rand() % 360, false);
	AddFireBall(84 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
	AddFireBall(88 * 32, Window::gameHeight - 11 * 32, 6, rand() % 360, false);
	AddFireBall(92 * 32, Window::gameHeight - 6 * 32, 6, rand() % 360, true);
}

void Map::LoadMinionLevel_7_1()
{
	ClearMinion();

	AddKoppa(26 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(44 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(53 * 32, Window::gameHeight - 3 * 32, 12, 0, true);
	AddKoppa(65 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(114 * 32, Window::gameHeight - 3 * 32, 11, 1, true);

	AddBeetle(169 * 32, Window::gameHeight - 11 * 32, 53, true);

	AddHammerBro(85 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(87 * 32, Window::gameHeight - 12 * 32);
	AddHammerBro(137 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(135 * 32, Window::gameHeight - 4 * 32);
}

void Map::LoadMinionLevel_7_2()
{
	ClearMinion();

	AddSquid(22 * 32, Window::gameHeight - 4 * 32);
	AddSquid(24 * 32, Window::gameHeight - 8 * 32);
	AddSquid(46 * 32, Window::gameHeight - 6 * 32);
	AddSquid(52 * 32, Window::gameHeight - 8 * 32);
	AddSquid(55 * 32, Window::gameHeight - 5 * 32);
	AddSquid(77 * 32, Window::gameHeight - 9 * 32);
	AddSquid(83 * 32, Window::gameHeight - 7 * 32);
	AddSquid(90 * 32, Window::gameHeight - 4 * 32);
	AddSquid(94 * 32, Window::gameHeight - 12 * 32);
	AddSquid(105 * 32, Window::gameHeight - 4 * 32);
	AddSquid(150 * 32, Window::gameHeight - 7 * 32);
	AddSquid(173 * 32, Window::gameHeight - 4 * 32);
	AddSquid(179 * 32, Window::gameHeight - 4 * 32);

	AddCheep(75 * 32 + 28, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(78 * 32 + 28, Window::gameHeight - 8 * 32, 0, 1);
	AddCheep(81 * 32 + 28, Window::gameHeight - 3 * 32 - 28, 0, 1);
	AddCheep(94 * 32 + 14, Window::gameHeight - 9 * 32, 0, 1);
	AddCheep(101 * 32 + 28, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(97 * 32 + 8, Window::gameHeight - 12 * 32, 0, 1);
	AddCheep(117 * 32 + 8, Window::gameHeight - 11 * 32, 0, 1);
	AddCheep(127 * 32 + 24, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(131 * 32 + 8, Window::gameHeight - 4 * 32 - 4, 0, 1);
	AddCheep(136 * 32 + 16, Window::gameHeight - 7 * 32, 0, 1);
	AddCheep(145 * 32 + 8, Window::gameHeight - 5 * 32, 0, 1);
	AddCheep(149 * 32 + 28, Window::gameHeight - 9 * 32 - 4, 0, 1);
	AddCheep(164 * 32, Window::gameHeight - 12 * 32, 0, 1);
	AddCheep(167 * 32, Window::gameHeight - 4 * 32, 0, 1);
	AddCheep(175 * 32, Window::gameHeight - 7 * 32 - 4, 0, 1);
	AddCheep(183 * 32, Window::gameHeight - 11 * 32, 0, 1);
	AddCheep(186 * 32 + 16, Window::gameHeight - 8 * 32, 0, 1);
}

void Map::LoadMinionLevel_7_3()
{
	ClearMinion();

	AddKoppa(52 * 32, Window::gameHeight - 7 * 32, 12, 0, true);
	AddKoppa(140 * 32, Window::gameHeight - 8 * 32, 12, 0, true);
	AddKoppa(156 * 32, Window::gameHeight - 6 * 32, 12, 0, true);

	AddKoppa(79 * 32, Window::gameHeight - 6 * 32, 11, 1, true);
	AddKoppa(95 * 32, Window::gameHeight - 6 * 32, 11, 1, true);
	AddKoppa(119 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
}

void Map::LoadMinionLevel_7_4()
{
	ClearMinion();

	AddBowser(263 * 32, Window::gameHeight - 7 * 32, true);
	AddToad(281 * 32, Window::gameHeight - 4 * 32, false);
}

void Map::LoadMinionLevel_8_1()
{
	ClearMinion();

	AddGoombas(23 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(24 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(26 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(30 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(31 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(33 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(69 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(70 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(72 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(108 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(109 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(111 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(148 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(149 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(151 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(232 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(233 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(235 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(257 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(258 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(260 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(264 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(265 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(267 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(272 * 32, Window::gameHeight - 3 * 32, 5, true);
	AddGoombas(273 * 32 + 16, Window::gameHeight - 3 * 32, 5, true);

	AddKoppa(43 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(44 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(61 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(119 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(124 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(125 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(127 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(130 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(131 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(133 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(161 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(172 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(177 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(207 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(208 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(305 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(332 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(339 * 32, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(340 * 32 + 16, Window::gameHeight - 3 * 32, 11, 1, true);
	AddKoppa(342 * 32, Window::gameHeight - 3 * 32, 11, 1, true);

	AddBeetle(18 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(81 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(254 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(283 * 32, Window::gameHeight - 3 * 32, 53, true);
}

void Map::LoadMinionLevel_8_2()
{
	ClearMinion();

	AddGoombas(184 * 32, Window::gameHeight - 6 * 32, 5, true);
	AddGoombas(186 * 32, Window::gameHeight - 8 * 32, 5, true);

	AddKoppa(18 * 32 - 8, Window::gameHeight - 6 * 32, 12, 0, true);
	AddKoppa(24 * 32, Window::gameHeight - 11 * 32, 12, 0, true);
	AddKoppa(57 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(66 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(69 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(92 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(95 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(139 * 32, Window::gameHeight - 3 * 32, 12, 0, true);
	AddKoppa(170 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(172 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(175 * 32, Window::gameHeight - 7 * 32, 12, 0, true);
	AddKoppa(203 * 32, Window::gameHeight - 9 * 32, 12, 0, true);

	AddBeetle(111 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(121 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(123 * 32, Window::gameHeight - 3 * 32, 53, true);
	AddBeetle(189 * 32, Window::gameHeight - 3 * 32, 53, true);

	AddLakito(16 * 32, Window::gameHeight - 12 * 32, 216 * 32);
}

void Map::LoadMinionLevel_8_3()
{
	ClearMinion();

	AddKoppa(30 * 32, Window::gameHeight - 5 * 32, 12, 0, true);
	AddKoppa(93 * 32, Window::gameHeight - 4 * 32, 12, 0, true);
	AddKoppa(137 * 32, Window::gameHeight - 3 * 32, 11, 1, true);

	AddHammerBro(63 * 32, Window::gameHeight - 4 * 32);
	AddHammerBro(65 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(117 * 32, Window::gameHeight - 8 * 32);
	AddHammerBro(119 * 32, Window::gameHeight - 4 * 32);
	AddHammerBro(146 * 32, Window::gameHeight - 4 * 32);
	AddHammerBro(159 * 32, Window::gameHeight - 4 * 32);
	AddHammerBro(177 * 32, Window::gameHeight - 4 * 32);
	AddHammerBro(185 * 32, Window::gameHeight - 4 * 32);
}

void Map::LoadMinionLevel_8_4()
{
	ClearMinion();

	AddGoombas(56 * 32, Window::gameHeight - 3 * 32, 9, true);
	AddGoombas(57 * 32 + 16, Window::gameHeight - 3 * 32, 9, true);
	AddGoombas(59 * 32, Window::gameHeight - 3 * 32, 9, true);

	AddBeetle(139 * 32, Window::gameHeight - 3 * 32, 57, true);
	AddBeetle(141 * 32, Window::gameHeight - 3 * 32, 57, true);

	AddHammerBro(316 * 32, Window::gameHeight - 4 * 32);

	AddKoppa(150 * 32 - 8, Window::gameHeight - 5 * 32, 18, 0, true);
	AddKoppa(152 * 32 - 8, Window::gameHeight - 4 * 32, 18, 0, true);
	AddKoppa(165 * 32 - 8, Window::gameHeight - 4 * 32, 18, 0, true);
	AddKoppa(167 * 32 - 8, Window::gameHeight - 5 * 32, 18, 0, true);

	AddBowser(338 * 32, Window::gameHeight - 7 * 32, true);
	AddToad(356 * 32, Window::gameHeight - 4 * 32, true);

	AddFireBall(410 * 32, Window::gameHeight - 8 * 32, 6, rand() % 360, true);
	AddFireBall(421 * 32, Window::gameHeight - 5 * 32, 6, rand() % 360, false);
	AddFireBall(430 * 32, Window::gameHeight - 9 * 32, 6, rand() % 360, true);
	AddFireBall(446 * 32, Window::gameHeight - 7 * 32, 6, rand() % 360, true);
	AddFireBall(454 * 32, Window::gameHeight - 8 * 32, 6, rand() % 360, false);

	AddSquid(418 * 32, Window::gameHeight - 4 * 32);
	AddSquid(441 * 32, Window::gameHeight - 5 * 32);
	AddSquid(443 * 32, Window::gameHeight - 9 * 32);
}

void Map::AddGoombas(int x, int y, int id, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Goombas(x, y, id, moveDirection));
}

void Map::AddKoppa(int x, int y, int id, int minionState, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Koopa(x, y, id, minionState, moveDirection));
}
void Map::AddBowser(int x, int y, bool spawnHammer)
{
	minion[GetListID(x)].push_back(new Bowser(x, y, spawnHammer));
}

void Map::AddToad(int x, int y, bool peach)
{
	minion[GetListID(x)].push_back(new Toad(x, y, peach));
}

void Map::AddSquid(int x, int y)
{
	minion[GetListID(x)].push_back(new Squid(x, y));
}

void Map::AddCheep(int x, int y, int minionType, int moveSpeed, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Cheep(x, y, minionType, moveSpeed, moveDirection));
}

void Map::AddCheepSpawner(int x, int xEnd)
{
}

void Map::AddHammerBro(int x, int y)
{
	minion[GetListID(x)].push_back(new HammerBro(x, y));
}

void Map::AddHammer(int x, int y, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Hammer(x, y));
}

void Map::AddLakito(int x, int y, int maxX)
{
	minion[GetListID(x)].push_back(new Lakito(x, y, maxX));
}

void Map::AddSpikey(int x, int y)
{
	minion[GetListID(x)].push_back(new Spikey(x, y));
}

void Map::AddBeetle(int x, int y, int id, bool moveDirection)
{
	minion[GetListID((int)x)].push_back(new Beetle(x, y, id, moveDirection));
}

void Map::AddVine(int x, int y, int id, int minionState)
{
	minion[GetListID(x)].push_back(new Vine());
}

void Map::AddFire(int x, int y, int toY)
{
	minion[GetListID(x)].push_back(new Fire(x, y, toY));
}

void Map::AddFireBall(int x, int y, int width, int id, bool left)
{
	for (int i = 9; i < width; i++)
	{
		//minion[GetListID(x)].push_back(new FireBall());
	}
}

void Map::AddBubble(int x, int y)
{
}

void Map::AddBulletBillSpawner(int x, int y, int minionState)
{
}

void Map::AddBulletBill(int x, int y, int minionState, bool moveDirection)
{
}

int Map::GetStartMap()
{
	return (int)(-xMap - (-(int)xMap % 32)) / 32;
}

int Map::GetEndMap()
{
	return (int)(-xMap - (-(int)xMap % 32) + 800) / 32 + 2;
}

int Map::GetListID(int x)
{
	return x / 160;
}