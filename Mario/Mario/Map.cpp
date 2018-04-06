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
				listBlock[tile[i][j]->GetID()]->Draw(window, sf::Vector2f(32.0f * i + xMap, j * 32.0f));
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

Event* Map::GetEvent()
{
	return event;
}

bool Map::GetInEvent()
{
	return inEvent;
}

void Map::SetInEvent(bool inEvent)
{
	this->inEvent = inEvent;
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
	underWater = true;

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

	AddGoombas(704, 383, 5, true);
	AddGoombas(1280, 383, 5, true);
	AddGoombas(1632, 383, 5, true);
	AddGoombas(1680, 383, 5, true);
	AddGoombas(2560, 127, 5, true);
	AddGoombas(2624, 127, 5, true);
	AddGoombas(3104, 383, 5, true);
	AddGoombas(3152, 383, 5, true);
	AddGoombas(3648, 383, 5, true);
	AddGoombas(3696, 383, 5, true);
	AddGoombas(3968, 383, 5, true);
	AddGoombas(4016, 383, 5, true);
	AddGoombas(4096, 383, 5, true);
	AddGoombas(4144, 383, 5, true);
	AddGoombas(5568, 383, 5, true);
	AddGoombas(5612, 383, 5, true);

	AddKoppa(3424, 383, 11, 1, true);
}

void Map::LoadMinionLevel_1_2()
{
	ClearMinion();

	AddGoombas(512, 383, 7, true);
	AddGoombas(552, 351, 7, true);
	AddGoombas(928, 383, 7, true);
	AddGoombas(1984, 383, 7, true);
	AddGoombas(2048, 383, 7, true);
	AddGoombas(2336, 127, 7, true);
	AddGoombas(2432, 255, 7, true);
	AddGoombas(2480, 255, 7, true);
	AddGoombas(3168, 383, 7, true);
	AddGoombas(3216, 383, 7, true);
	AddGoombas(3264, 383, 7, true);
	AddGoombas(3616, 383, 7, true);
	AddGoombas(4320, 288, 7, true);
	AddGoombas(4368, 256, 7, true);

	AddKoppa(1408, 383, 14, 1, true);
	AddKoppa(1456, 383, 14, 1, true);
	AddKoppa(1888, 383, 14, 1, true);

	AddKoppa(4672, 383, 14, 1, true);
}

void Map::LoadMinionLevel_1_3()
{
	ClearMinion();

	AddGoombas(1408, 95, 5, true);
	AddGoombas(1472, 95, 5, true);
	AddGoombas(2560, 159, 5, true);

	AddKoppa(952, 127, 11, 1, true);
	AddKoppa(2360, 127, 11, 3, false);
	AddKoppa(3512, 191, 11, 1, true);
	AddKoppa(3640, 159, 11, 3, false);
	AddKoppa(4248, 383, 11, 1, true);
}

void Map::LoadMinionLevel_1_4()
{
	ClearMinion();

	AddBowser(4320, 255);
	AddToad(4896, 351, false);

	AddFireBall(960, 319, 6, rand() % 360, true);
	AddFireBall(1568, 191, 6, rand() % 360, true);
	AddFireBall(1920, 191, 6, rand() % 360, true);
	AddFireBall(2144, 191, 6, rand() % 360, true);
	AddFireBall(2432, 287, 6, rand() % 360, true);
	AddFireBall(2688, 287, 6, rand() % 360, true);
	AddFireBall(2816, 127, 6, rand() % 360, false);
}

