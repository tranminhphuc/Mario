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

	LoadMinion();
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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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

	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

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
	//LoadMinion();

	ReadMap("Source/maps/Level8_4.map");
}

void Map::LoadMinion()
{
	ClearMinion();

	fstream f;

	switch (level)
	{
	case Level_1_1:
		f.open("Source/minions/Minion_Level1_1.txt");
		break;
	case Level_1_2:
		f.open("Source/minions/Minion_Level1_2.txt");
		break;
	case Level_1_3:
		f.open("Source/minions/Minion_Level1_3.txt");
		break;
	case Level_1_4:
		f.open("Source/minions/Minion_Level1_4.txt");
		break;
	case Level_2_1:
		f.open("Source/minions/Minion_Level2_1.txt");
		break;
	case Level_2_2:
		f.open("Source/minions/Minion_Level2_2.txt");
		break;
	case Level_2_3:
		f.open("Source/minions/Minion_Level2_3.txt");
		break;
	case Level_2_4:
		f.open("Source/minions/Minion_Level2_4.txt");
		break;
	case Level_3_1:
		f.open("Source/minions/Minion_Level3_1.txt");
		break;
	case Level_3_2:
		f.open("Source/minions/Minion_Level3_2.txt");
		break;
	case Level_3_3:
		f.open("Source/minions/Minion_Level3_3.txt");
		break;
	case Level_3_4:
		f.open("Source/minions/Minion_Level3_4.txt");
		break;
	case Level_4_1:
		f.open("Source/minions/Minion_Level4_1.txt");
		break;
	case Level_4_2:
		f.open("Source/minions/Minion_Level4_2.txt");
		break;
	case Level_4_3:
		f.open("Source/minions/Minion_Level4_3.txt");
		break;
	case Level_4_4:
		f.open("Source/minions/Minion_Level4_4.txt");
		break;
	case Level_5_1:
		f.open("Source/minions/Minion_Level5_1.txt");
		break;
	case Level_5_2:
		f.open("Source/minions/Minion_Level5_2.txt");
		break;
	case Level_5_3:
		f.open("Source/minions/Minion_Level5_3.txt");
		break;
	case Level_5_4:
		f.open("Source/minions/Minion_Level5_4.txt");
		break;
	case Level_6_1:
		f.open("Source/minions/Minion_Level6_1.txt");
		break;
	case Level_6_2:
		f.open("Source/minions/Minion_Level6_2.txt");
		break;
	case Level_6_3:
		f.open("Source/minions/Minion_Level6_3.txt");
		break;
	case Level_6_4:
		f.open("Source/minions/Minion_Level6_4.txt");
		break;
	case Level_7_1:
		f.open("Source/minions/Minion_Level7_1.txt");
		break;
	case Level_7_2:
		f.open("Source/minions/Minion_Level7_2.txt");
		break;
	case Level_7_3:
		f.open("Source/minions/Minion_Level7_3.txt");
		break;
	case Level_7_4:
		f.open("Source/minions/Minion_Level7_4.txt");
		break;
	case Level_8_1:
		f.open("Source/minions/Minion_Level8_1.txt");
		break;
	case Level_8_2:
		f.open("Source/minions/Minion_Level8_2.txt");
		break;
	case Level_8_3:
		f.open("Source/minions/Minion_Level8_3.txt");
		break;
	case Level_8_4:
		f.open("Source/minions/Minion_Level8_4.txt");
		break;
	}

	while (!f.eof())
	{
		string text;
		int x, y;
		int id, minionState;
		int moveSpeed;
		bool moveDirection;

		f >> text;

		if (text == "Goombas" || text == "Beetle")
		{
			f >> text >> x;
			f >> text >> y;
			f >> text >> id;
			minion[GetListID(x)].push_back(new Goombas(x, y, id, true));
		}
		else if (text == "Koopa")
		{
			f >> text >> x;
			f >> text >> y;
			f >> text >> id;
			f >> text >> minionState;
			minion[GetListID(x)].push_back(new Koopa(x, y, id, minionState, true));
		}
		else if (text == "Bowser")
		{
			f >> text >> x;
			f >> text >> y;
			minion[GetListID(x)].push_back(new Bowser(x, y, true));
		}
		else if (text == "Toad")
		{
			bool peach;
			f >> text >> x;
			f >> text >> y;
			f >> text >> peach;
			minion[GetListID(x)].push_back(new Toad(x, y, peach));
		}
		else if (text == "FireBall")
		{
			int radius;
			f >> text >> x;
			f >> text >> y;
			f >> text >> radius;
			f >> text >> moveDirection;
			minion[GetListID(x)].push_back(new FireBall(x + 8, y + 8, 14 * radius, moveDirection));
		}
		else if (text == "Squid")
		{
			f >> text >> x;
			f >> text >> y;
			minion[GetListID(x)].push_back(new Squid(x, y));
		}
		else if (text == "Cheep")
		{
			int minionType;
			f >> text >> x;
			f >> text >> y;
			f >> text >> minionType;
			f >> text >> moveSpeed;
			minion[GetListID(x)].push_back(new Cheep(x, y, minionType, moveSpeed));
		}
		else if (text == "CheepSpawner")
		{
			int xEnd;
			f >> text >> x;
			f >> text >> xEnd;
		}
		else if (text == "HammerBro")
		{
			f >> text >> x;
			f >> text >> y;
			minion[GetListID(x)].push_back(new HammerBro(x, y));
		}
		else if (text == "Lakito")
		{
			int maxX;
			f >> text >> x;
			f >> text >> y;
			f >> text >> maxX;
			minion[GetListID(x)].push_back(new Lakito(x, y, maxX));
		}
		else if (text == "Beetle")
		{
			f >> text >> x;
			f >> text >> y;
			f >> text >> id;
			minion[GetListID((int)x)].push_back(new Beetle(x, y, id, moveDirection));
		}
		f >> text;
	}
}

void Map::AddHammer(int x, int y, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Hammer(x, y));
}

void Map::AddSpikey(int x, int y)
{
	minion[GetListID(x)].push_back(new Spikey(x, y));
}

void Map::AddVine(int x, int y, int id, int minionState)
{
	minion[GetListID(x)].push_back(new Vine());
}

void Map::AddFire(int x, int y, int toY)
{
	minion[GetListID(x)].push_back(new Fire(x, y, toY));
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