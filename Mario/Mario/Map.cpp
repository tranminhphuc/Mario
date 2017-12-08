#include "Map.h"

Map::Map()
{
	Xmap = 0;
	Ymap = 0;
	maptype = NgoaiTroiBanNgay;

	LoadGameData();
	LoadLevel_1_1();
}

Map::~Map()
{

}

void Map::Update(float time)
{
	listBlock[16]->GetAnimation()->Update(time);
	listBlock[18]->GetAnimation()->Update(time);
	listBlock[73]->GetAnimation()->Update(time);
	listBlock[74]->GetAnimation()->Update(time);
	listBlock[75]->GetAnimation()->Update(time);
}

void Map::Draw(RenderWindow & window)
{
	DrawMap(window);
}

void Map::DrawMap(RenderWindow & window)
{
	for (int i = GetStartMap(), iEnd = GetEndMap(); i < iEnd && i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if (tile[i][j]->GetID() != 0)
			{
				listBlock[tile[i][j]->GetID()]->Draw(window, (float)(32 * i + Xmap), (float)(j * 32));
			}
		}
	}
}

void Map::SetBackGroundColor(RenderWindow & window)
{
	switch (maptype)
	{
	case NgoaiTroiBanNgay: case Bien: case Ho: case ThienDuong:
		window.clear(Color(93, 148, 252, 255));
		break;
	case LongDat: case NuiLua: case NgoaiTroiBanDem: case DiaNguc:
		window.clear(Color(0, 0, 0, 255));
		break;
	default:
		window.clear(Color(93, 148, 252, 255));
		break;
	}
}

bool Map::CheckCollision(int x, int y)
{
	return listBlock[tile[x][y]->GetID()]->getCollision();
}

void Map::MoveMap(int x)
{
	if (Xmap + x > 0)
	{
		Xmap = 0;
	}
	else
	{
		Xmap += x;
	}
}