void Map::LoadMinionLevel_2_1()
{
	ClearMinion();

	AddGoombas(768, 223, 5, true);
	AddGoombas(1344, 383, 5, true);
	AddGoombas(1392, 383, 5, true);
	AddGoombas(1888, 383, 5, true);
	AddGoombas(1936, 383, 5, true);
	AddGoombas(2176, 383, 5, true);
	AddGoombas(2224, 383, 5, true);
	AddGoombas(2272, 383, 5, true);
	AddGoombas(2784, 383, 5, true);
	AddGoombas(2832, 383, 5, true);
	AddGoombas(2880, 383, 5, true);
	AddGoombas(3280, 383, 5, true);
	AddGoombas(3664, 383, 5, true);
	AddGoombas(3856, 383, 5, true);
	AddGoombas(5184, 383, 5, true);
	AddGoombas(5232, 383, 5, true);

	AddKoppa(1022, 383, 11, 1, true);
	AddKoppa(1056, 383, 11, 1, true);
	AddKoppa(1760, 255, 11, 1, true);
	AddKoppa(2112, 383, 11, 1, true);
	AddKoppa(4384, 383, 11, 1, true);
	AddKoppa(4832, 319, 12, 0, true);
	AddKoppa(5408, 383, 12, 0, true);
	AddKoppa(5472, 383, 12, 0, true);
	AddKoppa(5920, 383, 11, 1, true);
}

void Map::LoadMinionLevel_2_2()
{
	ClearMinion();

	AddSquid(704, 351);
	AddSquid(1472, 287);
	AddSquid(1760, 319);
	AddSquid(2656, 255);
	AddSquid(3008, 95);
	AddSquid(3360, 351);

	AddCheep(2428, 319, 0, 1);
	AddCheep(2524, 223, 0, 1);
	AddCheep(2620, 355, 0, 1);
	AddCheep(3022, 191, 0, 1);
	AddCheep(3260, 319, 0, 1);
	AddCheep(3112, 95, 0, 1);
	AddCheep(3752, 127, 0, 1);
	AddCheep(4088, 319, 0, 1);
	AddCheep(4200, 347, 0, 1);
	AddCheep(4368, 255, 0, 1);
	AddCheep(4648, 319, 0, 1);
	AddCheep(4796, 187, 0, 1);
	AddCheep(5248, 95, 0, 1);
	AddCheep(5344, 351, 0, 1);
	AddCheep(5600, 251, 0, 1);
	AddCheep(5856, 127, 0, 1);
	AddCheep(5968, 223, 0, 1);
}

void Map::LoadMinionLevel_2_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_2_4()
{
	ClearMinion();

	AddBowser(4320, 255);
	AddToad(4896, 351, false);

	AddFireBall(1568, 319, 6, rand() % 360, true);
	AddFireBall(1760, 191, 6, rand() % 360, true);
	AddFireBall(1952, 319, 6, rand() % 360, true);
	AddFireBall(2336, 319, 6, rand() % 360, true);
	AddFireBall(2624, 223, 6, rand() % 360, true);
	AddFireBall(2944, 351, 6, rand() % 360, false);
}

void Map::LoadMinionLevel_3_1()
{
	ClearMinion();

	AddGoombas(1184, 383, 5, true);
	AddGoombas(1696, 383, 5, true);
	AddGoombas(1744, 383, 5, true);
	AddGoombas(1792, 383, 5, true);
	AddGoombas(2624, 255, 5, true);
	AddGoombas(2672, 255, 5, true);
	AddGoombas(2720, 255, 5, true);
	AddGoombas(3008, 383, 5, true);
	AddGoombas(3056, 383, 5, true);
	AddGoombas(4444, 255, 5, true);
	AddGoombas(4480, 223, 5, true);
	AddGoombas(4928, 383, 5, true);
	AddGoombas(4976, 383, 5, true);
	AddGoombas(5024, 383, 5, true);

	AddKoppa(800, 383, 18, 0, true);
	AddKoppa(896, 351, 18, 0, true);
	AddKoppa(2080, 383, 17, 1, true);
	AddKoppa(3232, 383, 17, 1, true);
	AddKoppa(4768, 383, 17, 1, true);
	AddKoppa(4864, 127, 17, 1, true);
	AddKoppa(5280, 383, 18, 0, true);
	AddKoppa(5376, 351, 18, 0, true);
	AddKoppa(5440, 255, 17, 1, true);
	AddKoppa(5472, 383, 18, 0, true);
	AddKoppa(6016, 191, 17, 1, true);
	AddKoppa(6112, 127, 17, 1, true);

	AddHammerBro(3616, 223);
	AddHammerBro(3712, 351);
}

