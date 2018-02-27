#include "Map.h"
#include "Game.h"

Map::Map()
{
	player = new Player(84, 368);

	xMap = 0;
	yMap = 0;
	mapType = BanNgay;
	level = Level_1_1;

	Game::GetText()->SetFont("Source/images/font.bmp");

	LoadSource();
	LoadGameData();
	LoadLevel();
}

Map::~Map() { }

void Map::Update()
{
	UpdateBlock();
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
					//delete minion[i][j];
					//minion[i].erase(minion[i].begin() + j);
					//continue;
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
	//DrawMinion(window);
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
	Game::GetText()->Draw(window, "MARIO", 54, 16);

	if (player->GetScore() < 100)
		Game::GetText()->Draw(window, "0000" + to_string(player->GetScore()), 54, 32);
	else if(player->GetScore() < 1000)
		Game::GetText()->Draw(window, "000" + to_string(player->GetScore()), 54, 32);
	else if (player->GetScore() < 10000)
		Game::GetText()->Draw(window, "00" + to_string(player->GetScore()), 54, 32);
	else if (player->GetScore() < 100000)
		Game::GetText()->Draw(window, "0" + to_string(player->GetScore()), 54, 32);
	else
		Game::GetText()->Draw(window, to_string(player->GetScore()), 54, 32);

	Game::GetText()->Draw(window, "WORLD", 462, 16);
}