void Map::LoadGameData()
{
	vector<string> name;
	vector<float> time;

	// ----- 0 -----
	name.push_back("Source/images/transp.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), false));
	name.clear();
	time.clear();
	// ----- 1 -----
	name.push_back("Source/images/gnd_red_1.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 2 -----
	name.push_back("Source/images/gnd1.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 3 -----
	name.push_back("Source/images/uw_0.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 4 -----
	name.push_back("Source/images/gnd2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 5 -----
	name.push_back("Source/images/gnd_4.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 6 -----
	name.push_back("Source/images/gnd_5.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 7 -----
	name.push_back("Source/images/gnd_red2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 8 -----
	name.push_back("Source/images/gnd1_2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 9 -----
	name.push_back("Source/images/gnd2_2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 10 -----
	name.push_back("Source/images/brickred.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 11 -----
	name.push_back("Source/images/brick1.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 12 -----
	name.push_back("Source/images/brick2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 13 -----
	name.push_back("Source/images/gnd_red2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 14 -----
	name.push_back("Source/images/gnd1_2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 15 -----
	name.push_back("Source/images/gnd2_2.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 16 -----
	name.push_back("Source/images/blockq_0.bmp");
	time.push_back(0.3f);
	name.push_back("Source/images/blockq_2.bmp");
	time.push_back(0.03f);
	name.push_back("Source/images/blockq_1.bmp");
	time.push_back(0.13f);
	name.push_back("Source/images/blockq_2.bmp");
	time.push_back(0.14f);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 17 -----
	name.push_back("Source/images/blockq_used.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 18 -----
	name.push_back("Source/images/blockq1_0.bmp");
	time.push_back(0.3f);
	name.push_back("Source/images/blockq1_2.bmp");
	time.push_back(0.03f);
	name.push_back("Source/images/blockq1_1.bmp");
	time.push_back(0.13f);
	name.push_back("Source/images/blockq1_2.bmp");
	time.push_back(0.14f);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 19 -----
	name.push_back("Source/images/blockq1_used.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 20 -----
	name.push_back("Source/images/blockq2_used.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 21 -----
	name.push_back("Source/images/pipe_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 22 -----
	name.push_back("Source/images/pipe_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 23 -----
	name.push_back("Source/images/pipe_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 24 -----
	name.push_back("Source/images/pipe_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 25 -----
	name.push_back("Source/images/pipe_hor_bot_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 26 -----
	name.push_back("Source/images/pipe_hor_top_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 27 -----
	name.push_back("Source/images/pipe_hor_bot_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 28 -----
	name.push_back("Source/images/pipe_hor_top_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 29 -----
	name.push_back("Source/images/pipe_hor_bot_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 30 -----
	name.push_back("Source/images/pipe_hor_top_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 31 -----
	name.push_back("Source/images/pipe1_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 32 -----
	name.push_back("Source/images/pipe1_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 33 -----
	name.push_back("Source/images/pipe1_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 34 -----
	name.push_back("Source/images/pipe1_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 35 -----
	name.push_back("Source/images/pipe1_hor_bot_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 36 -----
	name.push_back("Source/images/pipe1_hor_top_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 37 -----
	name.push_back("Source/images/pipe1_hor_bot_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 38 -----
	name.push_back("Source/images/pipe1_hor_top_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 39 -----
	name.push_back("Source/images/pipe1_hor_bot_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 40 -----
	name.push_back("Source/images/pipe1_hor_top_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 41 -----
	name.push_back("Source/images/pipe2_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 42 -----
	name.push_back("Source/images/pipe2_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 43 -----
	name.push_back("Source/images/pipe2_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 44 -----
	name.push_back("Source/images/pipe2_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 45 -----
	name.push_back("Source/images/pipe2_hor_bot_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 46 -----
	name.push_back("Source/images/pipe2_hor_top_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 47 -----
	name.push_back("Source/images/pipe2_hor_bot_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 48 -----
	name.push_back("Source/images/pipe2_hor_top_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 49 -----
	name.push_back("Source/images/pipe2_hor_bot_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 50 -----
	name.push_back("Source/images/pipe2_hor_top_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 51 -----
	name.push_back("Source/images/pipe3_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 52 -----
	name.push_back("Source/images/pipe3_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 53 -----
	name.push_back("Source/images/pipe3_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 54 -----
	name.push_back("Source/images/pipe3_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 55 -----
	name.push_back("Source/images/pipe3_hor_bot_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 56 -----
	name.push_back("Source/images/pipe3_hor_top_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 57 -----
	name.push_back("Source/images/pipe3_hor_bot_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 58 -----
	name.push_back("Source/images/pipe3_hor_top_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 59 -----
	name.push_back("Source/images/pipe3_hor_bot_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 60 -----
	name.push_back("Source/images/pipe3_hor_top_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 61 -----
	name.push_back("Source/images/pipe4_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 62 -----
	name.push_back("Source/images/pipe4_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 63 -----
	name.push_back("Source/images/pipe4_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 64 -----
	name.push_back("Source/images/pipe4_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 65 -----
	name.push_back("Source/images/pipe5_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 66 -----
	name.push_back("Source/images/pipe5_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 67 -----
	name.push_back("Source/images/pipe5_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 68 -----
	name.push_back("Source/images/pipe5_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 69 -----
	name.push_back("Source/images/pipe6_left_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 70 -----
	name.push_back("Source/images/pipe6_right_bot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 71 -----
	name.push_back("Source/images/pipe6_left_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 72 -----
	name.push_back("Source/images/pipe6_right_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 73 -----
	name.push_back("Source/images/coin_use00.bmp");
	time.push_back(0.3f);
	name.push_back("Source/images/coin_use02.bmp");
	time.push_back(0.03f);
	name.push_back("Source/images/coin_use01.bmp");
	time.push_back(0.13f);
	name.push_back("Source/images/coin_use02.bmp");
	time.push_back(0.14f);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 74 -----
	name.push_back("Source/images/coin_use0.bmp");
	time.push_back(0.3f);
	name.push_back("Source/images/coin_use2.bmp");
	time.push_back(0.03f);
	name.push_back("Source/images/coin_use1.bmp");
	time.push_back(0.13f);
	name.push_back("Source/images/coin_use2.bmp");
	time.push_back(0.14f);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 75 -----
	name.push_back("Source/images/coin_use30.bmp");
	time.push_back(0.3f);
	name.push_back("Source/images/coin_use32.bmp");
	time.push_back(0.03f);
	name.push_back("Source/images/coin_use31.bmp");
	time.push_back(0.13f);
	name.push_back("Source/images/coin_use32.bmp");
	time.push_back(0.14f);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 76 -----
	name.push_back("Source/images/end0_l.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 77 -----
	name.push_back("Source/images/end0_dot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 78 -----
	name.push_back("Source/images/end1_l.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 79 -----
	name.push_back("Source/images/end1_dot.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 80 -----
	name.push_back("Source/images/castle0_brick.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 81 -----
	name.push_back("Source/images/castle0_center_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 82 -----
	name.push_back("Source/images/castle0_center_center_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 83 -----
	name.push_back("Source/images/castle0_center_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 84 -----
	name.push_back("Source/images/castle0_center_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 85 -----
	name.push_back("Source/images/castle0_top0.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 86 -----
	name.push_back("Source/images/castle0_top1.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 87 -----
	name.push_back("Source/images/castle1_brick.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 88 -----
	name.push_back("Source/images/castle1_center_center.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 89 -----
	name.push_back("Source/images/castle1_center_center_top.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 90 -----
	name.push_back("Source/images/castle1_center_left.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 91 -----
	name.push_back("Source/images/castle1_center_right.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 92 -----
	name.push_back("Source/images/castle1_top0.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
	// ----- 93 -----
	name.push_back("Source/images/castle1_top1.bmp");
	time.push_back(0);
	listBlock.push_back(new Object(new Animation(name, time), true));
	name.clear();
	time.clear();
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

void Map::LoadLevel_1_1()
{
	ClearMap();

	mapWidth = 260;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();

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

	DrawPiPe(28, 12, 1);
	DrawPiPe(38, 12, 2);
	DrawPiPe(46, 12, 3);
	DrawPiPe(57, 12, 3);
	DrawPiPe(163, 12, 1);
	DrawPiPe(179, 12, 1);

	DrawEnd(198, 11, 9);
	DrawCastleSmall(202, 12);

	maptype = LongDat;

	DrawGND(240, 14, 17, 2);

	DrawBrick(240, 12, 1, 11);
	DrawBrick(244, 12, 7, 3);
	DrawBrick(244, 2, 7, 1);

	DrawCoin(244, 9, 7, 1);
	DrawCoin(244, 7, 7, 1);
	DrawCoin(244, 5, 7, 1);

	DrawPiPeVertical(255, 12, 11);
	DrawPiPeHorizontal(253, 12, 1);

	maptype = NgoaiTroiBanNgay;
}

void Map::LoadLevel_1_2()
{
	ClearMap();

	mapWidth = 330;
	mapHeight = 15;
	mapTime = 400;
	maptype = LongDat;

	CreateMap();
}

void Map::LoadLevel_1_3()
{
	ClearMap();

	mapWidth = 270;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_1_4()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_2_1()
{
	ClearMap();

	mapWidth = 365;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_2_2()
{
	ClearMap();

	mapWidth = 320;
	mapHeight = 15;
	mapTime = 400;
	maptype = Bien;

	CreateMap();
}

void Map::LoadLevel_2_3()
{
	ClearMap();

	mapWidth = 250;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_2_4()
{
	ClearMap();

	mapWidth = 190;
	mapHeight = 15;
	mapTime = 300;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_3_1()
{
	ClearMap();

	mapWidth = 375;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanDem;

	CreateMap();
}

void Map::LoadLevel_3_2()
{
	ClearMap();

	mapWidth = 230;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanDem;

	CreateMap();
}

void Map::LoadLevel_3_3()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanDem;

	CreateMap();
}

void Map::LoadLevel_3_4()
{
	ClearMap();

	mapWidth = 225;
	mapHeight = 15;
	mapTime = 300;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_4_1()
{
	ClearMap();

	mapWidth = 325;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_4_2()
{
	ClearMap();

	mapWidth = 435;
	mapHeight = 15;
	mapTime = 400;
	maptype = LongDat;

	CreateMap();
}

void Map::LoadLevel_4_3()
{
	ClearMap();

	mapWidth = 170;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_4_4()
{
	ClearMap();

	mapWidth = 200;
	mapHeight = 15;
	mapTime = 300;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_5_1()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_5_2()
{
	ClearMap();

	mapWidth = 415;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_5_3()
{
	ClearMap();

	mapWidth = 270;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_5_4()
{
	ClearMap();

	mapWidth = 190;
	mapHeight = 15;
	mapTime = 300;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_6_1()
{
	ClearMap();

	mapWidth = 210;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanDem;

	CreateMap();
}

void Map::LoadLevel_6_2()
{
	ClearMap();

	mapWidth = 495;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_6_3()
{
	ClearMap();

	mapWidth = 200;
	mapHeight = 15;
	mapTime = 300;
	maptype = DiaNguc;

	CreateMap();
}

void Map::LoadLevel_6_4()
{
	ClearMap();

	mapWidth = 180;
	mapHeight = 15;
	mapTime = 300;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_7_1()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_7_2()
{
	ClearMap();

	mapWidth = 320;
	mapHeight = 15;
	mapTime = 400;
	maptype = Bien;

	CreateMap();
}

void Map::LoadLevel_7_3()
{
	ClearMap();

	mapWidth = 250;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_7_4()
{
	ClearMap();

	mapWidth = 300;
	mapHeight = 15;
	mapTime = 400;
	maptype = NuiLua;

	CreateMap();
}

void Map::LoadLevel_8_1()
{
	ClearMap();

	mapWidth = 440;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_8_2()
{
	ClearMap();

	mapWidth = 400;
	mapHeight = 15;
	mapTime = 400;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_8_3()
{
	ClearMap();

	mapWidth = 240;
	mapHeight = 15;
	mapTime = 300;
	maptype = NgoaiTroiBanNgay;

	CreateMap();
}

void Map::LoadLevel_8_4()
{
	ClearMap();

	mapWidth = 480;
	mapHeight = 15;
	mapTime = 400;
	maptype = NuiLua;

	CreateMap();
}

void Map::DrawGND(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tile[x + i][y - j]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 1 : maptype == LongDat ? 2 : maptype == Bien ? 3 : maptype == DiaNguc ? 4 : maptype == Ho ? 6 : 5);
		}
	}
}

void Map::DrawGND2(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tile[x + i][y - j]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 13 : maptype == NuiLua ? 15 : 14);
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
				tile[x + i][y - j]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 13 : maptype == NuiLua ? 15 : 14);
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
				tile[x + i][y - j + 1]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 13 : maptype == NuiLua ? 15 : 14);
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
			tile[x + i][y - j]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 10 : maptype == LongDat ? 11 : 12);
		}
	}
}

void Map::DrawBlockQ(int x, int y, int width)
{
	for (int i = 0; i < width; i++)
	{
		tile[x + i][y]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 16 : 17);
	}
}

void Map::DrawPiPe(int x, int y, int height)
{
	for (int i = 0; i < height; i++)
	{
		tile[x][y - i]->SetID(maptype == NgoaiTroiBanNgay ? 21 : maptype == Bien ? 41 : maptype == NgoaiTroiBanDem ? 51 : maptype == ThienDuong ? 61 : maptype == NuiLua ? 69 : maptype == Ho ? 65 : 31);
		tile[x + 1][y - i]->SetID(maptype == NgoaiTroiBanNgay ? 22 : maptype == Bien ? 42 : maptype == NgoaiTroiBanDem ? 52 : maptype == ThienDuong ? 62 : maptype == NuiLua ? 70 : maptype == Ho ? 66 : 32);
	}

	tile[x][y - height]->SetID(maptype == NgoaiTroiBanNgay ? 23 : maptype == Bien ? 43 : maptype == NgoaiTroiBanDem ? 53 : maptype == ThienDuong ? 63 : maptype == NuiLua ? 71 : maptype == Ho ? 67 : 33);
	tile[x + 1][y - height]->SetID(maptype == NgoaiTroiBanNgay ? 24 : maptype == Bien ? 44 : maptype == NgoaiTroiBanDem ? 54 : maptype == ThienDuong ? 64 : maptype == NuiLua ? 72 : maptype == Ho ? 68 : 34);
}

void Map::DrawPiPeHorizontal(int x, int y, int width)
{
	tile[x][y]->SetID(maptype == NgoaiTroiBanNgay ? 25 : maptype == Bien ? 45 : maptype == NgoaiTroiBanDem ? 55 : 35);
	tile[x][y - 1]->SetID(maptype == NgoaiTroiBanNgay ? 26 : maptype == Bien ? 46 : maptype == NgoaiTroiBanDem ? 56 : 36);

	for (int i = 0; i < width; i++)
	{
		tile[x + i + 1][y]->SetID(maptype == NgoaiTroiBanNgay ? 27 : maptype == Bien ? 47 : maptype == NgoaiTroiBanDem ? 57 : 37);
		tile[x + i + 1][y - 1]->SetID(maptype == NgoaiTroiBanNgay ? 28 : maptype == Bien ? 48 : maptype == NgoaiTroiBanDem ? 58 : 38);
	}

	tile[x + width + 1][y]->SetID(maptype == NgoaiTroiBanNgay ? 29 : maptype == Bien ? 49 : maptype == NgoaiTroiBanDem ? 59 : 39);
	tile[x + width + 1][y - 1]->SetID(maptype == NgoaiTroiBanNgay ? 30 : maptype == Bien ? 50 : maptype == NgoaiTroiBanDem ? 60 : 40);
}

void Map::DrawPiPeVertical(int x, int y, int height)
{
	for (int i = 0; i < height; i++)
	{
		tile[x][y - i]->SetID(maptype == NgoaiTroiBanNgay ? 21 : maptype == Bien ? 41 : maptype == NgoaiTroiBanDem ? 51 : 31);
		tile[x + 1][y - i]->SetID(maptype == NgoaiTroiBanNgay ? 22 : maptype == Bien ? 42 : maptype == NgoaiTroiBanDem ? 52 : 32);
	}
}

void Map::DrawCoin(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tile[x + i][y - j]->SetID(maptype == NgoaiTroiBanNgay || maptype == NgoaiTroiBanDem ? 73 : maptype == Bien ? 75 : 74);
		}
	}
}

void Map::DrawEnd(int x, int y, int height)
{
	for (int i = 0; i < height; i++)
	{
		tile[x][y - i]->SetID(maptype == NgoaiTroiBanDem ? 78 : 76);
	}
	tile[x][y - height]->SetID(maptype == NgoaiTroiBanDem ? 79 : 77);
}

void Map::DrawCastleSmall(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		tile[x][y - i]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 1][y - i]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 2][y - i]->SetID(maptype == NuiLua ? 88 : 81);
		tile[x + 3][y - i]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 4][y - i]->SetID(maptype == NuiLua ? 87 : 80);
	}

	tile[x + 2][y - 1]->SetID(maptype == NuiLua ? 89 : 82);

	for (int i = 0; i < 5; i++)
	{
		tile[x + i][y - 2]->SetID(i == 0 || i == 4 ? maptype == NuiLua ? 93 : 86 : maptype == NuiLua ? 92 : 85);
	}

	tile[x + 1][y - 3]->SetID(maptype == NuiLua ? 90 : 83);
	tile[x + 2][y - 3]->SetID(maptype == NuiLua ? 87 : 80);
	tile[x + 3][y - 3]->SetID(maptype == NuiLua ? 91 : 84);

	for (int i = 0; i < 3; i++)
	{
		tile[x + i + 1][y - 4]->SetID(maptype == NuiLua ? 93 : 86);
	}
}

void Map::DrawCastleBig(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tile[x + i][y - j]->SetID(maptype == NuiLua ? 87 : 80);
			tile[x + i + 7][y - j]->SetID(maptype == NuiLua ? 87 : 80);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		tile[x + 2 + i * 2][y]->SetID(maptype == NuiLua ? 88 : 81);
		tile[x + 2 + i * 2][y - 1]->SetID(maptype == NuiLua ? 89 : 82);
	}

	for (int i = 0; i < 9; i++)
	{
		tile[x + i][y - 2]->SetID(maptype == NuiLua ? 87 : 80);
	}

	for (int i = 0; i < 9; i++)
	{
		if (i < 2 || i > 6)
		{
			tile[x + i][y - 5]->SetID(maptype == NuiLua ? 93 : 86);
		}
		else
		{
			tile[x + i][y - 5]->SetID(maptype == NuiLua ? 92 : 85);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		tile[x + 3 + i * 2][y]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 3 + i * 2][y - 1]->SetID(maptype == NuiLua ? 87 : 80);
	}

	for (int i = 0; i < 2; i++)
	{
		tile[x + 3 + i * 2][y - 3]->SetID(maptype == NuiLua ? 88 : 81);
		tile[x + 3 + i * 2][y - 4]->SetID(maptype == NuiLua ? 89 : 82);
	}

	for (int i = 0; i < 3; i++)
	{
		tile[x + 2 + i * 2][y - 3]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 2 + i * 2][y - 4]->SetID(maptype == NuiLua ? 87 : 80);
	}

	for (int i = 0; i < 2; i++)
	{
		tile[x + 2][y - 6 - 1]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 3][y - 6 - 1]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 5][y - 6 - 1]->SetID(maptype == NuiLua ? 87 : 80);
		tile[x + 6][y - 6 - 1]->SetID(maptype == NuiLua ? 87 : 80);
	}

	tile[x + 4][y - 6]->SetID(maptype == NuiLua ? 88 : 81);
	tile[x + 4][y - 7]->SetID(maptype == NuiLua ? 89 : 82);

	for (int i = 0; i < 3; i++)
	{
		tile[x + 3 + i][y - 8]->SetID(maptype == NuiLua ? 92 : 85);
	}

	tile[x + 2][y - 8]->SetID(maptype == NuiLua ? 93 : 86);
	tile[x + 6][y - 8]->SetID(maptype == NuiLua ? 93 : 86);

	tile[x + 3][y - 9]->SetID(maptype == NuiLua ? 90 : 83);
	tile[x + 4][y - 9]->SetID(maptype == NuiLua ? 87 : 80);
	tile[x + 5][y - 9]->SetID(maptype == NuiLua ? 91 : 84);

	for (int i = 0; i < 3; i++)
	{
		tile[x + 3 + i][y - 10]->SetID(maptype == NuiLua ? 93 : 86);
	}
}

void Map::DrawCastleWall(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tile[x + i][y - j]->SetID(maptype == NuiLua ? 87 : 80);
		}
	}

	for (int i = 0; i < width; i++)
	{
		tile[x + i][y - height - 1]->SetID(maptype == NuiLua ? 89 : 82);
	}
}

int Map::GetStartMap()
{
	return (int)(-Xmap - (-(int)Xmap % 32)) / 32;
}

int Map::GetEndMap()
{
	return (int)(-Xmap - (-(int)Xmap % 32) + 800) / 32 + 2;
}

Vector2i Map::getBlock(float x, float y)
{
	return Vector2i((int)(x < 0 ? 0 : x), (int)(y > 480 ? 0 : y));
}