void Map::LoadMinionLevel_3_2()
{
	ClearMinion();

	AddGoombas(768, 383, 5, true);
	AddGoombas(816, 383, 5, true);
	AddGoombas(864, 383, 5, true);
	AddGoombas(2272, 383, 5, true);
	AddGoombas(2320, 383, 5, true);
	AddGoombas(2368, 383, 5, true);
	AddGoombas(3808, 383, 5, true);
	AddGoombas(3856, 383, 5, true);
	AddGoombas(3904, 383, 5, true);
	AddGoombas(5728, 383, 5, true);
	AddGoombas(5776, 383, 5, true);
	AddGoombas(5824, 383, 5, true);
	AddGoombas(6016, 383, 5, true);
	AddGoombas(6064, 383, 5, true);
	AddGoombas(6112, 383, 5, true);

	AddKoppa(544, 383, 17, 1, true);
	AddKoppa(1056, 383, 17, 1, true);
	AddKoppa(1104, 383, 17, 1, true);
	AddKoppa(1152, 383, 17, 1, true);
	AddKoppa(1376, 383, 17, 1, true);
	AddKoppa(1424, 383, 17, 1, true);
	AddKoppa(2112, 383, 17, 1, true);
	AddKoppa(2496, 383, 17, 1, true);
	AddKoppa(3136, 383, 18, 0, true);
	AddKoppa(3552, 383, 17, 1, true);
	AddKoppa(4288, 383, 17, 1, true);
	AddKoppa(4480, 383, 17, 1, true);
	AddKoppa(4528, 415, 17, 1, true);
	AddKoppa(4576, 383, 17, 1, true);
	AddKoppa(4800, 383, 17, 1, true);
	AddKoppa(4848, 383, 17, 1, true);
	AddKoppa(5184, 383, 17, 1, true);
	AddKoppa(5232, 383, 17, 1, true);
	AddKoppa(5280, 383, 17, 1, true);
	AddKoppa(5600, 383, 17, 1, true);
}

void Map::LoadMinionLevel_3_3()
{
	ClearMinion();

	AddGoombas(832, 191, 5, true);

	AddKoppa(1664, 191, 17, 1, true);
	AddKoppa(1728, 319, 17, 1, true);
	AddKoppa(2336, 383, 17, 1, true);
	AddKoppa(3640, 159, 18, 3, false);
	AddKoppa(3968, 287, 17, 1, true);
	AddKoppa(4032, 287, 17, 1, true);
}

void Map::LoadMinionLevel_3_4()
{
	ClearMinion();

	AddBowser(4320, 255);
	AddToad(4896, 351, false);

	AddFireBall(608, 351, 6, rand() % 360, true);
	AddFireBall(768, 351, 6, rand() % 360, true);
	AddFireBall(928, 351, 6, rand() % 360, true);
	AddFireBall(1728, 351, 6, rand() % 360, true);
	AddFireBall(1728, 159, 6, rand() % 360, false);
	AddFireBall(2048, 351, 6, rand() % 360, true);
	AddFireBall(2048, 159, 6, rand() % 360, false);
	AddFireBall(2560, 351, 6, rand() % 360, true);
	AddFireBall(2560, 159, 6, rand() % 360, false);
}

void Map::LoadMinionLevel_4_1()
{
	ClearMinion();

	AddLakito(832, 95, 207 * 32);
}