void Map::SetBackGroundColor(sf::RenderWindow & window)
{
	switch (mapType)
	{
	case BanNgay: case HoangHon: case Bien: case Ho: case ThienDuong:
		window.clear(sf::Color(93, 148, 252, 255));
		break;
	case LongDat: case NuiLua: case BuoiToi: case BinhMinh: case DiaNguc:
		window.clear(sf::Color(0, 0, 0, 255));
		break;
	default:
		window.clear(sf::Color(93, 148, 252, 255));
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

int Map::GetX()
{
	return xMap;
}

void Map::SetX(int x)
{
	this->xMap = x;
}

int Map::GetY()
{
	return yMap;
}

void Map::SetY(int y)
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
	if (x <= 0 || x >= Game::gameWidth || y <= 0 || y >= Game::gameHeight)
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

void Map::Destroy(int x, int y, int id, int direction)
{
	if (direction == 0)
	{
		switch (id)
		{
		case 16: case 18:
			if (tile[x][y]->GetMushroom())
			{
				if (tile[x][y]->GetPowerUp())
				{
					/*if (player->GetLevel() == 0)
						minion[GetListID(32 * x)].push_back(new Mushroom(32 * x, Game::gameHeight - 32 * y, true, x, y));
					else
						minion[GetListID(32 * x)].push_back(new Flower(32 * x, Game::gameHeight - 32 * y));*/
				}
				else
				{
					//minion[GetListID(32 * x)].push_back(new Mushroom(32 * x, Game::gameHeight - 32 * y, false, x, y));
				}
			}
			else
			{
				player->SetScore(player->GetScore() + 200);
				player->SetCoin(player->GetCoin() + 1);
			}

			if (tile[x][y]->getNumberOfCoin() > 1)
			{
				tile[x][y]->SetNumberOfCoin(tile[x][y]->getNumberOfCoin() - 1);
			}
			else
			{
				tile[x][y]->SetNumberOfCoin(0);
				SetTileID(x, y, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh ? 17 : mapType == LongDat ? 19 : 20);
			}
			break;
		case 10: case 11: case 12:
			if (tile[x][y]->GetStar())
			{
				SetTileID(x, y, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh ? 17 : mapType == LongDat ? 19 : 20);
				//minion[GetListID(32 * x)].push_back(new Star(32 * x, Game::gameHeight - 32 * y, x, y));
			}
			else if (tile[x][y]->GetMushroom())
			{
				SetTileID(x, y, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh ? 17 : mapType == LongDat ? 19 : 20);

				if (tile[x][y]->GetPowerUp())
				{
					/*if (player->GetLevel() == 0)
						minion[GetListID(32 * x)].push_back(new Mushroom(32 * x, Game::gameHeight - 32 * y, true, x, y));
					else
						minion[GetListID(32 * x)].push_back(new Flower(32 * x, Game::gameHeight - 32 * y));*/
				}
				else
				{
					//minion[GetListID(32 * x)].push_back(new Mushroom(32 * x, Game::gameHeight - 32 * y, true, x, y));
				}
			}
			else if (tile[x][y]->getNumberOfCoin() > 0)
			{
				player->SetScore(player->GetScore() + 200);
				player->SetCoin(player->GetCoin() + 1);
				tile[x][y]->SetNumberOfCoin(tile[x][y]->getNumberOfCoin() - 1);

				if (tile[x][y]->getNumberOfCoin() == 0)
					SetTileID(x, y, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh ? 17 : mapType == LongDat ? 19 : 20);
			}
			else
			{
				if (player->GetLevel() > 0)
				{
					SetTileID(x, y, 0);
				}
			}
			break;
		default:
			break;
		}
	}
	else if (direction == 1)
	{

	}
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

sf::Vector2i Map::getTilePosition(int x, int y)
{
	return sf::Vector2i((int)(x < 0 ? 0 : x), (int)(y > 480 ? 0 : y));
}

void Map::MoveMap(int x)
{
	if (xMap + x > 0)
	{
		//player->MoveX(x - xMap);
		xMap = 0;
	}
	else
	{
		xMap += x;
	}
}

void Map::LoadImage(string file, vector<Object*>& object)
{
	int size;
	bool collision, canDestroy, visible;

	vector<string> name;
	vector<unsigned int> time;

	fstream f;
	f.open(file);

	f >> size;

	for (int i = 0; i < size; i++)
	{
		string image;
		unsigned int delay;

		f >> image;
		f >> delay;

		name.push_back("Source/images/" + image);
		time.push_back(delay);
	}

	f >> collision >> canDestroy >> visible;
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

	DrawGND(0, 14, 69, 2);
	DrawGND(71, 14, 15, 2);
	DrawGND(89, 14, 64, 2);
	DrawGND(155, 14, 85, 2);

	DrawGND2(134, 12, 4, true);
	DrawGND2(140, 12, 4, false);
	DrawGND2(148, 12, 4, true);
	DrawGND2(152, 12, 1, 4);
	DrawGND2(155, 12, 4, false);
	DrawGND2(181, 12, 8, true);
	DrawGND2(189, 12, 1, 8);
	DrawGND2(198, 12, 1, 1);

	DrawBrick(20, 9, 1, 1);
	DrawBrick(22, 9, 1, 1);
	DrawBrick(24, 9, 1, 1);
	DrawBrick(77, 9, 1, 1);
	DrawBrick(79, 9, 1, 1);
	DrawBrick(80, 5, 8, 1);
	DrawBrick(91, 5, 3, 1);
	DrawBrick(94, 9, 1, 1);
	DrawBrick(100, 9, 2, 1);
	DrawBrick(118, 9, 1, 1);
	DrawBrick(121, 5, 3, 1);
	DrawBrick(128, 5, 1, 1);
	DrawBrick(129, 9, 1, 1);
	DrawBrick(131, 5, 1, 1);
	DrawBrick(168, 9, 2, 1);
	DrawBrick(171, 9, 1, 1);

	DrawBlockQ(16, 9, 1);
	DrawBlockQ(21, 9, 1);
	DrawBlockQ(22, 5, 1);
	DrawBlockQ(23, 9, 1);
	DrawBlockQ(78, 9, 1);
	DrawBlockQ(94, 5, 1);
	DrawBlockQ(106, 9, 1);
	DrawBlockQ(109, 9, 1);
	DrawBlockQ(109, 5, 1);
	DrawBlockQ(112, 9, 1);
	DrawBlockQ(129, 5, 2);
	DrawBlockQ(170, 9, 1);

	DrawPipe(28, 12, 1);
	DrawPipe(38, 12, 2);
	DrawPipe(46, 12, 3);
	DrawPipe(57, 12, 3);
	DrawPipe(163, 12, 1);
	DrawPipe(179, 12, 1);

	DrawEnd(198, 11, 9);
	DrawCastleSmall(202, 12);

	
	tile[21][5]->SetMustroom(true);
	tile[78][9]->SetMustroom(true);
	tile[109][5]->SetMustroom(true);
	tile[78][9]->SetPowerUp(false);

	tile[101][9]->SetStar(true);

	tile[94][9]->SetNumberOfCoin(4);

	mapType = LongDat;
	DrawGND(240, 14, 17, 2);

	DrawBrick(240, 12, 1, 11);
	DrawBrick(244, 12, 7, 3);
	DrawBrick(244, 2, 7, 1);

	DrawCoins(244, 9, 7, 1);
	DrawCoins(244, 7, 7, 1);
	DrawCoins(244, 5, 7, 1);

	DrawPipeVertical(255, 12, 11);
	DrawPipeHorizontal(253, 12, 1);

	mapType = BanNgay;
}

void Map::LoadLevel_1_2()
{
	ClearMap();

	mapWidth = 330;
	mapHeight = 15;
	mapTime = 400;
	mapType = LongDat;

	CreateMap();
	
	LoadMinionLevel_1_2();

	DrawGND(0, 14, 80, 2);
	DrawGND(83, 14, 37, 2);
	DrawGND(122, 14, 2, 2);
	DrawGND(126, 14, 12, 2);
	DrawGND(145, 14, 8, 2);
	DrawGND(160, 14, 43, 2);

	DrawGND2(17, 12, 1, 1);
	DrawGND2(19, 12, 1, 2);
	DrawGND2(21, 12, 1, 3);
	DrawGND2(23, 12, 1, 4);
	DrawGND2(25, 12, 1, 4);
	DrawGND2(27, 12, 1, 3);
	DrawGND2(31, 12, 1, 3);
	DrawGND2(33, 12, 1, 2);
	DrawGND2(133, 12, 4, true);
	DrawGND2(137, 12, 1, 4);

	DrawBrick(0, 12, 1, 11);
	DrawBrick(6, 2, 132, 1);
	DrawBrick(29, 8, 1, 1);
	DrawBrick(39, 9, 1, 3);
	DrawBrick(40, 9, 1, 1);
	DrawBrick(41, 9, 1, 3);
	DrawBrick(42, 7, 2, 1);
	DrawBrick(44, 9, 1, 3);
	DrawBrick(45, 9, 1, 1);
	DrawBrick(46, 9, 1, 3);
	DrawBrick(52, 9, 2, 5);
	DrawBrick(54, 11, 2, 3);
	DrawBrick(54, 4, 2, 2);
	DrawBrick(58, 4, 6, 2);
	DrawBrick(58, 9, 6, 1);
	DrawBrick(62, 8, 2, 4);
	DrawBrick(66, 4, 4, 2);
	DrawBrick(67, 9, 1, 5);
	DrawBrick(68, 9, 1, 1);
	DrawBrick(69, 9, 1, 2);
	DrawBrick(72, 9, 2, 5);
	DrawBrick(76, 9, 4, 1);
	DrawBrick(76, 4, 4, 2);
	DrawBrick(84, 8, 6, 2);
	DrawBrick(122, 12, 2, 3);
	DrawBrick(145, 8, 6, 1);
	DrawBrick(160, 12, 17, 3);
	DrawBrick(161, 2, 7, 1);
	DrawBrick(170, 9, 7, 8);
	DrawBrick(177, 2, 10, 1);
	DrawBrick(190, 12, 13, 13);

	DrawBlockQ(10, 9, 5);

	DrawCoins(40, 8, 1, 1);
	DrawCoins(41, 5, 4, 1);
	DrawCoins(45, 8, 1, 1);
	DrawCoins(58, 8, 4, 1);
	DrawCoins(68, 8, 1, 1);
	DrawCoins(84, 5, 6, 1);

	DrawPipe(103, 12, 2);
	DrawPipe(109, 12, 3);
	DrawPipe(115, 12, 1);
	DrawPipe(178, 12, 2);
	DrawPipe(182, 12, 2);
	DrawPipe(186, 12, 2);

	DrawPipeVertical(168, 9, 8);
	DrawPipeHorizontal(166, 9, 1);
	
	tile[10][9]->SetMustroom(true);
	tile[69][8]->SetMustroom(true);
	tile[89][2]->SetMustroom(true);
	tile[150][8]->SetMustroom(true);
	tile[89][2]->SetPowerUp(false);

	tile[46][7]->SetStar(true);

	tile[29][8]->SetNumberOfCoin(10);
	tile[73][8]->SetNumberOfCoin(8);

	mapType = BanNgay;
	DrawGND(210, 14, 24, 2);

	DrawPipe(222, 12, 3);
	DrawPipeHorizontal(220, 12, 1);

	DrawCastleSmall(210, 12);

	mapType = LongDat;
	DrawGND(240, 14, 17, 2);

	DrawBrick(240, 12, 1, 11);
	DrawBrick(243, 9, 10, 1);
	DrawBrick(243, 5, 10, 4);
	DrawBrick(253, 10, 2, 9);

	DrawCoins(243, 12, 9, 1);
	DrawCoins(244, 8, 8, 1);

	DrawPipeVertical(255, 12, 11);
	DrawPipeHorizontal(253, 12, 1);

	tile[252][9]->SetNumberOfCoin(10);

	mapType = BanNgay;
	DrawGND(281, 14, 42, 2);

	DrawGND2(286, 12, 8, true);
	DrawGND2(294, 12, 1, 8);
	DrawGND2(303, 12, 1, 1);

	DrawPipe(284, 12, 1);

	DrawEnd(303, 11, 9);
	DrawCastleSmall(307, 12);

	mapType = LongDat;
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

	DrawGND(0, 14, 16, 2);
	DrawGND(129, 14, 47, 2);

	DrawGND2(138, 12, 2, 4);
	DrawGND2(140, 12, 2, 6);
	DrawGND2(142, 12, 2, 8);
	DrawGND2(152, 12, 1, 1);

	DrawBlockQ(59, 10, 1);

	DrawCoins(27, 4, 3, 1);
	DrawCoins(33, 11, 1, 1);
	DrawCoins(37, 2, 2, 1);
	DrawCoins(50, 6, 2, 1);
	DrawCoins(60, 4, 4, 1);
	DrawCoins(85, 5, 2, 1);
	DrawCoins(93, 4, 2, 1);
	DrawCoins(97, 4, 2, 1);
	DrawCoins(113, 12, 3, 1);
	DrawCoins(120, 5, 2, 1);

	DrawT(18, 14, 4, 3);
	DrawT(24, 14, 8, 6);
	DrawT(26, 8, 5, 4);
	DrawT(32, 14, 3, 3);
	DrawT(35, 14, 5, 7);
	DrawT(40, 14, 7, 11);
	DrawT(50, 14, 4, 2);
	DrawT(59, 14, 5, 2);
	DrawT(60, 12, 4, 8);
	DrawT(65, 14, 5, 2);
	DrawT(70, 14, 3, 6);
	DrawT(76, 14, 6, 9);
	DrawT(98, 14, 4, 4);
	DrawT(104, 14, 8, 8);
	DrawT(113, 14, 3, 2);
	DrawT(116, 14, 4, 6);
	DrawT(122, 14, 4, 6);

	DrawEnd(152, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(155, 12);
	DrawCastleWall(164, 12, 12, 6);

	tile[59][10]->SetMustroom(true);	

	mapType = BanNgay;
}

void Map::LoadLevel_1_4()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_1_4();

	DrawGND(0, 14, 3, 8);
	DrawGND(0, 4, 24, 3);
	DrawGND(3, 14, 1, 7);
	DrawGND(4, 14, 1, 6);
	DrawGND(5, 14, 8, 5);
	DrawGND(15, 14, 11, 5);
	DrawGND(23, 5, 1, 4);
	DrawGND(24, 2, 13, 1);
	DrawGND(29, 14, 3, 5);
	DrawGND(35, 14, 37, 6);
	DrawGND(37, 5, 35, 4);
	DrawGND(72, 14, 32, 5);
	DrawGND(72, 2, 91, 1);
	DrawGND(80, 3, 1, 1);
	DrawGND(88, 3, 1, 1);
	DrawGND(97, 4, 7, 2);
	DrawGND(104, 14, 24, 2);
	DrawGND(116, 12, 4, 3);
	DrawGND(123, 12, 5, 3);
	DrawGND(123, 4, 5, 2);
	DrawGND(141, 14, 3, 6);
	DrawGND(142, 5, 2, 3);
	DrawGND(144, 14, 19, 2);

	DrawLava(13, 14, 2, 3);
	DrawLava(26, 14, 3, 2);
	DrawLava(32, 14, 3, 2);
	DrawLava(128, 14, 13, 2);

	DrawBlockQ(30, 6, 1);

	DrawBridge(128, 10, 13);

	tile[23][6]->SetID(16);
	tile[30][10]->SetID(16);
	tile[37][6]->SetID(16);
	tile[49][6]->SetID(16);
	tile[60][6]->SetID(16);
	tile[67][6]->SetID(16);
	tile[76][9]->SetID(16);
	tile[80][4]->SetID(16);
	tile[84][9]->SetID(16);
	tile[88][4]->SetID(16);
	tile[92][9]->SetID(16);

	mapType = NuiLua;
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

	DrawGND(0, 14, 92, 2);
	DrawGND(96, 14, 10, 2);
	DrawGND(109, 14, 30, 2);
	DrawGND(142, 14, 10, 2);
	DrawGND(154, 14, 70, 2);

	DrawGND2(20, 12, 5, true);
	DrawGND2(34, 12, 1, 4);
	DrawGND2(35, 12, 1, 2);
	DrawGND2(154, 12, 1, 3);
	DrawGND2(190, 12, 2, 10);
	DrawGND2(200, 12, 1, 1);

	DrawBrick(15, 9, 3, 1);
	DrawBrick(28, 5, 4, 1);
	DrawBrick(68, 9, 1, 1);
	DrawBrick(69, 5, 4, 1);
	DrawBrick(81, 5, 5, 1);
	DrawBrick(92, 5, 4, 1);
	DrawBrick(125, 5, 4, 1);
	DrawBrick(161, 9, 1, 1);
	DrawBrick(164, 5, 5, 1);
	DrawBrick(172, 5, 1, 1);
	DrawBrick(185, 9, 2, 1);

	DrawBlockQ(53, 9, 5);
	DrawBlockQ(53, 5, 5);
	DrawBlockQ(79, 9, 4);
	DrawBlockQ(85, 9, 3);
	DrawBlockQ(173, 9, 1);

	DrawPipe(46, 12, 3);
	DrawPipe(74, 12, 3);
	DrawPipe(103, 12, 3);
	DrawPipe(115, 12, 1);
	DrawPipe(122, 12, 3);
	DrawPipe(126, 12, 3);
	DrawPipe(130, 12, 4);
	DrawPipe(176, 12, 2);

	DrawEnd(200, 11, 9);
	DrawCastleSmall(204, 12);
	DrawCastleBig(-2, 12);

	tile[16][9]->SetMustroom(true);
	tile[28][5]->SetMustroom(true);
	tile[53][9]->SetMustroom(true);
	tile[125][5]->SetMustroom(true);
	tile[172][5]->SetMustroom(true);
	tile[28][5]->SetPowerUp(false);

	tile[69][5]->SetStar(true);

	tile[161][9]->SetNumberOfCoin(7);

	mapType = LongDat;
	DrawGND(230, 14, 17, 2);

	DrawBrick(230, 12, 1, 11);
	DrawBrick(234, 12, 7, 3);
	DrawBrick(234, 2, 7, 1);

	DrawCoins(234, 9, 7, 1);
	DrawCoins(234, 7, 7, 1);
	DrawCoins(235, 5, 5, 1);

	DrawPipeVertical(245, 12, 11);
	DrawPipeHorizontal(243, 12, 1);

	mapType = BanNgay;
	DrawBonus(270, 13, 4);
	DrawBonus(275, 13, 57);
	DrawBonusEnd(332);

	DrawCoins(285, 6, 16, 1);
	DrawCoins(302, 4, 3, 1);
	DrawCoins(306, 5, 16, 1);
	DrawCoins(323, 4, 3, 1);
	DrawCoins(333, 12, 3, 1);

	mapType = BanNgay;
}

void Map::LoadLevel_2_2()
{
	ClearMap();

	mapWidth = 320;
	mapHeight = 15;
	mapTime = 400;
	mapType = Bien;

	CreateMap();
	underWater = true;

	LoadMinionLevel_2_2();

	DrawWater(0, 14, 200, 13);
	DrawPipeHorizontal(189, 8, 1);

	DrawGND(0, 14, 66, 2);
	DrawGND(18, 9, 3, 1);
	DrawGND(42, 9, 2, 1);
	DrawGND(64, 12, 1, 3);
	DrawGND(65, 12, 1, 5);
	DrawGND(71, 14, 60, 2);
	DrawGND(71, 12, 1, 5);
	DrawGND(72, 12, 1, 3);
	DrawGND(78, 12, 2, 3);
	DrawGND(78, 4, 2, 3);
	DrawGND(82, 5, 3, 1);
	DrawGND(102, 9, 2, 1);
	DrawGND(115, 8, 2, 1);
	DrawGND(129, 12, 1, 4);
	DrawGND(130, 12, 1, 2);
	DrawGND(131, 4, 1, 3);
	DrawGND(132, 4, 8, 1);
	DrawGND(140, 14, 17, 2);
	DrawGND(140, 12, 1, 2);
	DrawGND(141, 12, 1, 4);
	DrawGND(156, 12, 1, 8);
	DrawGND(157, 5, 2, 1);
	DrawGND(162, 5, 2, 1);
	DrawGND(164, 12, 1, 8);
	DrawGND(164, 14, 38, 2);
	DrawGND(172, 9, 5, 1);
	DrawGND(172, 5, 5, 1);
	DrawGND(180, 9, 4, 1);
	DrawGND(180, 5, 4, 1);
	DrawGND(185, 12, 17, 1);
	DrawGND(186, 11, 16, 1);
	DrawGND(187, 10, 15, 1);
	DrawGND(188, 9, 14, 1);
	DrawGND(188, 5, 14, 1);
	DrawGND(189, 5, 4, 1);
	DrawGND(190, 8, 12, 3);

	DrawCoins(14, 12, 2, 1);
	DrawCoins(27, 5, 3, 1);
	DrawCoins(36, 12, 3, 1);
	DrawCoins(67, 8, 3, 1);
	DrawCoins(101, 11, 3, 1);
	DrawCoins(113, 6, 3, 1);
	DrawCoins(133, 11, 1, 1);
	DrawCoins(134, 12, 3, 1);
	DrawCoins(137, 11, 1, 1);
	DrawCoins(159, 9, 3, 1);
	DrawCoins(159, 12, 3, 1);

	mapType = BanNgay;
	DrawGND(220, 14, 24, 2);

	DrawPipe(232, 12, 3);
	DrawPipeHorizontal(230, 12, 1);

	DrawCastleSmall(220, 12);

	mapType = BanNgay;
	DrawGND(271, 14, 42, 2);

	DrawGND2(276, 12, 8, true);
	DrawGND2(284, 12, 1, 8);
	DrawGND2(293, 12, 1, 1);

	DrawPipe(274, 12, 1);

	DrawEnd(293, 11, 9);
	DrawCastleSmall(297, 12);

	mapType = Bien;
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

	DrawGND(0, 14, 7, 2);
	DrawGND(207, 14, 43, 2);

	DrawGND2(10, 12, 3, true);
	DrawGND2(13, 12, 2, 3);
	DrawGND2(31, 14, 1, 5);
	DrawGND2(47, 14, 1, 5);
	DrawGND2(63, 14, 1, 5);
	DrawGND2(68, 14, 1, 5);
	DrawGND2(79, 14, 1, 5);
	DrawGND2(84, 14, 1, 5);
	DrawGND2(95, 14, 1, 5);
	DrawGND2(99, 14, 1, 6);
	DrawGND2(105, 14, 1, 6);
	DrawGND2(127, 14, 1, 5);
	DrawGND2(143, 14, 1, 5);
	DrawGND2(146, 14, 1, 3);
	DrawGND2(155, 14, 1, 3);
	DrawGND2(159, 14, 1, 5);
	DrawGND2(168, 14, 1, 5);
	DrawGND2(183, 14, 1, 5);
	DrawGND2(193, 12, 1, 3);
	DrawGND2(194, 12, 3, false);
	DrawGND2(208, 12, 8, true);
	DrawGND2(216, 12, 1, 8);
	DrawGND2(225, 12, 1, 1);

	DrawBlockQ(102, 5, 1);

	DrawCoins(36, 5, 4, 1);
	DrawCoins(55, 5, 1, 1);
	DrawCoins(57, 5, 1, 1);
	DrawCoins(59, 5, 1, 1);
	DrawCoins(56, 6, 1, 1);
	DrawCoins(58, 6, 1, 1);
	DrawCoins(72, 5, 1, 1);
	DrawCoins(73, 4, 2, 1);
	DrawCoins(75, 5, 1, 1);
	DrawCoins(97, 5, 3, 1);
	DrawCoins(108, 5, 3, 1);
	DrawCoins(133, 5, 6, 1);
	DrawCoins(149, 8, 4, 1);
	DrawCoins(173, 6, 6, 1);

	DrawT(8, 14, 8, 2);
	DrawT(112, 14, 8, 2);
	DrawT(192, 14, 13, 2);

	DrawBridge2(15, 10, 16);
	DrawBridge2(32, 10, 15);
	DrawBridge2(48, 10, 15);
	DrawBridge2(69, 10, 10);
	DrawBridge2(85, 10, 10);
	DrawBridge2(100, 9, 5);
	DrawBridge2(122, 10, 3);
	DrawBridge2(128, 10, 15);
	DrawBridge2(147, 12, 8);
	DrawBridge2(160, 10, 8);
	DrawBridge2(171, 10, 2);
	DrawBridge2(175, 10, 2);
	DrawBridge2(179, 10, 2);
	DrawBridge2(184, 10, 9);

	DrawEnd(225, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(228, 12);
	DrawCastleWall(237, 12, 13, 6);

	tile[102][5]->SetMustroom(true);

	mapType = BanNgay;
}

void Map::LoadLevel_2_4()
{
	ClearMap();

	mapWidth = 190;
	mapHeight = 15;
	mapTime = 300;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_2_4();

	DrawGND(0, 14, 16, 5);
	DrawGND(0, 4, 16, 3);
	DrawGND(0, 9, 5, 1);
	DrawGND(0, 8, 4, 1);
	DrawGND(0, 7, 3, 1);
	DrawGND(18, 9, 2, 1);
	DrawGND(22, 7, 3, 1);
	DrawGND(27, 9, 2, 1);
	DrawGND(32, 14, 52, 2);
	DrawGND(32, 12, 2, 3);
	DrawGND(34, 5, 49, 4);
	DrawGND(37, 9, 37, 1);
	DrawGND(80, 12, 4, 3);
	DrawGND(92, 14, 17, 2);
	DrawGND(92, 12, 7, 3);
	DrawGND(93, 4, 6, 3);
	DrawGND(108, 12, 1, 3);
	DrawGND(111, 14, 2, 5);
	DrawGND(115, 12, 5, 3);
	DrawGND(115, 14, 13, 2);
	DrawGND(115, 4, 13, 3);
	DrawGND(122, 12, 2, 3);
	DrawGND(126, 12, 2, 3);
	DrawGND(128, 2, 42, 1);
	DrawGND(141, 14, 29, 2);
	DrawGND(141, 12, 3, 4);
	DrawGND(142, 5, 2, 3);

	DrawLava(16, 14, 16, 2);
	DrawLava(109, 14, 2, 2);
	DrawLava(113, 14, 2, 2);
	DrawLava(128, 14, 13, 2);

	DrawBrick(128, 5, 6, 1);

	DrawBlockQ(23, 3, 1);

	DrawCoins(102, 12, 3, 1);
	DrawCoins(102, 8, 3, 1);

	DrawBridge(128, 10, 13);

	tile[23][7]->SetID(16);
	tile[43][13]->SetID(16);
	tile[49][9]->SetID(16);
	tile[55][5]->SetID(16);
	tile[55][13]->SetID(16);
	tile[61][9]->SetID(16);
	tile[67][13]->SetID(16);
	tile[73][9]->SetID(16);
	tile[82][6]->SetID(16);
	tile[92][10]->SetID(16);
	tile[103][11]->SetID(16);

	tile[23][3]->SetMustroom(true);

	mapType = NuiLua;
}

void Map::LoadLevel_3_1()
{
	ClearMap();

	mapWidth = 375;
	mapHeight = 15;
	mapTime = 400;
	mapType = BuoiToi;

	CreateMap();

	LoadMinionLevel_3_1();

	DrawGND(0, 14, 45, 2);
	DrawGND(48, 14, 29, 2);
	DrawGND(85, 14, 1, 2);
	DrawGND(88, 14, 40, 2);
	DrawGND(132, 14, 10, 2);
	DrawGND(144, 14, 33, 2);
	DrawGND(180, 14, 42, 2);

	DrawGND2(73, 12, 4, true);
	DrawGND2(85, 12, 1, 4);
	DrawGND2(88, 12, 1, 4);
	DrawGND2(89, 12, 1, 2);
	DrawGND2(136, 12, 6, true);
	DrawGND2(174, 12, 1, 3);
	DrawGND2(175, 12, 1, 6);
	DrawGND2(183, 12, 8, true);
	DrawGND2(191, 12, 1, 8);
	DrawGND2(200, 12, 1, 1);

	DrawBrick(26, 9, 3, 1);
	DrawBrick(61, 9, 1, 1);
	DrawBrick(90, 5, 3, 1);
	DrawBrick(111, 9, 12, 1);
	DrawBrick(111, 5, 11, 1);
	DrawBrick(129, 8, 3, 1);
	DrawBrick(129, 5, 3, 1);
	DrawBrick(150, 9, 3, 1);
	DrawBrick(150, 5, 3, 1);
	DrawBrick(155, 9, 3, 1);
	DrawBrick(155, 5, 3, 1);
	DrawBrick(166, 9, 5, 1);

	DrawBlockQ(16, 9, 1);
	DrawBlockQ(19, 8, 1);
	DrawBlockQ(22, 8, 1);
	DrawBlockQ(113, 5, 1);
	DrawBlockQ(117, 5, 1);
	DrawBlockQ(151, 9, 1);
	DrawBlockQ(156, 9, 1);

	DrawPipe(32, 12, 2);
	DrawPipe(38, 12, 3);
	DrawPipe(57, 12, 2);
	DrawPipe(67, 12, 1);
	DrawPipe(103, 12, 3);

	DrawBridge2(77, 9, 8);

	DrawWater(77, 14, 8, 3);
	DrawWater(86, 14, 2, 3);

	DrawEnd(200, 11, 9);
	DrawCastleSmall(204, 12);
	DrawCastleBig(-2, 12);

	tile[22][8]->SetMustroom(true);
	tile[82][5]->SetMustroom(true);
	tile[117][5]->SetMustroom(true);
	tile[156][9]->SetMustroom(true);
	tile[82][5]->SetPowerUp(false);

	tile[90][5]->SetStar(true);

	tile[167][9]->SetNumberOfCoin(8);

	mapType = LongDat;
	DrawGND(240, 14, 17, 2);

	DrawBrick(240, 12, 1, 11);
	DrawBrick(243, 8, 1, 2);
	DrawBrick(243, 6, 2, 1);
	DrawBrick(243, 5, 3, 1);
	DrawBrick(244, 9, 1, 1);
	DrawBrick(245, 8, 1, 1);
	DrawBrick(246, 7, 1, 1);
	DrawBrick(247, 6, 2, 2);
	DrawBrick(249, 7, 1, 1);
	DrawBrick(250, 8, 1, 1);
	DrawBrick(250, 5, 3, 1);
	DrawBrick(251, 9, 1, 1);
	DrawBrick(251, 6, 2, 1);
	DrawBrick(252, 8, 1, 2);

	DrawCoins(244, 8, 1, 1);
	DrawCoins(245, 7, 1, 1);
	DrawCoins(246, 4, 4, 1);
	DrawCoins(246, 6, 1, 1);
	DrawCoins(247, 3, 2, 1);
	DrawCoins(249, 6, 1, 1);
	DrawCoins(250, 7, 1, 1);
	DrawCoins(251, 8, 1, 1);

	DrawPipeVertical(255, 12, 11);
	DrawPipeHorizontal(253, 12, 1);

	tile[245][5]->SetMustroom(true);

	mapType = ThienDuong;
	DrawBonus(270, 13, 4);
	DrawBonus(275, 13, 78);
	DrawBonus(301, 8, 1);
	DrawBonus(320, 8, 1);
	DrawBonus(320, 7, 1);
	DrawBonus(331, 8, 1);
	DrawBonus(331, 7, 1);
	DrawBonus(337, 6, 2);
	DrawBonus(341, 6, 1);
	DrawBonus(343, 6, 1);
	DrawBonus(345, 6, 1);
	DrawBonus(347, 6, 1);
	DrawBonus(349, 6, 1);
	DrawBonusEnd(353);

	DrawCoins(284, 6, 16, 1);
	DrawCoins(303, 6, 16, 1);
	DrawCoins(322, 5, 8, 1);
	DrawCoins(341, 5, 10, 1);
	DrawCoins(355, 11, 3, 1);

	mapType = BuoiToi;
}

void Map::LoadLevel_3_2()
{
	ClearMap();

	mapWidth = 230;
	mapHeight = 15;
	mapTime = 300;
	mapType = BuoiToi;

	CreateMap();

	LoadMinionLevel_3_2();

	DrawGND(0, 14, 80, 2);
	DrawGND(82, 14, 41, 2);
	DrawGND(125, 14, 3, 2);
	DrawGND(130, 14, 100, 2);

	DrawGND2(49, 12, 1, 1);
	DrawGND2(60, 12, 1, 3);
	DrawGND2(75, 12, 1, 2);
	DrawGND2(79, 12, 1, 2);
	DrawGND2(126, 12, 1, 2);
	DrawGND2(192, 12, 8, true);
	DrawGND2(200, 12, 1, 8);
	DrawGND2(209, 12, 1, 1);

	DrawBrick(77, 9, 1, 1);
	DrawBrick(77, 5, 1, 1);
	DrawBrick(126, 6, 1, 1);

	DrawBlockQ(60, 6, 1);

	DrawCoins(55, 9, 3, 1);
	DrawCoins(168, 6, 4, 1);

	DrawPipe(169, 12, 2);

	DrawEnd(209, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleSmall(213, 12);

	tile[60][6]->SetMustroom(true);

	tile[77][5]->SetStar(true);

	tile[77][9]->SetNumberOfCoin(10);

	mapType = BuoiToi;
}

void Map::LoadLevel_3_3()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	mapType = BinhMinh;

	CreateMap();

	LoadMinionLevel_3_3();

	DrawGND(0, 14, 16, 2);
	DrawGND(144, 14, 31, 2);

	DrawGND2(151, 12, 1, 1);

	DrawBlockQ(49, 3, 1);

	DrawT(18, 14, 5, 5);
	DrawT(22, 14, 6, 8);
	DrawT(30, 14, 3, 2);
	DrawT(36, 14, 7, 3);
	DrawT(43, 14, 4, 6);
	DrawT(47, 14, 6, 8);
	DrawT(46, 14, 10, 4);
	DrawT(55, 14, 4, 12);
	DrawT(65, 14, 3, 8);
	DrawT(69, 14, 3, 8);
	DrawT(73, 14, 3, 8);
	DrawT(77, 14, 3, 11);
	DrawT(65, 14, 16, 2);
	DrawT(84, 14, 4, 4);
	DrawT(97, 14, 3, 6);
	DrawT(104, 14, 4, 10);
	DrawT(108, 14, 3, 8);
	DrawT(107, 14, 5, 4);
	DrawT(116, 14, 3, 2);
	DrawT(119, 14, 12, 5);

	DrawCoins(31, 12, 2, 1);
	DrawCoins(37, 6, 1, 1);
	DrawCoins(42, 6, 3, 1);
	DrawCoins(52, 9, 3, 1);
	DrawCoins(56, 2, 2, 1);
	DrawCoins(66, 6, 1, 1);
	DrawCoins(70, 6, 1, 1);
	DrawCoins(74, 6, 1, 1);
	DrawCoins(78, 3, 1, 1);
	DrawCoins(81, 5, 1, 1);
	DrawCoins(88, 5, 1, 1);
	DrawCoins(90, 5, 1, 1);
	DrawCoins(105, 4, 2, 1);
	DrawCoins(108, 10, 1, 1);

	DrawSeeSaw(82, 2, 8);
	DrawSeeSaw(137, 2, 5);

	DrawEnd(151, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(154, 12);
	DrawCastleWall(163, 12, 12, 6);

	tile[49][3]->SetMustroom(true);

	mapType = BinhMinh;
}

void Map::LoadLevel_3_4()
{
	ClearMap();

	mapWidth = 225;
	mapHeight = 15;
	mapTime = 300;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_3_4();

	DrawGND(0, 14, 16, 5);
	DrawGND(0, 4, 16, 3);
	DrawGND(0, 9, 5, 1);
	DrawGND(0, 8, 4, 1);
	DrawGND(0, 7, 3, 1);
	DrawGND(16, 2, 149, 1);
	DrawGND(18, 14, 3, 5);
	DrawGND(23, 14, 3, 5);
	DrawGND(28, 14, 3, 5);
	DrawGND(33, 14, 13, 2);
	DrawGND(33, 14, 2, 5);
	DrawGND(35, 4, 11, 2);
	DrawGND(48, 14, 40, 2);
	DrawGND(53, 12, 3, 1);
	DrawGND(53, 4, 3, 2);
	DrawGND(63, 12, 3, 1);
	DrawGND(63, 4, 3, 2);
	DrawGND(79, 12, 3, 1);
	DrawGND(79, 4, 3, 2);
	DrawGND(90, 4, 6, 2);
	DrawGND(90, 14, 6, 5);
	DrawGND(99, 14, 3, 5);
	DrawGND(105, 14, 3, 5);
	DrawGND(111, 4, 15, 2);
	DrawGND(111, 14, 5, 2);
	DrawGND(116, 14, 2, 2);
	DrawGND(118, 14, 10, 5);
	DrawGND(141, 14, 3, 6);
	DrawGND(142, 5, 2, 3);
	DrawGND(144, 14, 21, 2);

	DrawLava(46, 14, 2, 2);
	DrawLava(48, 14, 40, 2);
	DrawLava(88, 14, 2, 2);
	DrawLava(96, 14, 3, 2);
	DrawLava(102, 14, 3, 2);
	DrawLava(108, 14, 3, 2);
	DrawLava(128, 14, 13, 2);

	DrawBrick(132, 5, 2, 3);

	DrawBlockQ(42, 9, 3);

	DrawCoins(81, 6, 3, 1);

	DrawBridge(128, 10, 13);

	tile[19][11]->SetID(16);
	tile[24][11]->SetID(16);
	tile[29][11]->SetID(16);
	tile[54][5]->SetID(16);
	tile[54][11]->SetID(16);
	tile[64][11]->SetID(16);
	tile[64][5]->SetID(16);
	tile[80][11]->SetID(16);
	tile[80][5]->SetID(16);

	tile[43][9]->SetMustroom(true);

	mapType = NuiLua;
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

	DrawGND(0, 14, 32, 2);
	DrawGND(34, 14, 44, 2);
	DrawGND(82, 14, 67, 2);
	DrawGND(151, 14, 23, 2);
	DrawGND(177, 14, 3, 2);
	DrawGND(182, 14, 8, 2);
	DrawGND(192, 14, 58, 2);

	DrawGND2(103, 12, 1, 3);
	DrawGND2(189, 12, 1, 3);
	DrawGND2(208, 12, 8, true);
	DrawGND2(216, 12, 1, 8);
	DrawGND2(225, 12, 1, 1);

	DrawBrick(149, 9, 2, 1);
	DrawBrick(220, 9, 1, 1);

	DrawBlockQ(25, 9, 1);
	DrawBlockQ(25, 5, 1);
	DrawBlockQ(64, 9, 1);
	DrawBlockQ(64, 5, 1);
	DrawBlockQ(66, 9, 1);
	DrawBlockQ(66, 5, 1);
	DrawBlockQ(90, 9, 4);
	DrawBlockQ(146, 9, 3);
	DrawBlockQ(148, 5, 4);
	DrawBlockQ(151, 9, 3);

	DrawCoins(41, 9, 1, 1);
	DrawCoins(42, 8, 2, 1);
	DrawCoins(44, 9, 1, 1);
	DrawCoins(105, 6, 4, 1);
	DrawCoins(119, 6, 4, 1);
	DrawCoins(135, 6, 4, 1);

	DrawPipe(21, 12, 2);
	DrawPipe(116, 12, 3);
	DrawPipe(132, 12, 3);
	DrawPipe(163, 12, 1);

	DrawEnd(225, 11, 9);
	DrawCastleSmall(229, 12);
	DrawCastleBig(-2, 12);

	tile[25][9]->SetMustroom(true);
	tile[92][5]->SetMustroom(true);
	tile[148][9]->SetMustroom(true);
	tile[92][5]->SetPowerUp(false);

	tile[220][9]->SetNumberOfCoin(6);

	mapType = LongDat;
	DrawGND(250, 14, 17, 2);

	DrawBrick(250, 12, 1, 11);
	DrawBrick(253, 11, 1, 3);
	DrawBrick(253, 12, 10, 1);
	DrawBrick(253, 8, 8, 1);
	DrawBrick(253, 2, 12, 1);
	DrawBrick(254, 9, 6, 1);
	DrawBrick(260, 11, 1, 3);
	DrawBrick(263, 9, 1, 1);

	DrawCoins(253, 12, 10, 1);
	DrawCoins(253, 8, 8, 1);

	DrawPipeVertical(265, 12, 11);
	DrawPipeHorizontal(263, 12, 1);

	tile[263][9]->SetMustroom(true);

	mapType = BanNgay;
}

void Map::LoadLevel_4_2()
{
	ClearMap();

	mapWidth = 435;
	mapHeight = 15;
	mapTime = 400;
	mapType = LongDat;

	CreateMap();

	LoadMinionLevel_4_2();

	DrawGND(0, 14, 11, 2);
	DrawGND(13, 14, 2, 2);
	DrawGND(17, 14, 1, 2);
	DrawGND(21, 14, 36, 2);
	DrawGND(63, 14, 42, 2);
	DrawGND(107, 14, 2, 2);
	DrawGND(111, 14, 2, 2);
	DrawGND(119, 14, 4, 2);
	DrawGND(129, 14, 15, 2);
	DrawGND(146, 14, 9, 2);
	DrawGND(160, 14, 23, 2);
	DrawGND(185, 14, 49, 2);

	DrawGND2(103, 12, 1, 2);
	DrawGND2(104, 12, 1, 3);
	DrawGND2(111, 12, 2, 3);
	DrawGND2(152, 12, 3, true);
	DrawGND2(173, 12, 4, true);

	DrawBrick(0, 12, 1, 11);
	DrawBrick(6, 2, 14, 1);
	DrawBrick(22, 11, 5, 3);
	DrawBrick(27, 9, 2, 1);
	DrawBrick(30, 12, 18, 4);
	DrawBrick(20, 5, 28, 4);
	DrawBrick(48, 2, 9, 1);
	DrawBrick(65, 5, 2, 1);
	DrawBrick(67, 2, 45, 1);
	DrawBrick(76, 9, 2, 1);
	DrawBrick(80, 9, 2, 1);
	DrawBrick(87, 8, 1, 1);
	DrawBrick(119, 9, 4, 1);
	DrawBrick(119, 5, 3, 1);
	DrawBrick(119, 2, 4, 1);
	DrawBrick(128, 2, 27, 1);
	DrawBrick(160, 7, 1, 6);
	DrawBrick(161, 9, 11, 1);
	DrawBrick(161, 5, 15, 4);
	DrawBrick(176, 2, 13, 1);
	DrawBrick(185, 12, 6, 3);
	DrawBrick(191, 12, 18, 11);
	DrawBrick(209, 2, 10, 1);
	DrawBrick(222, 12, 12, 12);

	DrawBlockQ(50, 9, 2);
	DrawBlockQ(54, 9, 3);
	DrawBlockQ(50, 5, 2);

	DrawCoins(27, 12, 3, 1);
	DrawCoins(162, 8, 10, 1);

	DrawPipe(72, 12, 2);
	DrawPipe(78, 12, 6);
	DrawPipe(84, 12, 2);
	DrawPipe(89, 12, 2);
	DrawPipe(107, 12, 3);
	DrawPipe(131, 12, 1);
	DrawPipe(138, 12, 2);
	DrawPipe(142, 12, 3);
	DrawPipe(180, 12, 6);
	DrawPipe(214, 12, 2);

	DrawPipeVertical(189, 9, 8);
	DrawPipeHorizontal(187, 9, 1);

	tile[28][9]->SetMustroom(true);
	tile[55][9]->SetMustroom(true);
	tile[120][5]->SetMustroom(true);
	tile[161][9]->SetMustroom(true);

	tile[81][9]->SetStar(true);

	tile[43][4]->SetNumberOfCoin(8);
	tile[77][9]->SetNumberOfCoin(6);

	mapType = BanNgay;
	DrawGND(240, 14, 24, 2);

	DrawPipe(252, 12, 3);
	DrawPipeHorizontal(250, 12, 1);

	DrawCastleSmall(240, 12);

	mapType = LongDat;
	DrawGND(270, 14, 17, 2);

	DrawBrick(269, 12, 1, 12);
	DrawBrick(270, 12, 1, 11);
	DrawBrick(274, 7, 1, 2);
	DrawBrick(275, 7, 5, 1);
	DrawBrick(280, 7, 1, 6);
	DrawBrick(281, 6, 2, 1);
	DrawBrick(274, 2, 6, 1);
	DrawBrick(284, 7, 1, 1);

	DrawCoins(275, 6, 5, 2);

	DrawPipeVertical(285, 12, 11);
	DrawPipeHorizontal(283, 12, 1);

	tile[284][7]->SetNumberOfCoin(8);

	mapType = ThienDuong;
	DrawGND(310, 14, 4, 2);
	DrawGND(315, 14, 59, 2);

	DrawGND2(350, 12, 9, true);
	DrawGND2(359, 4, 11, 1);
	DrawGND2(372, 12, 2, 11);

	DrawCoins(322, 8, 3, 1);
	DrawCoins(326, 4, 3, 1);
	DrawCoins(332, 4, 3, 1);
	DrawCoins(336, 6, 3, 1);
	DrawCoins(340, 3, 5, 1);
	DrawCoins(345, 9, 2, 1);

	DrawTMush(322, 12, 3, 4);
	DrawTMush(326, 12, 3, 8);
	DrawTMush(328, 12, 3, 2);
	DrawTMush(332, 12, 3, 8);
	DrawTMush(332, 12, 5, 2);
	DrawTMush(336, 12, 3, 6);
	DrawTMush(340, 12, 5, 9);
	DrawTMush(341, 12, 7, 3);

	DrawPipe(360, 12, 2);
	DrawPipe(364, 12, 2);
	DrawPipe(368, 12, 2);

	mapType = BanNgay;
	DrawGND(391, 14, 42, 2);

	DrawGND2(396, 12, 8, true);
	DrawGND2(404, 12, 1, 8);
	DrawGND2(413, 12, 1, 1);

	DrawPipe(394, 12, 1);

	DrawEnd(413, 11, 9);
	DrawCastleSmall(417, 12);

	mapType = LongDat;
}

void Map::LoadLevel_4_3()
{
	ClearMap();

	mapWidth = 171;
	mapHeight = 15;
	mapTime = 300;
	mapType = ThienDuong;

	CreateMap();

	LoadMinionLevel_4_3();

	DrawGND(0, 14, 15, 2);
	DrawGND(141, 14, 30, 2);

	DrawGND2(147, 12, 1, 1);

	DrawBlockQ(43, 2, 1);

	DrawCoins(20, 4, 3, 1);
	DrawCoins(24, 8, 5, 1);
	DrawCoins(38, 11, 3, 1);
	DrawCoins(48, 7, 1, 1);
	DrawCoins(57, 3, 1, 1);
	DrawCoins(67, 6, 3, 1);
	DrawCoins(73, 8, 1, 1);
	DrawCoins(70, 2, 3, 1);
	DrawCoins(96, 7, 1, 1);
	DrawCoins(104, 4, 1, 1);
	DrawCoins(113, 8, 5, 1);

	DrawTMush(16, 14, 5, 2);
	DrawTMush(19, 14, 5, 10);
	DrawTMush(23, 14, 7, 6);
	DrawTMush(32, 14, 3, 11);
	DrawTMush(39, 14, 5, 10);
	DrawTMush(36, 14, 7, 3);
	DrawTMush(44, 14, 3, 6);
	DrawTMush(51, 14, 3, 7);
	DrawTMush(67, 14, 3, 8);
	DrawTMush(65, 14, 5, 2);
	DrawTMush(70, 14, 3, 12);
	DrawTMush(72, 14, 3, 6);
	DrawTMush(74, 14, 5, 10);
	DrawTMush(84, 14, 3, 6);
	DrawTMush(99, 14, 3, 4);
	DrawTMush(105, 14, 3, 5);
	DrawTMush(113, 14, 5, 6);
	DrawTMush(117, 14, 3, 9);
	DrawTMush(121, 14, 7, 2);
	DrawTMush(130, 14, 5, 5);

	DrawSeeSaw(49, 2, 8);
	DrawSeeSaw(81, 2, 9);
	DrawSeeSaw(92, 2, 6);
	DrawSeeSaw(103, 2, 7);

	DrawEnd(147, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(150, 12);
	DrawCastleWall(159, 12, 12, 6);

	tile[43][2]->SetMustroom(true);

	mapType = ThienDuong;
}

void Map::LoadLevel_4_4()
{
	ClearMap();

	mapWidth = 200;
	mapHeight = 15;
	mapTime = 300;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_4_4();

	DrawGND(0, 2, 147, 1);
	DrawGND(0, 4, 6, 2);
	DrawGND(0, 14, 7, 5);
	DrawGND(0, 9, 5, 1);
	DrawGND(0, 8, 4, 1);
	DrawGND(0, 9, 3, 1);
	DrawGND(0, 7, 3, 1);
	DrawGND(9, 14, 2, 5);
	DrawGND(13, 14, 3, 5);
	DrawGND(16, 14, 72, 2);
	DrawGND(18, 9, 6, 4);
	DrawGND(25, 9, 1, 4);
	DrawGND(27, 9, 1, 4);
	DrawGND(29, 9, 1, 4);
	DrawGND(31, 9, 1, 4);
	DrawGND(33, 9, 1, 4);
	DrawGND(35, 9, 3, 4);
	DrawGND(38, 6, 6, 1);
	DrawGND(44, 9, 31, 4);
	DrawGND(77, 5, 3, 3);
	DrawGND(77, 12, 3, 3);
	DrawGND(86, 10, 2, 1);
	DrawGND(89, 8, 2, 1);
	DrawGND(90, 14, 1, 4);
	DrawGND(90, 10, 5, 1);
	DrawGND(91, 10, 4, 1);
	DrawGND(93, 7, 1, 1);
	DrawGND(94, 9, 1, 2);
	DrawGND(95, 7, 1, 2);
	DrawGND(95, 14, 65, 2);
	DrawGND(96, 6, 2, 1);
	DrawGND(96, 10, 48, 1);
	DrawGND(100, 6, 4, 1);
	DrawGND(105, 9, 1, 4);
	DrawGND(106, 6, 2, 1);
	DrawGND(110, 6, 34, 1);
	DrawGND(144, 9, 1, 5);
	DrawGND(145, 4, 2, 3);
	DrawGND(152, 2, 41, 1);
	DrawGND(152, 12, 4, 3);
	DrawGND(158, 12, 2, 3);
	DrawGND(173, 14, 20, 2);
	DrawGND(173, 12, 3, 4);
	DrawGND(174, 5, 2, 3);

	DrawLava(7, 14, 2, 2);
	DrawLava(11, 14, 2, 2);
	DrawLava(88, 14, 2, 2);
	DrawLava(91, 14, 4, 2);
	DrawLava(160, 14, 13, 2);

	DrawPipe(40, 12, 2);

	DrawBridge(160, 10, 13);

	mapType = NuiLua;
}

void Map::LoadLevel_5_1()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 300;
	mapType = HoangHon;

	CreateMap();

	LoadMinionLevel_5_1();

	DrawBulletBill(111, 12, 0);
	DrawBulletBill(159, 12, 0);
	DrawBulletBill(170, 12, 0);

	DrawGND(0, 14, 49, 2);
	DrawGND(51, 14, 41, 2);
	DrawGND(96, 14, 18, 2);
	DrawGND(116, 14, 36, 2);
	DrawGND(155, 14, 70, 2);

	DrawGND2(89, 12, 1, 4);
	DrawGND2(90, 9, 4, 1);
	DrawGND2(116, 12, 1, 3);
	DrawGND2(147, 12, 1, 4);
	DrawGND2(156, 9, 2, 1);
	DrawGND2(182, 12, 5, true);
	DrawGND2(189, 10, 2, 6);
	DrawGND2(199, 12, 1, 1);

	DrawBrick(90, 5, 3, 1);
	DrawBrick(148, 9, 3, 1);

	DrawPipe(44, 12, 2);
	DrawPipe(51, 12, 2);
	DrawPipe(156, 8, 1);
	DrawPipe(163, 12, 1);
	
	DrawEnd(199, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleSmall(203, 12);

	tile[148][9]->SetMustroom(true);

	tile[91][5]->SetStar(true);

	mapType = LongDat;
	DrawGND(228, 14, 17, 2);

	DrawBrick(227, 12, 1, 12);
	DrawBrick(228, 12, 1, 11);
	DrawBrick(232, 7, 1, 2);
	DrawBrick(233, 7, 5, 1);
	DrawBrick(238, 7, 1, 6);
	DrawBrick(239, 6, 2, 1);
	DrawBrick(232, 2, 6, 1);
	DrawBrick(242, 7, 1, 1);

	DrawCoins(233, 8, 5, 2);

	DrawPipeVertical(243, 12, 11);
	DrawPipeHorizontal(241, 12, 1);

	tile[242][7]->SetNumberOfCoin(8);

	mapType = HoangHon;
}

void Map::LoadLevel_5_2()
{
	ClearMap();

	mapWidth = 415;
	mapHeight = 15;
	mapTime = 400;
	mapType = HoangHon;

	CreateMap();

	LoadMinionLevel_5_2();

	DrawBulletBill(97, 8, 0);
	DrawBulletBill(187, 12, 0);

	DrawGND(74, 14, 33, 2);
	DrawGND(109, 14, 37, 2);
	DrawGND(148, 14, 24, 2);
	DrawGND(176, 14, 31, 2);
	DrawGND(209, 14, 25, 2);
	DrawGND(231, 14, 19, 2);
	DrawGND(253, 14, 2, 2);
	DrawGND(257, 14, 8, 2);
	DrawGND(266, 14, 2, 2);
	DrawGND(269, 14, 35, 2);

	DrawGND2(92, 12, 4, true);
	DrawGND2(96, 9, 3, 1);
	DrawGND2(124, 12, 4, true);
	DrawGND2(128, 12, 1, 4);
	DrawGND2(129, 12, 1, 2);
	DrawGND2(142, 12, 4, true);
	DrawGND2(148, 12, 1, 5);
	DrawGND2(149, 12, 1, 6);
	DrawGND2(150, 12, 1, 6);
	DrawGND2(209, 12, 1, 3);
	DrawGND2(263, 12, 2, true);
	DrawGND2(266, 12, 1, 4);
	DrawGND2(267, 12, 1, 5);
	DrawGND2(269, 12, 1, 7);
	DrawGND2(270, 12, 2, 8);
	DrawGND2(280, 12, 1, 1);

	DrawBrick(109, 9, 6, 1);
	DrawBrick(109, 5, 6, 1);
	DrawBrick(166, 5, 2, 1);
	DrawBrick(169, 8, 3, 1);
	DrawBrick(198, 9, 8, 1);
	DrawBrick(198, 5, 8, 1);
	DrawBrick(221, 11, 2, 1);
	DrawBrick(227, 9, 3, 1);
	DrawBrick(233, 5, 5, 1);
	DrawBrick(248, 9, 1, 1);
	DrawBrick(252, 5, 4, 1);

	DrawBlockQ(158, 9, 5);

	DrawCoins(101, 4, 3, 1);
	DrawCoins(109, 8, 3, 1);
	DrawCoins(166, 4, 2, 1);
	DrawCoins(252, 4, 2, 1);

	DrawPipe(135, 12, 2);
	DrawPipe(195, 12, 1);
	DrawPipe(253, 12, 1);

	DrawEnd(280, 11, 9);
	DrawCastleSmall(80, 12);
	DrawCastleSmall(284, 12);

	tile[114][5]->SetMustroom(true);
	tile[222][11]->SetMustroom(true);
	tile[248][9]->SetMustroom(true);

	tile[205][5]->SetStar(true);

	tile[221][11]->SetNumberOfCoin(6);

	mapType = Bien;
	DrawWater(0, 14, 65, 13);
	DrawPipeHorizontal(62, 8, 1);

	DrawGND(0, 14, 22, 2);
	DrawGND(11, 6, 5, 1);
	DrawGND(26, 14, 2, 5);
	DrawGND(26, 4, 2, 3);
	DrawGND(32, 4, 2, 3);
	DrawGND(32, 14, 2, 5);
	DrawGND(34, 14, 4, 2);
	DrawGND(38, 4, 6, 1);
	DrawGND(40, 14, 2, 2);
	DrawGND(44, 14, 30, 2);
	DrawGND(50, 9, 4, 1);
	DrawGND(54, 6, 4, 1);
	DrawGND(59, 12, 15, 1);
	DrawGND(60, 11, 14, 1);
	DrawGND(61, 10, 13, 2);
	DrawGND(61, 5, 13, 4);
	DrawGND(63, 8, 11, 3);

	DrawCoins(22, 7, 10, 1);
	DrawCoins(40, 12, 2, 1);
	DrawCoins(50, 8, 4, 1);
	DrawCoins(54, 5, 4, 1);

	mapType = ThienDuong;
	DrawBonus(325, 13, 4);
	DrawBonus(330, 13, 57);
	DrawBonusEnd(387);

	DrawCoins(340, 6, 16, 1);
	DrawCoins(357, 4, 3, 1);
	DrawCoins(361, 5, 16, 1);
	DrawCoins(378, 4, 3, 1);
	DrawCoins(394, 12, 3, 1);

	mapType = HoangHon;
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

	DrawGND(0, 14, 16, 2);
	DrawGND(129, 14, 47, 2);

	DrawGND2(138, 12, 2, 4);
	DrawGND2(140, 12, 2, 6);
	DrawGND2(142, 12, 2, 8);
	DrawGND2(152, 12, 1, 1);

	DrawBlockQ(59, 10, 1);

	DrawT(18, 14, 4, 3);
	DrawT(24, 14, 8, 6);
	DrawT(26, 8, 5, 4);
	DrawT(32, 14, 3, 3);
	DrawT(35, 14, 5, 7);
	DrawT(40, 14, 7, 11);
	DrawT(50, 14, 4, 2);
	DrawT(50, 14, 4, 2);
	DrawT(59, 14, 5, 2);
	DrawT(60, 12, 4, 8);
	DrawT(65, 14, 5, 2);
	DrawT(70, 14, 3, 6);
	DrawT(76, 14, 6, 9);
	DrawT(98, 14, 4, 4);
	DrawT(104, 14, 8, 8);
	DrawT(113, 14, 3, 2);
	DrawT(116, 14, 4, 6);
	DrawT(122, 14, 4, 6);

	DrawCoins(27, 4, 3, 1);
	DrawCoins(33, 11, 1, 1);
	DrawCoins(37, 2, 2, 1);
	DrawCoins(50, 6, 2, 1);
	DrawCoins(60, 4, 4, 1);
	DrawCoins(85, 5, 2, 1);
	DrawCoins(93, 4, 2, 1);
	DrawCoins(97, 4, 2, 1);
	DrawCoins(113, 12, 3, 1);
	DrawCoins(120, 5, 2, 1);

	DrawEnd(152, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(155, 12);
	DrawCastleWall(164, 12, 12, 6);

	tile[59][10]->SetMustroom(true);

	mapType = BanNgay;
}

void Map::LoadLevel_5_4()
{
	ClearMap();

	mapWidth = 190;
	mapHeight = 15;
	mapTime = 300;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_5_4();

	DrawGND(0, 14, 16, 5);
	DrawGND(0, 9, 5, 1);
	DrawGND(0, 8, 4, 1);
	DrawGND(0, 7, 3, 1);
	DrawGND(0, 4, 16, 3);
	DrawGND(18, 9, 2, 1);
	DrawGND(22, 7, 3, 1);
	DrawGND(27, 9, 2, 1);
	DrawGND(32, 14, 52, 2);
	DrawGND(32, 12, 2, 3);
	DrawGND(34, 5, 49, 4);
	DrawGND(37, 9, 37, 1);
	DrawGND(80, 12, 4, 3);
	DrawGND(92, 14, 17, 2);
	DrawGND(92, 12, 7, 3);
	DrawGND(93, 4, 6, 3);
	DrawGND(108, 12, 1, 3);
	DrawGND(111, 14, 2, 5);
	DrawGND(115, 14, 13, 2);
	DrawGND(115, 12, 5, 3);
	DrawGND(115, 4, 13, 3);
	DrawGND(122, 12, 2, 3);
	DrawGND(126, 12, 2, 3);
	DrawGND(128, 2, 42, 1);
	DrawGND(141, 14, 29, 2);
	DrawGND(141, 12, 3, 4);
	DrawGND(142, 5, 2, 3);

	DrawLava(16, 14, 16, 2);
	DrawLava(109, 14, 2, 2);
	DrawLava(113, 14, 2, 2);
	DrawLava(128, 14, 13, 2);

	DrawBrick(128, 5, 6, 1);

	DrawBlockQ(23, 3, 1);

	DrawCoins(102, 12, 3, 1);
	DrawCoins(102, 8, 3, 1);

	DrawBridge(128, 10, 13);

	DrawPlatformLine(86);
	DrawPlatformLine(89);

	tile[23][7]->SetID(16);
	tile[43][13]->SetID(16);
	tile[49][9]->SetID(16);
	tile[55][5]->SetID(16);
	tile[55][13]->SetID(16);
	tile[61][9]->SetID(16);
	tile[67][13]->SetID(16);
	tile[73][9]->SetID(16);
	tile[82][6]->SetID(16);
	tile[92][10]->SetID(16);
	tile[103][11]->SetID(16);

	tile[23][3]->SetMustroom(true);

	mapType = NuiLua;
}

void Map::LoadLevel_6_1()
{
	ClearMap();

	mapWidth = 210;
	mapHeight = 15;
	mapTime = 400;
	mapType = BinhMinh;

	CreateMap();

	LoadMinionLevel_6_1();

	DrawGND(0, 14, 20, 2);
	DrawGND(22, 14, 9, 2);
	DrawGND(37, 14, 2, 2);
	DrawGND(41, 14, 16, 2);
	DrawGND(59, 14, 15, 2);
	DrawGND(77, 14, 16, 2);
	DrawGND(96, 14, 31, 2);
	DrawGND(134, 14, 2, 2);
	DrawGND(137, 14, 12, 2);
	DrawGND(155, 14, 9, 2);
	DrawGND(167, 14, 7, 2);
	DrawGND(176, 14, 34, 2);

	DrawGND2(26, 12, 6, 1);
	DrawGND2(29, 11, 5, 1);
	DrawGND2(32, 10, 4, 1);
	DrawGND2(35, 9, 3, 1);
	DrawGND2(69, 12, 4, true);
	DrawGND2(73, 12, 1, 4);
	DrawGND2(84, 11, 2, true);
	DrawGND2(87, 12, 1, 5);
	DrawGND2(88, 12, 1, 6);
	DrawGND2(89, 12, 1, 7);
	DrawGND2(122, 12, 5, true);
	DrawGND2(143, 12, 6, true);
	DrawGND2(169, 12, 5, true);
	DrawGND2(176, 12, 2, 8);
	DrawGND2(186, 12, 1, 1);

	DrawBrick(36, 5, 2, 1);
	DrawBrick(41, 9, 3, 1);
	DrawBrick(90, 6, 3, 1);
	DrawBrick(92, 10, 3, 1);
	DrawBrick(127, 8, 2, 1);
	DrawBrick(130, 12, 5, 1);
	DrawBrick(149, 7, 2, 1);
	DrawBrick(151, 9, 2, 1);
	DrawBrick(152, 11, 2, 1);

	DrawBlockQ(16, 9, 2);
	DrawBlockQ(130, 8, 2);

	DrawPipe(102, 12, 2);

	DrawCoins(62, 9, 3, 1);
	DrawCoins(76, 7, 2, 1);
	DrawCoins(105, 8, 3, 1);

	DrawEnd(186, 11, 9);
	DrawCastleSmall(192, 12);
	DrawCastleBig(-2, 12);

	tile[36][5]->SetMustroom(true);
	tile[90][8]->SetMustroom(true);
	tile[130][8]->SetMustroom(true);
	tile[90][8]->SetPowerUp(false);

	tile[43][9]->SetNumberOfCoin(7);
	tile[152][9]->SetNumberOfCoin(8);

	mapType = BinhMinh;
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

	DrawGND(77, 14, 131, 2);
	DrawGND(214, 14, 12, 2);
	DrawGND(227, 14, 1, 2);
	DrawGND(229, 14, 8, 2);
	DrawGND(238, 14, 82, 2);

	DrawGND2(117, 8, 2, 1);
	DrawGND2(147, 9, 2, 1);
	DrawGND2(196, 9, 2, 1);
	DrawGND2(234, 12, 3, true);
	DrawGND2(241, 12, 1, 4);
	DrawGND2(242, 12, 1, 2);
	DrawGND2(252, 9, 2, 1);
	DrawGND2(284, 12, 8, true);
	DrawGND2(292, 12, 1, 8);
	DrawGND2(301, 12, 1, 1);

	DrawBrick(95, 9, 3, 1);
	DrawBrick(108, 5, 3, 1);
	DrawBrick(136, 9, 2, 1);
	DrawBrick(152, 5, 5, 1);
	DrawBrick(162, 5, 4, 1);
	DrawBrick(195, 9, 1, 1);
	DrawBrick(198, 9, 1, 1);
	DrawBrick(200, 5, 1, 1);
	DrawBrick(204, 5, 9, 1);
	DrawBrick(223, 8, 2, 1);
	DrawBrick(225, 5, 2, 1);
	DrawBrick(229, 9, 3, 1);
	DrawBrick(230, 5, 2, 1);
	DrawBrick(245, 9, 3, 1);
	DrawBrick(245, 5, 3, 1);

	DrawPipe(104, 12, 3);
	DrawPipe(113, 12, 3);
	DrawPipe(117, 7, 1);
	DrawPipe(120, 12, 1);
	DrawPipe(122, 12, 1);
	DrawPipe(131, 12, 3);
	DrawPipe(141, 12, 4);
	DrawPipe(147, 8, 1);
	DrawPipe(152, 12, 1);
	DrawPipe(159, 12, 1);
	DrawPipe(165, 12, 2);
	DrawPipe(169, 12, 1);
	DrawPipe(172, 12, 5);
	DrawPipe(179, 12, 2);
	DrawPipe(187, 12, 3);
	DrawPipe(190, 12, 1);
	DrawPipe(196, 8, 2);
	DrawPipe(200, 12, 1);
	DrawPipe(216, 12, 1);
	DrawPipe(220, 12, 1);
	DrawPipe(238, 12, 2);
	DrawPipe(252, 8, 2);
	DrawPipe(259, 12, 3);
	DrawPipe(264, 12, 1);
	DrawPipe(266, 12, 2);
	DrawPipe(268, 12, 3);
	DrawPipe(274, 12, 2);
	DrawPipe(286, 12, 3);

	DrawEnd(301, 11, 9);
	DrawCastleSmall(85, 12);
	DrawCastleSmall(305, 12);

	tile[137][9]->SetMustroom(true);

	tile[225][5]->SetStar(true);

	tile[109][5]->SetNumberOfCoin(8);

	mapType = Bien;
	DrawWater(0, 14, 65, 13);
	DrawPipeHorizontal(62, 8, 1);

	DrawGND(0, 14, 22, 2);
	DrawGND(11, 6, 5, 1);
	DrawGND(26, 4, 2, 3);
	DrawGND(26, 14, 2, 5);
	DrawGND(32, 14, 2, 5);
	DrawGND(32, 4, 2, 3);
	DrawGND(34, 14, 4, 2);
	DrawGND(38, 4, 6, 1);
	DrawGND(40, 14, 2, 2);
	DrawGND(44, 14, 30, 2);
	DrawGND(50, 9, 4, 1);
	DrawGND(54, 6, 4, 1);
	DrawGND(59, 12, 15, 1);
	DrawGND(60, 11, 14, 1);
	DrawGND(61, 10, 13, 2);
	DrawGND(61, 5, 13, 4);
	DrawGND(63, 8, 11, 3);

	DrawCoins(22, 7, 10, 1);
	DrawCoins(40, 12, 2, 1);
	DrawCoins(50, 8, 4, 1);
	DrawCoins(54, 5, 4, 1);

	mapType = LongDat;
	DrawGND(330, 14, 17, 2);

	DrawBrick(329, 12, 1, 12);
	DrawBrick(330, 12, 1, 11);
	DrawBrick(334, 7, 1, 2);
	DrawBrick(334, 12, 6, 1);
	DrawBrick(344, 7, 1, 1);
	DrawBrick(335, 7, 5, 1);
	DrawBrick(340, 7, 1, 6);
	DrawBrick(341, 6, 2, 1);

	DrawCoins(335, 6, 5, 2);

	DrawPipeVertical(345, 12, 11);
	DrawPipeHorizontal(343, 12, 1);

	tile[344][7]->SetNumberOfCoin(8);

	mapType = LongDat;
	DrawGND(360, 13, 17, 2);

	DrawBrick(360, 12, 1, 11);
	DrawBrick(363, 11, 1, 3);
	DrawBrick(370, 11, 1, 3);
	DrawBrick(364, 9, 6, 1);
	DrawBrick(363, 12, 12, 1);
	DrawBrick(373, 9, 1, 1);

	DrawCoins(363, 12, 10, 1);
	DrawCoins(363, 8, 8, 1);

	DrawPipeVertical(375, 12, 11);
	DrawPipeHorizontal(373, 12, 1);

	tile[373][9]->SetMustroom(true);

	mapType = BanNgay;
	DrawBonus(390, 13, 4);
	DrawBonus(395, 13, 78);
	DrawBonus(421, 8, 1);
	DrawBonus(440, 8, 1);
	DrawBonus(440, 7, 1);
	DrawBonus(451, 8, 1);
	DrawBonus(451, 7, 1);
	DrawBonus(457, 6, 2);
	DrawBonus(461, 6, 1);
	DrawBonus(463, 6, 1);
	DrawBonus(465, 6, 1);
	DrawBonus(467, 6, 1);
	DrawBonus(469, 6, 1);
	DrawBonusEnd(473);

	DrawCoins(404, 6, 16, 1);
	DrawCoins(423, 6, 16, 1);
	DrawCoins(442, 5, 8, 1);
	DrawCoins(461, 5, 10, 1);
	DrawCoins(475, 11, 3, 1);

	mapType = BanNgay;
}

void Map::LoadLevel_6_3()
{
	ClearMap();

	mapWidth = 200;
	mapHeight = 15;
	mapTime = 300;
	mapType = DiaNguc;

	CreateMap();

	LoadMinionLevel_6_3();

	DrawGND(0, 14, 16, 2);
	DrawGND(160, 14, 30, 2);

	DrawGND2(167, 12, 1, 1);

	DrawT(18, 14, 3, 2);
	DrawT(21, 14, 3, 6);
	DrawT(24, 14, 3, 2);
	DrawT(31, 14, 4, 6);
	DrawT(37, 14, 3, 2);
	DrawT(43, 14, 3, 2);
	DrawT(49, 14, 4, 4);
	DrawT(65, 14, 5, 6);
	DrawT(85, 14, 3, 12);
	DrawT(85, 14, 5, 5);
	DrawT(90, 14, 3, 7);
	DrawT(93, 14, 3, 2);
	DrawT(97, 14, 4, 2);
	DrawT(103, 14, 3, 2);
	DrawT(107, 14, 5, 6);
	DrawT(113, 14, 5, 2);
	DrawT(123, 14, 3, 2);
	DrawT(132, 14, 3, 10);
	DrawT(132, 14, 4, 2);
	DrawT(135, 14, 4, 6);
	DrawT(156, 14, 3, 10);

	DrawSeeSaw(71, 2, 5);
	DrawSeeSaw(79, 2, 4);
	DrawSeeSaw(127, 2, 4);

	DrawCastleSmall(0, 12);
	DrawCastleBig(170, 12);
	DrawCastleWall(179, 12, 11, 6);

	mapType = BuoiToi;
	DrawBlockQ(55, 3, 1);

	DrawCoins(28, 2, 2, 1);
	DrawCoins(43, 4, 7, 1);
	DrawCoins(73, 5, 2, 1);
	DrawCoins(85, 2, 3, 1);
	DrawCoins(100, 8, 4, 1);
	DrawCoins(128, 5, 2, 1);
	DrawCoins(145, 7, 2, 1);
	DrawCoins(154, 3, 2, 1);

	DrawEnd(167, 11, 9);

	tile[55][3]->SetMustroom(true);

	mapType = DiaNguc;
}

void Map::LoadLevel_6_4()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_6_4();

	DrawGND(0, 14, 3, 8);
	DrawGND(0, 4, 24, 3);
	DrawGND(3, 14, 1, 7);
	DrawGND(4, 14, 1, 6);
	DrawGND(5, 14, 8, 5);
	DrawGND(15, 14, 11, 5);
	DrawGND(23, 5, 1, 4);
	DrawGND(24, 2, 13, 1);
	DrawGND(29, 14, 3, 5);
	DrawGND(35, 14, 37, 6);
	DrawGND(37, 5, 35, 4);
	DrawGND(72, 14, 32, 5);
	DrawGND(72, 2, 91, 1);
	DrawGND(80, 3, 1, 1);
	DrawGND(88, 3, 1, 1);
	DrawGND(97, 4, 7, 2);
	DrawGND(104, 14, 24, 2);
	DrawGND(116, 12, 4, 3);
	DrawGND(123, 12, 5, 3);
	DrawGND(123, 4, 5, 2);
	DrawGND(141, 14, 3, 6);
	DrawGND(142, 5, 2, 3);
	DrawGND(144, 14, 19, 2);

	DrawLava(13, 14, 2, 3);
	DrawLava(26, 14, 3, 2);
	DrawLava(32, 14, 3, 2);
	DrawLava(128, 14, 13, 2);

	DrawBlockQ(30, 6, 1);

	DrawBridge(128, 10, 13);

	tile[23][6]->SetID(16);
	tile[37][6]->SetID(16);
	tile[80][4]->SetID(16);
	tile[92][9]->SetID(16);
	tile[30][10]->SetID(16);
	tile[49][6]->SetID(16);
	tile[60][6]->SetID(16);
	tile[67][6]->SetID(16);
	tile[76][9]->SetID(16);
	tile[84][9]->SetID(16);
	tile[88][4]->SetID(16);

	tile[30][6]->SetMustroom(true);

	mapType = NuiLua;
}

void Map::LoadLevel_7_1()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 400;
	mapType = HoangHon;

	CreateMap();

	LoadMinionLevel_7_1();

	DrawBulletBill(19, 12, 0);
	DrawBulletBill(28, 13, 0);
	DrawBulletBill(28, 11, 0);
	DrawBulletBill(36, 12, 0);
	DrawBulletBill(46, 12, 1);
	DrawBulletBill(56, 13, 0);
	DrawBulletBill(56, 11, 0);
	DrawBulletBill(64, 8, 0);
	DrawBulletBill(68, 12, 0);
	DrawBulletBill(104, 12, 0);
	DrawBulletBill(122, 12, 0);
	DrawBulletBill(146, 13, 0);
	DrawBulletBill(146, 11, 0);

	DrawGND(0, 14, 73, 2);
	DrawGND(75, 14, 77, 2);
	DrawGND(153, 14, 46, 2);

	DrawGND2(64, 9, 1, 1);
	DrawGND2(141, 12, 1, 3);
	DrawGND2(153, 12, 6, true);
	DrawGND2(162, 12, 8, true);
	DrawGND2(170, 12, 1, 8);
	DrawGND2(179, 12, 1, 1);

	DrawBrick(27, 5, 3, 1);
	DrawBrick(62, 9, 2, 1);
	DrawBrick(65, 9, 2, 1);
	DrawBrick(82, 9, 7, 1);
	DrawBrick(82, 5, 7, 1);
	DrawBrick(134, 9, 5, 1);
	DrawBrick(134, 5, 5, 1);
	DrawBrick(149, 8, 2, 1);
	DrawBrick(153, 6, 2, 1);
	DrawBrick(151, 2, 1, 1);

	DrawBlockQ(39, 9, 4);

	DrawPipe(76, 12, 2);
	DrawPipe(93, 12, 2);
	DrawPipe(109, 12, 2);
	DrawPipe(115, 12, 1);
	DrawPipe(128, 12, 1);

	DrawEnd(179, 11, 9);
	DrawCastleSmall(183, 12);
	DrawCastleBig(-2, 12);

	tile[27][5]->SetMustroom(true);
	tile[93][5]->SetMustroom(true);
	tile[151][2]->SetMustroom(true);
	tile[93][5]->SetPowerUp(false);
	tile[65][9]->SetNumberOfCoin(8);

	mapType = LongDat;
	DrawGND(210, 14, 17, 2);

	DrawBrick(210, 12, 1, 11);
	DrawBrick(214, 12, 7, 3);
	DrawBrick(214, 12, 7, 1);

	DrawCoins(214, 9, 7, 1);
	DrawCoins(214, 7, 7, 1);
	DrawCoins(215, 5, 5, 1);

	DrawPipeVertical(225, 12, 11);
	DrawPipeHorizontal(223, 12, 1);

	mapType = HoangHon;
}

void Map::LoadLevel_7_2()
{
	ClearMap();

	mapWidth = 320;
	mapHeight = 15;
	mapTime = 400;
	mapType = Bien;

	CreateMap();

	LoadMinionLevel_7_2();

	DrawWater(0, 14, 200, 13);
	DrawPipeHorizontal(189, 8, 1);

	DrawGND(0, 14, 66, 2);
	DrawGND(18, 9, 3, 1);
	DrawGND(42, 9, 2, 1);
	DrawGND(64, 12, 1, 3);
	DrawGND(65, 12, 1, 5);
	DrawGND(71, 12, 1, 5);
	DrawGND(71, 14, 60, 2);
	DrawGND(72, 12, 1, 3);
	DrawGND(78, 12, 2, 3);
	DrawGND(78, 4, 2, 3);
	DrawGND(82, 5, 3, 1);
	DrawGND(102, 9, 2, 1);
	DrawGND(115, 8, 2, 1);
	DrawGND(129, 12, 1, 4);
	DrawGND(130, 12, 1, 2);
	DrawGND(131, 4, 1, 3);
	DrawGND(132, 4, 8, 1);
	DrawGND(140, 12, 1, 2);
	DrawGND(140, 14, 17, 2);
	DrawGND(141, 12, 1, 4);
	DrawGND(156, 12, 1, 8);
	DrawGND(157, 5, 2, 1);
	DrawGND(162, 5, 2, 1);
	DrawGND(164, 14, 38, 2);
	DrawGND(164, 12, 1, 8);
	DrawGND(172, 9, 5, 1);
	DrawGND(172, 5, 5, 1);
	DrawGND(180, 9, 4, 1);
	DrawGND(180, 5, 4, 1);
	DrawGND(185, 12, 17, 1);
	DrawGND(186, 11, 16, 1);
	DrawGND(187, 10, 15, 1);
	DrawGND(188, 9, 14, 1);
	DrawGND(190, 8, 12, 3);
	DrawGND(188, 5, 14, 4);

	DrawCoins(14, 12, 2, 1);
	DrawCoins(27, 5, 3, 1);
	DrawCoins(36, 12, 3, 1);
	DrawCoins(67, 10, 3, 1);
	DrawCoins(101, 11, 3, 1);
	DrawCoins(113, 6, 3, 1);
	DrawCoins(133, 11, 1, 1);
	DrawCoins(134, 12, 3, 1);
	DrawCoins(137, 11, 1, 1);
	DrawCoins(159, 9, 3, 1);
	DrawCoins(159, 12, 3, 1);

	mapType = BanNgay;
	DrawGND(220, 14, 24, 2);

	DrawPipe(232, 12, 3);
	DrawPipeHorizontal(230, 12, 1);

	DrawCastleSmall(220, 12);

	mapType = BanNgay;
	DrawGND(271, 14, 42, 2);

	DrawGND2(276, 12, 8, true);
	DrawGND2(284, 12, 1, 8);
	DrawGND2(293, 12, 1, 1);

	DrawPipe(274, 12, 1);

	DrawEnd(293, 11, 9);
	DrawCastleSmall(297, 12);

	mapType = Bien;
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

	DrawGND(0, 14, 7, 2);
	DrawGND(207, 14, 43, 2);

	DrawGND2(10, 12, 3, true);
	DrawGND2(13, 12, 2, 3);
	DrawGND2(31, 14, 1, 5);
	DrawGND2(47, 14, 1, 5);
	DrawGND2(63, 14, 1, 5);
	DrawGND2(68, 14, 1, 5);
	DrawGND2(79, 14, 1, 5);
	DrawGND2(84, 14, 1, 5);
	DrawGND2(95, 14, 1, 5);
	DrawGND2(99, 14, 1, 6);
	DrawGND2(105, 14, 1, 6);
	DrawGND2(127, 14, 1, 5);
	DrawGND2(143, 14, 1, 5);
	DrawGND2(146, 14, 1, 3);
	DrawGND2(155, 14, 1, 3);
	DrawGND2(159, 14, 1, 5);
	DrawGND2(168, 14, 1, 5);
	DrawGND2(183, 14, 1, 5);
	DrawGND2(193, 12, 1, 3);
	DrawGND2(194, 12, 3, false);
	DrawGND2(208, 12, 8, true);
	DrawGND2(216, 12, 1, 8);
	DrawGND2(225, 12, 1, 1);

	DrawBlockQ(102, 5, 1);

	DrawCoins(36, 5, 4, 1);
	DrawCoins(55, 5, 1, 1);
	DrawCoins(57, 5, 1, 1);
	DrawCoins(59, 5, 1, 1);
	DrawCoins(56, 6, 1, 1);
	DrawCoins(58, 6, 1, 1);
	DrawCoins(72, 5, 1, 1);
	DrawCoins(73, 4, 2, 1);
	DrawCoins(75, 5, 1, 1);
	DrawCoins(97, 5, 3, 1);
	DrawCoins(108, 5, 3, 1);
	DrawCoins(133, 5, 6, 1);
	DrawCoins(149, 8, 4, 1);
	DrawCoins(173, 6, 6, 1);

	DrawT(8, 14, 8, 2);
	DrawT(112, 14, 8, 2);
	DrawT(192, 14, 13, 2);

	DrawBridge2(15, 10, 16);
	DrawBridge2(32, 10, 15);
	DrawBridge2(48, 10, 15);
	DrawBridge2(69, 10, 10);
	DrawBridge2(85, 10, 10);
	DrawBridge2(100, 9, 5);
	DrawBridge2(122, 10, 3);
	DrawBridge2(128, 10, 15);
	DrawBridge2(147, 12, 8);
	DrawBridge2(160, 10, 8);
	DrawBridge2(171, 10, 2);
	DrawBridge2(175, 10, 2);
	DrawBridge2(179, 10, 2);
	DrawBridge2(184, 10, 9);

	DrawEnd(225, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(228, 12);
	DrawCastleWall(237, 12, 13, 6);

	tile[102][5]->SetMustroom(true);

	mapType = BanNgay;
}

void Map::LoadLevel_7_4()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 400;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_7_4();

	DrawGND(0, 14, 16, 5);
	DrawGND(0, 9, 5, 1);
	DrawGND(0, 8, 4, 1);
	DrawGND(0, 7, 3, 1);
	DrawGND(0, 4, 16, 3);
	DrawGND(16, 2, 180, 1);
	DrawGND(28, 4, 4, 2);
	DrawGND(27, 14, 5, 5);
	DrawGND(32, 14, 61, 2);
	DrawGND(34, 9, 16, 1);
	DrawGND(36, 8, 14, 1);
	DrawGND(37, 7, 13, 1);
	DrawGND(38, 6, 12, 1);
	DrawGND(54, 10, 13, 1);
	DrawGND(55, 6, 11, 1);
	DrawGND(70, 9, 18, 1);
	DrawGND(70, 8, 19, 1);
	DrawGND(70, 7, 20, 1);
	DrawGND(70, 6, 22, 1);
	DrawGND(93, 12, 3, 3);
	DrawGND(93, 14, 3, 2);
	DrawGND(96, 14, 68, 2);
	DrawGND(98, 9, 16, 1);
	DrawGND(100, 8, 14, 1);
	DrawGND(101, 7, 13, 1);
	DrawGND(102, 6, 12, 1);
	DrawGND(118, 10, 13, 1);
	DrawGND(119, 6, 11, 1);
	DrawGND(134, 9, 18, 1);
	DrawGND(134, 8, 19, 1);
	DrawGND(134, 7, 20, 1);
	DrawGND(134, 6, 22, 1);
	DrawGND(157, 12, 3, 3);
	DrawGND(157, 12, 3, 3);
	DrawGND(163, 6, 2, 1);
	DrawGND(166, 6, 2, 1);
	DrawGND(167, 14, 1, 2);
	DrawGND(168, 6, 1, 1);
	DrawGND(170, 6, 4, 1);
	DrawGND(171, 14, 85, 2);
	DrawGND(174, 9, 6, 4);
	DrawGND(182, 6, 3, 1);
	DrawGND(183, 10, 3, 1);
	DrawGND(187, 6, 7, 1);
	DrawGND(188, 10, 7, 1);
	DrawGND(196, 2, 94, 1);
	DrawGND(196, 6, 3, 1);
	DrawGND(197, 10, 3, 1);
	DrawGND(201, 9, 1, 4);
	DrawGND(202, 6, 15, 1);
	DrawGND(203, 12, 1, 1);
	DrawGND(204, 12, 1, 2);
	DrawGND(205, 12, 19, 3);
	DrawGND(227, 12, 3, 3);
	DrawGND(232, 12, 8, 3);
	DrawGND(242, 12, 2, 3);
	DrawGND(246, 12, 2, 3);
	DrawGND(250, 12, 6, 3);
	DrawGND(269, 14, 3, 6);
	DrawGND(270, 5, 2, 3);
	DrawGND(272, 14, 18, 2);

	DrawLava(16, 14, 11, 2);
	DrawLava(164, 14, 3, 2);
	DrawLava(168, 14, 3, 2);
	DrawLava(256, 14, 13, 2);

	DrawBridge(256, 10, 13);

	tile[167][7]->SetID(16);

	mapType = NuiLua;
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

	DrawGND(0, 14, 46, 2);
	DrawGND(47, 14, 1, 2);
	DrawGND(49, 14, 2, 2);
	DrawGND(52, 14, 2, 2);
	DrawGND(55, 14, 2, 2);
	DrawGND(58, 14, 111, 2);
	DrawGND(170, 14, 1, 2);
	DrawGND(172, 14, 2, 2);
	DrawGND(175, 14, 1, 2);
	DrawGND(177, 14, 2, 2);
	DrawGND(180, 14, 17, 2);
	DrawGND(198, 14, 1, 2);
	DrawGND(200, 14, 1, 2);
	DrawGND(202, 14, 19, 2);
	DrawGND(227, 14, 10, 2);
	DrawGND(238, 14, 2, 2);
	DrawGND(242, 14, 2, 2);
	DrawGND(246, 14, 44, 2);
	DrawGND(293, 14, 2, 2);
	DrawGND(298, 14, 16, 2);
	DrawGND(319, 14, 1, 2);
	DrawGND(324, 14, 35, 2);
	DrawGND(360, 14, 1, 2);
	DrawGND(362, 14, 1, 2);
	DrawGND(364, 14, 1, 2);
	DrawGND(366, 14, 34, 2);

	DrawGND2(153, 12, 1, 4);
	DrawGND2(163, 12, 1, 4);
	DrawGND2(210, 12, 1, 2);
	DrawGND2(275, 12, 6, true);
	DrawGND2(303, 12, 1, 2);
	DrawGND2(307, 12, 1, 2);
	DrawGND2(360, 12, 1, 2);
	DrawGND2(362, 12, 1, 4);
	DrawGND2(364, 12, 1, 6);
	DrawGND2(366, 12, 2, 8);
	DrawGND2(376, 12, 1, 1);

	DrawBrick(154, 5, 8, 1);
	DrawBrick(184, 8, 8, 1);

	DrawCoins(64, 8, 1, 1);
	DrawCoins(89, 8, 1, 1);
	DrawCoins(98, 8, 1, 1);
	DrawCoins(109, 4, 2, 1);
	DrawCoins(223, 8, 2, 1);
	DrawCoins(283, 8, 2, 1);
	DrawCoins(291, 8, 1, 1);
	DrawCoins(296, 8, 1, 1);
	DrawCoins(316, 8, 2, 1);
	DrawCoins(321, 8, 2, 1);

	DrawPipe(35, 12, 3);
	DrawPipe(76, 12, 3);
	DrawPipe(82, 12, 2);
	DrawPipe(94, 12, 3);
	DrawPipe(104, 12, 3);
	DrawPipe(115, 12, 1);
	DrawPipe(140, 12, 2);
	DrawPipe(238, 12, 2);
	DrawPipe(242, 12, 3);
	DrawPipe(246, 12, 4);
	DrawPipe(344, 12, 2);
	DrawPipe(355, 12, 1);
	
	DrawEnd(376, 11, 9);
	DrawCastleSmall(380, 12);
	DrawCastleBig(-2, 12);

	tile[80][8]->SetMustroom(true);

	tile[186][8]->SetStar(true);

	tile[158][5]->SetNumberOfCoin(8);

	mapType = LongDat;
	DrawGND(410, 14, 17, 2);

	DrawBrick(410, 12, 1, 11);
	DrawBrick(413, 9, 10, 1);
	DrawBrick(413, 5, 10, 4);
	DrawBrick(423, 10, 2, 9);

	DrawCoins(413, 12, 9, 1);
	DrawCoins(414, 8, 8, 1);

	DrawPipeVertical(425, 12, 11);
	DrawPipeHorizontal(423, 12, 1);

	tile[422][9]->SetNumberOfCoin(10);

	mapType = BanNgay;
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

	DrawBulletBill(85, 12, 0);
	DrawBulletBill(93, 11, 0);
	DrawBulletBill(93, 13, 0);
	DrawBulletBill(105, 12, 0);
	DrawBulletBill(115, 13, 0);
	DrawBulletBill(119, 8, 0);
	DrawBulletBill(125, 12, 1);
	DrawBulletBill(175, 12, 0);
	DrawBulletBill(191, 13, 0);
	DrawBulletBill(191, 11, 0);

	DrawGND(0, 14, 15, 2);
	DrawGND(16, 14, 5, 2);
	DrawGND(22, 14, 14, 2);
	DrawGND(37, 14, 8, 2);
	DrawGND(46, 14, 4, 2);
	DrawGND(51, 14, 1, 2);
	DrawGND(53, 14, 3, 2);
	DrawGND(57, 14, 6, 2);
	DrawGND(64, 14, 14, 2);
	DrawGND(80, 14, 4, 2);
	DrawGND(85, 14, 53, 2);
	DrawGND(139, 14, 5, 2);
	DrawGND(145, 14, 1, 2);
	DrawGND(147, 14, 1, 2);
	DrawGND(154, 14, 20, 2);
	DrawGND(175, 14, 1, 2);
	DrawGND(179, 14, 23, 2);
	DrawGND(203, 14, 1, 2);
	DrawGND(206, 14, 31, 2);

	DrawGND2(17, 12, 4, true);
	DrawGND2(22, 12, 1, 6);
	DrawGND2(23, 12, 1, 7);
	DrawGND2(24, 12, 2, 8);
	DrawGND2(119, 9, 1, 1);
	DrawGND2(182, 12, 5, true);
	DrawGND2(199, 12, 3, true);
	DrawGND2(203, 12, 1, 5);
	DrawGND2(206, 12, 2, 8);
	DrawGND2(216, 12, 1, 1);
	
	DrawBrick(43, 5, 33, 1);
	DrawBrick(77, 9, 2, 1);
	DrawBrick(99, 9, 2, 1);
	DrawBrick(118, 9, 1, 1);
	DrawBrick(120, 9, 1, 1);
	DrawBrick(110, 9, 2, 1);

	DrawBlockQ(29, 9, 4);

	DrawPipe(163, 12, 1);
	DrawPipe(156, 12, 3);
	DrawPipe(142, 12, 1);
	DrawPipe(131, 12, 1);
	
	DrawEnd(216, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleSmall(220, 12);

	tile[44][5]->SetMustroom(true);
	tile[100][9]->SetMustroom(true);
	tile[44][9]->SetPowerUp(false);

	tile[120][9]->SetNumberOfCoin(8);

	mapType = LongDat;
	DrawGND(240, 14, 17, 2);

	DrawBrick(239, 12, 1, 12);
	DrawBrick(240, 12, 1, 11);
	DrawBrick(244, 7, 1, 2);
	DrawBrick(245, 7, 5, 1);
	DrawBrick(250, 7, 1, 6);
	DrawBrick(251, 6, 2, 1);
	DrawBrick(254, 7, 1, 1);

	DrawCoins(245, 6, 5, 2);

	DrawPipeVertical(255, 12, 11);
	DrawPipeHorizontal(253, 12, 1);

	tile[254][7]->SetNumberOfCoin(8);

	mapType = BanNgay;
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

	DrawBulletBill(18, 12, 0);
	DrawBulletBill(34, 12, 1);
	DrawBulletBill(86, 12, 0);

	DrawGND(0, 14, 69, 2);
	DrawGND(71, 14, 4, 2);
	DrawGND(77, 14, 47, 2);
	DrawGND(126, 14, 2, 2);
	DrawGND(130, 14, 67, 2);
	DrawGND(208, 14, 31, 2);

	DrawGND2(71, 12, 4, false);
	DrawGND2(95, 12, 1, 3);
	DrawGND2(109, 12, 2, 4);
	DrawGND2(195, 12, 1, 2);
	DrawGND2(198, 11, 1, 1);
	DrawGND2(200, 9, 1, 1);
	DrawGND2(202, 7, 1, 1);
	DrawGND2(204, 5, 2, 1);
	DrawGND2(214, 12, 1, 1);
	
	DrawBrick(60, 9, 8, 1);
	DrawBrick(60, 5, 8, 1);
	DrawBrick(115, 9, 8, 1);
	DrawBrick(115, 5, 8, 1);
	DrawBrick(190, 9, 1, 1);

	DrawPipe(53, 12, 3);
	DrawPipe(126, 12, 3);
	DrawPipe(168, 12, 2);

	DrawCastleWall(24, 12, 8, 6);
	DrawCastleWall(37, 12, 14, 6);
	DrawCastleWall(79, 12, 6, 6);
	DrawCastleWall(88, 12, 6, 6);
	DrawCastleWall(97, 12, 10, 6);
	DrawCastleWall(132, 12, 34, 6);
	DrawCastleWall(172, 12, 20, 6);
	DrawCastleWall(229, 12, 10, 6);

	DrawEnd(214, 11, 9);
	DrawCastleSmall(0, 12);
	DrawCastleBig(220, 12);

	tile[66][5]->SetMustroom(true);
	tile[116][5]->SetMustroom(true);

	mapType = BanNgay;
}

void Map::LoadLevel_8_4()
{
	ClearMap();

	mapWidth = 480;
	mapHeight = 15;
	mapTime = 400;
	mapType = NuiLua;

	CreateMap();

	LoadMinionLevel_8_4();

	DrawGND(0, 14, 369, 2);
	DrawGND(0, 2, 369, 1);
	DrawGND(0, 14, 6, 5);
	DrawGND(0, 9, 5, 1);
	DrawGND(0, 8, 4, 1);
	DrawGND(0, 7, 3, 1);
	DrawGND(11, 14, 55, 2);
	DrawGND(62, 12, 4, 3);
	DrawGND(75, 14, 21, 5);
	DrawGND(76, 6, 4, 1);
	DrawGND(163, 9, 2, 1);
	DrawGND(218, 12, 22, 3);
	DrawGND(244, 12, 16, 3);
	DrawGND(325, 12, 6, 3);
	DrawGND(325, 4, 6, 2);
	DrawGND(344, 12, 3, 4);
	DrawGND(345, 5, 2, 3);

	DrawLava(6, 14, 5, 2);
	DrawLava(66, 14, 9, 2);
	DrawLava(155, 14, 3, 2);
	DrawLava(240, 14, 4, 2);
	DrawLava(320, 14, 5, 2);
	DrawLava(331, 14, 13, 2);

	DrawPipe(19, 14, 3);
	DrawPipe(51, 14, 3);
	DrawPipe(81, 14, 6);
	DrawPipe(90, 14, 7);
	DrawPipe(126, 14, 3);
	DrawPipe(133, 14, 4);
	DrawPipe(143, 14, 3);
	DrawPipe(153, 14, 4);
	DrawPipe(163, 8, 2);
	DrawPipe(215, 14, 3);
	DrawPipe(224, 14, 6);
	DrawPipe(232, 14, 7);
	DrawPipe(248, 14, 6);
	DrawPipe(302, 14, 3);
	DrawPipe(309, 14, 3);
	
	DrawBridge(331, 10, 13);

	mapType = Bien;
	DrawWater(392, 12, 67, 11);
	DrawPipeHorizontal(458, 8, 1);

	mapType = Ho;
	DrawGND(385, 14, 7, 13);
	DrawGND(392, 14, 79, 2);
	DrawGND(396, 12, 12, 3);
	DrawGND(396, 4, 12, 3);
	DrawGND(401, 9, 7, 1);
	DrawGND(401, 5, 7, 1);
	DrawGND(408, 2, 63, 1);
	DrawGND(429, 12, 3, 3);
	DrawGND(429, 5, 3, 3);
	DrawGND(457, 12, 14, 4);
	DrawGND(457, 5, 14, 3);
	DrawGND(459, 8, 12, 3);

	DrawPipe(393, 14, 3);

	mapType = NuiLua;
}

void Map::LoadMinionLevel_1_1()
{
	ClearMinion();

	AddGoombas(22 * 32, 383, true);
	AddGoombas(40 * 32, 383, true);
	AddGoombas(51 * 32, 383, true);
	AddGoombas(52 * 32 + 16, 383, true);
	AddGoombas(80 * 32, 127, true);
	AddGoombas(82 * 32, 127, true);
	AddGoombas(97 * 32, 383, true);
	AddGoombas(98 * 32 + 16, 383, true);
	AddGoombas(114 * 32, 383, true);
	AddGoombas(115 * 32 + 16, 383, true);
	AddGoombas(124 * 32, 383, true);
	AddGoombas(125 * 32 + 16, 383, true);
	AddGoombas(128 * 32, 383, true);
	AddGoombas(129 * 32 + 16, 383, true);
	AddGoombas(174 * 32, 383, true);
	AddGoombas(175 * 32 + 12, 383, true);

	AddKoppa(107 * 32, 383, 1, true);
}

void Map::LoadMinionLevel_1_2()
{
	ClearMinion();

	AddGoombas(16 * 32, 383, true);
	AddGoombas(17 * 32 + 8, 351, true);
	AddGoombas(29 * 32, 383, true);
	AddGoombas(62 * 32, 383, true);
	AddGoombas(64 * 32, 383, true);
	AddGoombas(73 * 32, 383 - 8 * 32, true);
	AddGoombas(76 * 32, 383 - 4 * 32, true);
	AddGoombas(77 * 32 + 16, 368 - 4 * 32, true);
	AddGoombas(99 * 32, 383, true);
	AddGoombas(100 * 32 + 16, 383, true);
	AddGoombas(102 * 32, 383, true);
	AddGoombas(113 * 32, 383, true);
	AddGoombas(135 * 32, 383 - 3 * 32, true);
	AddGoombas(136 * 32 + 16, 383 - 4 * 32, true);

	AddKoppa(44 * 32, 383, 1, true);
	AddKoppa(45 * 32 + 16, 383, 1, true);
	AddKoppa(59 * 32, 383, 1, true);

	mapType = NuiLua;
	AddKoppa(146 * 32, 383, 1, true);

	mapType = LongDat;
}

void Map::LoadMinionLevel_1_3()
{
	ClearMinion();

	AddGoombas(44 * 32, Game::gameHeight - 32 - 11 * 32, true);
	AddGoombas(46 * 32, Game::gameHeight - 32 - 11 * 32, true);
	AddGoombas(80 * 32, Game::gameHeight - 32 - 9 * 32, true);

	mapType = NuiLua;

	AddKoppa(30 * 32 - 8, Game::gameHeight - 32 - 10 * 32, 1, true);
	AddKoppa(110 * 32 - 8, Game::gameHeight - 32 - 8 * 32, 1, true);

	AddKoppa(74 * 32 - 8, Game::gameHeight - 32 - 10 * 32, 3, false);
	AddKoppa(114 * 32 - 8, Game::gameHeight - 32 - 9 * 32, 3, false);

	AddKoppa(133 * 32 - 8, Game::gameHeight - 32 - 2 * 32, 1, true);

	mapType = BanNgay;
}

void Map::LoadMinionLevel_1_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_2_1()
{
	ClearMinion();

	AddGoombas(24 * 32, Game::gameHeight - 16 - 7 * 32, true);
	AddGoombas(42 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(43 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(59 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(60 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(68 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(69 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(71 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(87 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(88 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(90 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(102 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(114 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(120 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(162 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(163 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::LoadMinionLevel_2_2()
{
	ClearMinion();
}

void Map::LoadMinionLevel_2_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_2_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_3_1()
{
	ClearMinion();

	AddGoombas(37 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(53 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(54 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(56 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(82 * 32, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(83 * 32 + 16, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(85 * 32, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(94 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(95 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(139 * 32 - 4, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(140 * 32, Game::gameHeight - 16 - 7 * 32, true);
	AddGoombas(154 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(155 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(157 * 32, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::LoadMinionLevel_3_2()
{
	ClearMinion();

	AddGoombas(24 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(25 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(27 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(71 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(72 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(74 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(119 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(120 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(122 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(179 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(180 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(182 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(188 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(189 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(191 * 32, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::LoadMinionLevel_3_3()
{
	ClearMinion();

	AddGoombas(26 * 32, Game::gameHeight - 16 - 8 * 32, true);
}

void Map::LoadMinionLevel_3_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_4_1()
{
	ClearMinion();
}

void Map::LoadMinionLevel_4_2()
{
	ClearMinion();

	AddGoombas(43 * 32, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(44 * 32 + 16, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(46 * 32, Game::gameHeight - 16 - 6 * 32, true);
}

void Map::LoadMinionLevel_4_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_4_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_5_1()
{
	ClearMinion();

	AddGoombas(19 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(20 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(22 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(30 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(31 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(33 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(65 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(66 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(68 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(76 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(77 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(103 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(104 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(106 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(121 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(122 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(124 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(135 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(136 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(138 * 32, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::LoadMinionLevel_5_2()
{
	ClearMinion();

	AddGoombas(143 * 32, Game::gameHeight - 16 - 4 * 32, true);
	AddGoombas(145 * 32, Game::gameHeight - 16 - 6 * 32, true);
	AddGoombas(235 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(236 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::LoadMinionLevel_5_3()
{
	ClearMinion();

	AddGoombas(44 * 32, Game::gameHeight - 16 - 11 * 32, true);
	AddGoombas(46 * 32, Game::gameHeight - 16 - 11 * 32, true);
	AddGoombas(80 * 32, Game::gameHeight - 16 - 9 * 32, true);
}

void Map::LoadMinionLevel_5_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_6_1()
{
	ClearMinion();
}

void Map::LoadMinionLevel_6_2()
{
	ClearMinion();
}

void Map::LoadMinionLevel_6_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_6_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_7_1()
{
	ClearMinion();
}

void Map::LoadMinionLevel_7_2()
{
	ClearMinion();
}

void Map::LoadMinionLevel_7_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_7_4()
{
	ClearMinion();
}

void Map::LoadMinionLevel_8_1()
{
	ClearMinion();

	AddGoombas(23 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(24 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(26 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(30 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(31 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(33 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(69 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(70 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(72 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(108 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(109 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(111 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(148 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(149 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(151 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(232 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(233 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(235 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(257 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(258 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(260 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(264 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(265 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(267 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(272 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(273 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::LoadMinionLevel_8_2()
{
	ClearMinion();

	AddGoombas(184 * 32, Game::gameHeight - 16 - 5 * 32, true);
	AddGoombas(186 * 32, Game::gameHeight - 16 - 7 * 32, true);
}

void Map::LoadMinionLevel_8_3()
{
	ClearMinion();
}

void Map::LoadMinionLevel_8_4()
{
	ClearMinion();

	AddGoombas(56 * 32, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(57 * 32 + 16, Game::gameHeight - 16 - 2 * 32, true);
	AddGoombas(59 * 32, Game::gameHeight - 16 - 2 * 32, true);
}

void Map::AddGoombas(int x, int y, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Goombas(x, y, mapType == BanNgay || mapType == BuoiToi || mapType == HoangHon || mapType == BinhMinh ? 5 : mapType == LongDat ? 7 : 9, moveDirection));
}

void Map::AddKoppa(int x, int y, int minionState, bool moveDirection)
{
	int id;

	switch (minionState)
	{
	case 0 : case 3:
		id = mapType == BanNgay || mapType == BuoiToi || mapType == BinhMinh || mapType == HoangHon ? 12 : mapType == LongDat ? 15 : 18;
		break;
	case 1:
		id = mapType == BanNgay || mapType == BuoiToi || mapType == BinhMinh || mapType == HoangHon ? 11 : mapType == LongDat ? 14 : 17;
		break;
	case 2:
		id = mapType == BanNgay || mapType == BuoiToi || mapType == BinhMinh || mapType == HoangHon ? 13 : mapType == LongDat ? 16 : 19;
		break;
	}

	minion[GetListID(x)].push_back(new Koopa(x, y, id, minionState, moveDirection));
}
void Map::AddBowser(int x, int y, bool spawnHammer)
{
	minion[GetListID(x)].push_back(new Bowser(x, y));
}

void Map::AddToad(int x, int y, bool peach)
{
	minion[GetListID(x)].push_back(new Toad());
}

void Map::AddSquid(int x, int y)
{
	minion[GetListID(x)].push_back(new Squid(x, y));
}

void Map::AddCheep(int x, int y, int minionType, int moveSpeed, bool moveDirection)
{
	minion[GetListID(x)].push_back(new Cheep(x, y));
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
	minion[GetListID(x)].push_back(new Lakito(x, y));
}

void Map::AddSpikey(int x, int y)
{
	minion[GetListID(x)].push_back(new Spikey(x, y));
}

void Map::AddVine(int x, int y, int id, int minionState)
{
	minion[GetListID(x)].push_back(new Vine());
}

void Map::AddFire(float x, float y, int toY)
{
	//minion[GetListID(x)].push_back(new Fire(x, y));
}

void Map::AddFireBall(int x, int y, int width, int id, bool left)
{
	for (int i = 9; i < width; i++)
	{
		minion[GetListID(x)].push_back(new FireBall());
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


void Map::DrawGND(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			SetTileID(x + i, y - j, mapType == LongDat ? 2 : mapType == Bien ? 3 : mapType == DiaNguc ? 4 : mapType == NuiLua ? 5 : mapType == Ho ? 6 : 1);
		}
	}
}

void Map::DrawGND2(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			SetTileID(x + i, y - j, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh || mapType == ThienDuong ? 7 : mapType == DiaNguc ? 9 : 8);
		}
	}
}

void Map::DrawGND2(int x, int y, int size, bool direction)
{
	if (direction)
	{
		for (int i = 0, k = 1; i < size; i++)
		{
			for (int j = 0; j < k; j++)
			{
				SetTileID(x + i, y - j, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh || mapType == ThienDuong ? 7 : mapType == NuiLua ? 9 : 8);
			}
			k++;
		}
	}
	else
	{
		for (int i = 0, k = size; i < size; i++)
		{
			for (int j = k; j > 0; j--)
			{
				SetTileID(x + i, y - j + 1, mapType == BanNgay || mapType == BuoiToi ? 7 : mapType == NuiLua ? 9 : 8);
			}
			k--;
		}
	}
}

void Map::DrawBrick(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			SetTileID(x + i, y - j, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh ? 10 : mapType == LongDat ? 11 : 12);
		}
	}
}

void Map::DrawBlockQ(int x, int y, int width)
{
	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i, y, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh || mapType == ThienDuong ? 13 : 15);
	}
}

void Map::DrawBlockQ2(int x, int y, int width)
{
	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i, y, 117);
	}
}

void Map::DrawPipe(int x, int y, int height)
{
	for (int i = 0; i < height; i++)
	{
		SetTileID(x, y - i, mapType == BanNgay || mapType == BinhMinh ? 18 : mapType == Bien ? 38 : mapType == BuoiToi || mapType == HoangHon || mapType == NuiLua ? 48 : mapType == ThienDuong ? 58 : mapType == Ho ? 62 : 28);
		SetTileID(x + 1, y - i, mapType == BanNgay || mapType == BinhMinh ? 19 : mapType == Bien ? 39 : mapType == BuoiToi || mapType == HoangHon || mapType == NuiLua ? 49 : mapType == ThienDuong ? 59 : mapType == Ho ? 63 : 29);
	}

	SetTileID(x, y - height, mapType == BanNgay || mapType == BinhMinh ? 20 : mapType == Bien ? 40 : mapType == BuoiToi || mapType == HoangHon || mapType == NuiLua ? 50 : mapType == ThienDuong ? 60 : mapType == Ho ? 64 : 30);
	SetTileID(x + 1, y - height, mapType == BanNgay || mapType == BinhMinh ? 21 : mapType == Bien ? 41 : mapType == BuoiToi || mapType == HoangHon || mapType == NuiLua ? 51 : mapType == ThienDuong ? 61 : mapType == Ho ? 65 : 31);
}

void Map::DrawPipeHorizontal(int x, int y, int width)
{
	SetTileID(x, y, mapType == BanNgay ? 22 : mapType == Bien ? 42 : mapType == BuoiToi ? 52 : 32);
	SetTileID(x, y - 1, mapType == BanNgay ? 23 : mapType == Bien ? 43 : mapType == BuoiToi ? 53 : 33);

	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i + 1, y, mapType == BanNgay ? 24 : mapType == Bien ? 44 : mapType == BuoiToi ? 54 : 34);
		SetTileID(x + i + 1, y - 1, mapType == BanNgay ? 25 : mapType == Bien ? 45 : mapType == BuoiToi ? 55 : 35);
	}

	SetTileID(x + width + 1, y, mapType == BanNgay ? 26 : mapType == Bien ? 46 : mapType == BuoiToi ? 56 : 36);
	SetTileID(x + width + 1, y - 1, mapType == BanNgay ? 27 : mapType == Bien ? 47 : mapType == BuoiToi ? 57 : 37);
}

void Map::DrawPipeVertical(int x, int y, int height)
{
	for (int i = 0; i < height; i++)
	{
		SetTileID(x, y - i, mapType == BanNgay ? 18 : mapType == Bien ? 38 : mapType == BuoiToi ? 48 : 28);
		SetTileID(x + 1, y - i, mapType == BanNgay ? 19 : mapType == Bien ? 39 : mapType == BuoiToi ? 49 : 29);
	}
}

void Map::DrawCoins(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			SetTileID(x + i, y - j, mapType == BanNgay || mapType == HoangHon || mapType == BuoiToi || mapType == BinhMinh || mapType == ThienDuong ? 70 : mapType == Bien ? 72 : 71);
		}
	}
}

void Map::DrawEnd(int x, int y, int height)
{
	for (int i = 0; i < height; i++)
	{
		SetTileID(x, y - i, mapType == BuoiToi || mapType == HoangHon ? 75 : 73);
	}
	SetTileID(x, y - height, mapType == BuoiToi || mapType == HoangHon ? 76 : 74);
}

void Map::DrawCastleSmall(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		SetTileID(x, y - i, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 1, y - i, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 2, y - i, mapType == DiaNguc ? 85 : 78);
		SetTileID(x + 3, y - i, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 4, y - i, mapType == DiaNguc ? 84 : 77);
	}

	SetTileID(x + 2, y - 1, mapType == DiaNguc ? 86 : 79);

	for (int i = 0; i < 5; i++)
	{
		SetTileID(x + i, y - 2, i == 0 || i == 4 ? mapType == DiaNguc ? 90 : 83 : mapType == DiaNguc ? 89 : 82);
	}

	SetTileID(x + 1, y - 3, mapType == DiaNguc ? 87 : 80);
	SetTileID(x + 2, y - 3, mapType == DiaNguc ? 84 : 77);
	SetTileID(x + 3, y - 3, mapType == DiaNguc ? 88 : 81);

	for (int i = 0; i < 3; i++)
	{
		SetTileID(x + i + 1, y - 4, mapType == DiaNguc ? 90 : 83);
	}
}

void Map::DrawCastleBig(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SetTileID(x + i, y - j, mapType == DiaNguc ? 84 : 77);
			SetTileID(x + i + 7, y - j, mapType == DiaNguc ? 84 : 77);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		SetTileID(x + 2 + i * 2, y, mapType == DiaNguc ? 85 : 78);
		SetTileID(x + 2 + i * 2, y - 1, mapType == DiaNguc ? 86 : 79);
	}

	for (int i = 0; i < 9; i++)
	{
		SetTileID(x + i, y - 2, mapType == DiaNguc ? 84 : 77);
	}

	for (int i = 0; i < 9; i++)
	{
		if (i < 2 || i > 6)
			SetTileID(x + i, y - 5, mapType == DiaNguc ? 90 : 83);
		else
			SetTileID(x + i, y - 5, mapType == DiaNguc ? 89 : 82);
	}

	for (int i = 0; i < 2; i++)
	{
		SetTileID(x + 3 + i * 2, y, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 3 + i * 2, y - 1, mapType == DiaNguc ? 84 : 77);
	}

	for (int i = 0; i < 2; i++)
	{
		SetTileID(x + 3 + i * 2, y - 3, mapType == DiaNguc ? 85 : 78);
		SetTileID(x + 3 + i * 2, y - 4, mapType == DiaNguc ? 86 : 79);
	}

	for (int i = 0; i < 3; i++)
	{
		SetTileID(x + 2 + i * 2, y - 3, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 2 + i * 2, y - 4, mapType == DiaNguc ? 84 : 77);
	}

	for (int i = 0; i < 2; i++)
	{
		SetTileID(x + 2, y - 6 - i, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 3, y - 6 - i, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 5, y - 6 - i, mapType == DiaNguc ? 84 : 77);
		SetTileID(x + 6, y - 6 - i, mapType == DiaNguc ? 84 : 77);
	}

	SetTileID(x + 4, y - 6, mapType == DiaNguc ? 85 : 78);
	SetTileID(x + 4, y - 7, mapType == DiaNguc ? 86 : 79);

	for (int i = 0; i < 3; i++)
	{
		SetTileID(x + 3 + i, y - 8, mapType == DiaNguc ? 89 : 82);
	}

	SetTileID(x + 2, y - 8, mapType == DiaNguc ? 90 : 83);
	SetTileID(x + 6, y - 8, mapType == DiaNguc ? 90 : 83);

	SetTileID(x + 3, y - 9, mapType == DiaNguc ? 87 : 80);
	SetTileID(x + 4, y - 9, mapType == DiaNguc ? 84 : 77);
	SetTileID(x + 5, y - 9, mapType == DiaNguc ? 88 : 81);

	for (int i = 0; i < 3; i++)
	{
		SetTileID(x + 3 + i, y - 10, mapType == DiaNguc ? 90 : 83);
	}
}

void Map::DrawCastleWall(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			SetTileID(x + i, y - j, mapType == DiaNguc ? 84 : 77);
		}
	}

	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i, y - height + 1, mapType == DiaNguc ? 90 : 83);
	}
}

void Map::DrawT(int x, int y, int width, int height)
{
	for (int i = 0; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			SetTileID(x + j, y - i, mapType == DiaNguc ? 94 : 91);
		}
	}

	for (int i = 1; i < width - 1; i++)
	{
		SetTileID(x + i, y - height + 1, mapType == DiaNguc ? 102 : 96);
	}

	SetTileID(x, y - height + 1, mapType == DiaNguc ? 101 : 95);
	SetTileID(x + width - 1, y - height + 1, mapType == DiaNguc ? 103 : 97);
}

void Map::DrawTMush(int x, int y, int width, int height)
{
	for (int i = 0; i < height - 1; i++)
	{
		SetTileID(x + width / 2, y - i, 93);
	}

	SetTileID(x + width / 2, y - height + 2, 92);

	for (int i = 0; i < width - 1; i++)
	{
		SetTileID(x + i, y - height + 1, 99);
	}

	SetTileID(x, y - height + 1, 98);
	SetTileID(x + width - 1, y - height + 1, 100);
}

void Map::DrawWater(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			SetTileID(x + i, y - j, mapType == Bien ? 104 : 106);
		}

		SetTileID(x + i, y - height + 1, mapType == Bien ? 105 : 107);
	}
}

void Map::DrawLava(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			SetTileID(x + i, y - j, 108);
		}

		SetTileID(x + i, y - height + 1, 109);
	}
}

void Map::DrawBridge(int x, int y, int width)
{
	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i, y, 110);
	}

	SetTileID(x + width - 1, y - 1, 111);
}

void Map::DrawBridge2(int x, int y, int width)
{
	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i, y, 112);
		SetTileID(x + i, y - 1, mapType == BuoiToi ? 114 : 113);
	}
}

void Map::DrawBonus(int x, int y, int width)
{
	for (int i = 0; i < width; i++)
	{
		SetTileID(x + i, y, 116);
	}
}

void Map::DrawBonusEnd(int x)
{
	for (int i = 0; i < 20; i++)
	{
		SetTileID(x + i, 14, 118);
	}
}

void Map::DrawSeeSaw(int x, int y, int width)
{
	SetTileID(x, y, mapType == DiaNguc ? 123 : 119);
	SetTileID(x + width - 1, y, mapType == DiaNguc ? 124 : 120);

	for (int i = 1; i < width - 1; i++)
	{
		SetTileID(x + i, y, mapType == DiaNguc ? 125 : 121);
	}
}

void Map::DrawBulletBill(int x, int y, int height)
{
	SetTileID(x, y - height - 1, 128);
	SetTileID(x, y - height, 129);

	for (int i = 0; i < height; i++)
	{
		SetTileID(x, y - i, 127);
	}
}

void Map::DrawPlatformLine(int x)
{
	for (int i = 0; i < mapHeight; i++)
	{
		SetTileID(x, i, 130);
	}
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