void Map::LoadMinionLevel_4_2()
{
	ClearMinion();

	AddGoombas(1376, 255, 7, true);
	AddGoombas(1424, 255, 7, true);
	AddGoombas(1472, 255, 7, true);

	AddKoppa(2464, 383, 14, 1, true);
	AddKoppa(3200, 383, 14, 1, true);
	AddKoppa(3248, 383, 14, 1, true);
	AddKoppa(4384, 383, 14, 1, true);
	AddKoppa(5376, 383, 14, 1, true);
	AddKoppa(5424, 383, 14, 1, true);

	AddBeetle(2656, 383, 55, true);
	AddBeetle(2816, 383, 55, true);
	AddBeetle(4928, 287, 55, true);
	AddBeetle(5728, 383, 55, true);
}

void Map::LoadMinionLevel_4_3()
{
	ClearMinion();

	AddKoppa(894, 255, 11, 1, true);
	AddKoppa(928, 255, 11, 1, true);
	AddKoppa(1120, 95, 12, 3, false);
	AddKoppa(1248, 351, 11, 1, true);
	AddKoppa(2176, 383, 11, 1, true);
	AddKoppa(2496, 127, 11, 1, true);
}

void Map::LoadMinionLevel_4_4()
{
	ClearMinion();

	AddBowser(5344, 255);
	AddToad(5952, 351, false);

	AddFireBall(1696, 223, 6, rand() % 360, true);
	AddFireBall(1920, 319, 6, rand() % 360, false);
	AddFireBall(3680, 223, 6, rand() % 360, true);
	AddFireBall(3904, 351, 6, rand() % 360, true);
	AddFireBall(5184, 351, 6, rand() % 360, true);
}

void Map::LoadMinionLevel_5_1()
{
	ClearMinion();

	AddGoombas(608, 383, 5, true);
	AddGoombas(656, 383, 5, true);
	AddGoombas(704, 383, 5, true);
	AddGoombas(960, 383, 5, true);
	AddGoombas(1008, 383, 5, true);
	AddGoombas(1056, 383, 5, true);
	AddGoombas(2080, 383, 5, true);
	AddGoombas(2128, 383, 5, true);
	AddGoombas(2176, 383, 5, true);
	AddGoombas(2432, 383, 5, true);
	AddGoombas(2480, 383, 5, true);
	AddGoombas(3296, 383, 5, true);
	AddGoombas(3344, 383, 5, true);
	AddGoombas(3392, 383, 5, true);
	AddGoombas(3872, 383, 5, true);
	AddGoombas(3920, 383, 5, true);
	AddGoombas(3968, 383, 5, true);
	AddGoombas(4320, 383, 5, true);
	AddGoombas(4368, 383, 5, true);
	AddGoombas(4416, 383, 5, true);

	AddKoppa(512, 383, 11, 1, true);
	AddKoppa(1312, 383, 11, 1, true);
	AddKoppa(1360, 383, 11, 1, true);
	AddKoppa(1952, 351, 12, 0, true);
	AddKoppa(2784, 351, 12, 0, true);
	AddKoppa(4064, 383, 11, 1, true);
	AddKoppa(4608, 383, 11, 1, true);
	AddKoppa(4656, 383, 11, 1, true);
	AddKoppa(5696, 383, 12, 0, true);
	AddKoppa(5824, 255, 11, 1, true);
}

void Map::LoadMinionLevel_5_2()
{
	ClearMinion();

	AddGoombas(4576, 319, 5, true);
	AddGoombas(4640, 255, 5, true);
	AddGoombas(7520, 383, 5, true);
	AddGoombas(7568, 383, 5, true);

	AddKoppa(3296, 383, 11, 1, true);
	AddKoppa(3840, 351, 12, 0, true);
	AddKoppa(5952, 319, 12, 0, true);
	AddKoppa(7584, 127, 11, 1, true);
	AddKoppa(7776, 351, 12, 0, true);
	AddKoppa(7872, 383, 12, 0, true);
	AddKoppa(8512, 223, 12, 0, true);

	AddBeetle(6912, 383, 53, true);
	AddBeetle(6948, 383, 53, true);
	AddBeetle(6984, 383, 53, true);

	AddHammerBro(4032, 255);
	AddHammerBro(5152, 223);
	AddHammerBro(6400, 223);
	AddHammerBro(6528, 95);

	AddSquid(544, 351);
	AddSquid(1088, 351);
	AddSquid(1392, 351);
	
	AddCheep(880, 191, 0, 1);
	AddCheep(1244, 351, 0, 1);
	AddCheep(1552, 287, 0, 1);
	AddCheep(1712, 127, 0, 1);
}

void Map::LoadMinionLevel_5_3()
{
	ClearMinion();

	AddGoombas(1408, 95, 5, true);
	AddGoombas(1472, 95, 5, true);
	AddGoombas(2560, 159, 5, true);

	AddKoppa(952, 127, 11, 1, true);
	AddKoppa(2360, 127, 12, 3, false);
	AddKoppa(3512, 191, 11, 1, true);
	AddKoppa(3640, 159, 12, 3, false);
	AddKoppa(4248, 383, 11, 1, true);
}

void Map::LoadMinionLevel_5_4()
{
	ClearMinion();

	AddBowser(4320, 255);
	AddToad(4896, 351, false);

	AddFireBall(736, 255, 12, rand() % 360, true);
	AddFireBall(1376, 447, 6, rand() % 360, false);
	AddFireBall(1568, 287, 6, rand() % 360, true);
	AddFireBall(1760, 447, 6, rand() % 360, false);
	AddFireBall(1760, 159, 6, rand() % 360, true);
	AddFireBall(1952, 287, 6, rand() % 360, true);
	AddFireBall(2144, 447, 6, rand() % 360, true);
	AddFireBall(2336, 287, 6, rand() % 360, true);
	AddFireBall(2624, 191, 6, rand() % 360, true);
	AddFireBall(2944, 319, 6, rand() % 360, false);
	AddFireBall(3296, 383, 6, rand() % 360, true);
}

void Map::LoadMinionLevel_6_1()
{
	ClearMinion();

	AddLakito(736, 95, 176 * 32);
}

void Map::LoadMinionLevel_6_2()
{
	ClearMinion();

	AddGoombas(4864, 127, 5, true);
	AddGoombas(8128, 383, 5, true);

	AddKoppa(3552, 383, 11, 1, true);
	AddKoppa(4096, 351, 12, 0, true);
	AddKoppa(9312, 95, 12, 0, true);

	AddBeetle(4448, 383, 53, true);
	AddBeetle(5664, 383, 53, true);
	AddBeetle(6560, 127, 53, true);
	AddBeetle(7936, 383, 53, true);

	AddSquid(544, 319);
	AddSquid(1088, 319);
	AddSquid(1392, 319);

	AddCheep(880, 159, 0, 1);
	AddCheep(1244, 319, 0, 1);
	AddCheep(1552, 255, 0, 1);
	AddCheep(1712, 95, 0, 1);
}

void Map::LoadMinionLevel_6_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_6_4()
{
	ClearMinion();

	AddBowser(4320, 255, true);
	AddToad(4896, 255, false);

	AddFireBall(736, 191, 6, rand() % 360, true);
	AddFireBall(960, 319, 6, rand() % 360, true);
	AddFireBall(1184, 191, 6, rand() % 360, true);
	AddFireBall(1568, 191, 6, rand() % 360, true);
	AddFireBall(1920, 191, 6, rand() % 360, true);
	AddFireBall(2144, 191, 6, rand() % 360, true);
	AddFireBall(2432, 287, 6, rand() % 360, true);
	AddFireBall(2560, 127, 6, rand() % 360, false);
	AddFireBall(2688, 287, 6, rand() % 360, true);
	AddFireBall(2816, 127, 6, rand() % 360, false);
	AddFireBall(2944, 287, 6, rand() % 360, true);
}

void Map::LoadMinionLevel_7_1()
{
	ClearMinion();

	AddKoppa(832, 351, 12, 0, true);
	AddKoppa(1408, 319, 12, 0, true);
	AddKoppa(1696, 383, 12, 0, true);
	AddKoppa(2080, 351, 12, 0, true);
	AddKoppa(3648, 383, 11, 1, true);

	AddBeetle(5408, 127, 53, true);

	AddHammerBro(2720, 223);
	AddHammerBro(2784, 95);
	AddHammerBro(4384, 223);
	AddHammerBro(4320, 351);
}

void Map::LoadMinionLevel_7_2()
{
	ClearMinion();

	AddSquid(704, 351);
	AddSquid(768, 223);
	AddSquid(1472, 287);
	AddSquid(1664, 223);
	AddSquid(1760, 319);
	AddSquid(2464, 191);
	AddSquid(2656, 255);
	AddSquid(2880, 351);
	AddSquid(3008, 95);
	AddSquid(3360, 351);
	AddSquid(4800, 255);
	AddSquid(5536, 351);
	AddSquid(5728, 351);

	AddCheep(2428, 319, 0, 1);
	AddCheep(2524, 223, 0, 1);
	AddCheep(2620, 355, 0, 1);
	AddCheep(3022, 191, 0, 1);
	AddCheep(3260, 319, 0, 1);
	AddCheep(3112, 95, 0, 1);
	AddCheep(3752, 127, 0, 1);
	AddCheep(4088, 319, 0, 1);
	AddCheep(4200, 347, 0, 1);
	AddCheep(4368, 255, 0, 1);
	AddCheep(4648, 319, 0, 1);
	AddCheep(4796, 187, 0, 1);
	AddCheep(5248, 95, 0, 1);
	AddCheep(5344, 351, 0, 1);
	AddCheep(5600, 251, 0, 1);
	AddCheep(5856, 127, 0, 1);
	AddCheep(5968, 223, 0, 1);
}

void Map::LoadMinionLevel_7_3()
{
	ClearMinion();

	AddKoppa(1664, 255, 12, 0, true);
	AddKoppa(4480, 223, 12, 0, true);
	AddKoppa(4992, 287, 12, 0, true);

	AddKoppa(2528, 287, 11, 1, true);
	AddKoppa(3040, 287, 11, 1, true);
	AddKoppa(3808, 383, 11, 1, true);
}

void Map::LoadMinionLevel_7_4()
{
	ClearMinion();

	AddBowser(8416, 255, true);
	AddToad(8992, 351, false);
}

void Map::LoadMinionLevel_8_1()
{
	ClearMinion();

	AddGoombas(736, 383, 5, true);
	AddGoombas(784, 383, 5, true);
	AddGoombas(832, 383, 5, true);
	AddGoombas(960, 383, 5, true);
	AddGoombas(1008, 383, 5, true);
	AddGoombas(1056, 383, 5, true);
	AddGoombas(2208, 383, 5, true);
	AddGoombas(2256, 383, 5, true);
	AddGoombas(2304, 383, 5, true);
	AddGoombas(3456, 383, 5, true);
	AddGoombas(3504, 383, 5, true);
	AddGoombas(3552, 383, 5, true);
	AddGoombas(4736, 383, 5, true);
	AddGoombas(4784, 383, 5, true);
	AddGoombas(4832, 383, 5, true);
	AddGoombas(7424, 383, 5, true);
	AddGoombas(7472, 383, 5, true);
	AddGoombas(7520, 383, 5, true);
	AddGoombas(8224, 383, 5, true);
	AddGoombas(8272, 383, 5, true);
	AddGoombas(8320, 383, 5, true);
	AddGoombas(8448, 383, 5, true);
	AddGoombas(8480, 383, 5, true);
	AddGoombas(8544, 383, 5, true);
	AddGoombas(8704, 383, 5, true);
	AddGoombas(8752, 383, 5, true);

	AddKoppa(1376, 383, 11, 1, true);
	AddKoppa(1424, 383, 11, 1, true);
	AddKoppa(1952, 383, 11, 1, true);
	AddKoppa(3808, 383, 11, 1, true);
	AddKoppa(3968, 383, 11, 1, true);
	AddKoppa(4016, 383, 11, 1, true);
	AddKoppa(4064, 383, 11, 1, true);
	AddKoppa(4160, 383, 11, 1, true);
	AddKoppa(4208, 383, 11, 1, true);
	AddKoppa(4356, 383, 11, 1, true);
	AddKoppa(5152, 351, 12, 0, true);
	AddKoppa(5504, 319, 12, 0, true);
	AddKoppa(5664, 383, 11, 1, true);
	AddKoppa(6672, 383, 11, 1, true);
	AddKoppa(9760, 383, 11, 1, true);
	AddKoppa(10624, 383, 11, 1, true);
	AddKoppa(10848, 383, 11, 1, true);
	AddKoppa(10896, 383, 11, 1, true);
	AddKoppa(10944, 383, 11, 1, true);

	AddBeetle(576, 383, 53, true);
	AddBeetle(2592, 383, 53, true);
	AddBeetle(8128, 383, 53, true);
	AddBeetle(9056, 383, 53, true);
}

void Map::LoadMinionLevel_8_2()
{
	ClearMinion();

	AddGoombas(5888, 287, 5, true);
	AddGoombas(5952, 223, 5, true);

	AddKoppa(568, 287, 12, 0, true);
	AddKoppa(768, 127, 12, 0, true);
	AddKoppa(1824, 351, 12, 0, true);
	AddKoppa(2112, 351, 12, 0, true);
	AddKoppa(2208, 351, 12, 0, true);
	AddKoppa(2944, 319, 12, 0, true);
	AddKoppa(3040, 351, 12, 0, true);
	AddKoppa(4448, 383, 12, 0, true);
	AddKoppa(5440, 319, 12, 0, true);
	AddKoppa(5504, 351, 12, 0, true);
	AddKoppa(5600, 255, 12, 0, true);
	AddKoppa(6496, 191, 12, 0, true);

	AddBeetle(3552, 383, 53, true);
	AddBeetle(3872, 383, 53, true);
	AddBeetle(3936, 383, 53, true);
	AddBeetle(6048, 383, 53, true);

	AddLakito(512, 95, 216 * 32);
}

void Map::LoadMinionLevel_8_3()
{
	ClearMinion();

	AddKoppa(960, 319, 12, 0, true);
	AddKoppa(2976, 351, 12, 0, true);
	AddKoppa(4384, 383, 11, 1, true);

	AddHammerBro(2016, 351);
	AddHammerBro(2080, 223);
	AddHammerBro(3744, 223);
	AddHammerBro(3808, 351);
	AddHammerBro(4672, 351);
	AddHammerBro(5088, 351);
	AddHammerBro(5664, 351);
	AddHammerBro(5920, 351);
}

void Map::LoadMinionLevel_8_4()
{
	ClearMinion();

	AddGoombas(1792, 383, 9, true);
	AddGoombas(1840, 383, 9, true);
	AddGoombas(1888, 383, 9, true);

	AddBeetle(4448, 383, 57, true);
	AddBeetle(4512, 383, 57, true);

	AddHammerBro(10112, 351);

	AddKoppa(4792, 319, 18, 0, true);
	AddKoppa(4856, 351, 18, 0, true);
	AddKoppa(5272, 351, 18, 0, true);
	AddKoppa(5336, 319, 18, 0, true);

	AddBowser(10816, 255, true);
	AddToad(11392, 351, true);

	AddFireBall(13120, 223, 6, rand() % 360, true);
	AddFireBall(13472, 319, 6, rand() % 360, false);
	AddFireBall(13760, 191, 6, rand() % 360, true);
	AddFireBall(14272, 255, 6, rand() % 360, true);
	AddFireBall(14528, 223, 6, rand() % 360, false);

	AddSquid(13376, 351);
	AddSquid(14112, 319);
	AddSquid(14176, 191);
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