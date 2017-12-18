#include "Player.h"
#include "Windows.h"

Player::Player()
{
	LoadData();
}

Player::~Player()
{
}

void Player::MoveX(int x)
{
	if (x > 0)
	{
		if (!CheckCollisionRB(x, -2) && !CheckCollisionRT(x, 2) && CheckCollisionRC(x))
		{
			if (xPlayer > 416)
				Window::getMap()->MoveMap(-x);
			else
				xPlayer += x;
		}
		else
		{
			MoveX(x - 1);
		}
	}
}

void Player::MoveY(int y)
{
	bool left, right;
	if (y > 0)
	{
		left = CheckCollisionLB(2, y);
		right = CheckCollisionRB(-2, y);

		if (!left && !right)
		{
			yPlayer += y;
		}
		else
		{
			if (jumpState == NhayXuong)
			{
				jumpState = DungYen;
			}
			MoveY(y - 1);
		}
	}
	else if (y < 0)
	{
		left = CheckCollisionLT(2, y);
		right = CheckCollisionRT(-2, y);

		if (!left && !right)
		{
			yPlayer += y;
		}
		else if (jumpState == NhayLen)
		{
			if (!left && right)
			{
				sf::Vector2i RT = Window::getMap()->getTilePosition((int)(xPlayer - Window::getMap()->GetX() + width - 1), (int)(yPlayer + y));

				if (!Window::getMap()->GetObject(Window::getMap()->GetTile(RT.x, RT.y)->GetID()))
				{

				}
				else
				{
					jumpState = NhayXuong;
				}
			}
		}
	}
}

void Player::UpdateAnimation(float time)
{
	//mario->Update(time - 0.65f + moveSpeed * 0.04f);
}

void Player::LoadData()
{
	vector<string> name;
	vector<float> time;
	time.push_back(0);

	// ---- 0 ----
	name.push_back("Source/images/mario/mario_death.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 1 ----
	name.push_back("Source/images/mario/mario.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 2 ----
	name.push_back("Source/images/mario/mario_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 3 ----
	name.push_back("Source/images/mario/mario_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 4 ----
	name.push_back("Source/images/mario/mario_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 5 ----
	name.push_back("Source/images/mario/mario_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 6 ----
	name.push_back("Source/images/mario/mario_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 7 ----
	name.push_back("Source/images/mario/mario_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 8 ----
	name.push_back("Source/images/mario/mario_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 9 ----
	name.push_back("Source/images/mario/mario_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 10 ----
	name.push_back("Source/images/mario/mario_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 11 ----
	name.push_back("Source/images/mario/mario1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 12 ----
	name.push_back("Source/images/mario/mario1_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 13 ----
	name.push_back("Source/images/mario/mario1_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 14 ----
	name.push_back("Source/images/mario/mario1_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 15 ----
	name.push_back("Source/images/mario/mario1_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 16 ----
	name.push_back("Source/images/mario/mario1_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 17 ----
	name.push_back("Source/images/mario/mario1_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 18 ----
	name.push_back("Source/images/mario/mario1_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 19 ----
	name.push_back("Source/images/mario/mario1_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 20 ----
	name.push_back("Source/images/mario/mario1_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 21 ----
	name.push_back("Source/images/mario/mario2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 22 ----
	name.push_back("Source/images/mario/mario2_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 23 ----
	name.push_back("Source/images/mario/mario2_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 24 ----
	name.push_back("Source/images/mario/mario2_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 25 ----
	name.push_back("Source/images/mario/mario2_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 26 ----
	name.push_back("Source/images/mario/mario2_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 27 ----
	name.push_back("Source/images/mario/mario2_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 28 ----
	name.push_back("Source/images/mario/mario2_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 29 ----
	name.push_back("Source/images/mario/mario2_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 30 ----
	name.push_back("Source/images/mario/mario2_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 31 ----
	name.push_back("Source/images/mario/mario2s.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 32 ----
	name.push_back("Source/images/mario/mario2s_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 33 ----
	name.push_back("Source/images/mario/mario2s_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 34 ----
	name.push_back("Source/images/mario/mario2s_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 35 ----
	name.push_back("Source/images/mario/mario2s_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 36 ----
	name.push_back("Source/images/mario/mario2s_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 37 ----
	name.push_back("Source/images/mario/mario2s_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 38 ----
	name.push_back("Source/images/mario/mario2s_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 39 ----
	name.push_back("Source/images/mario/mario2s_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 40 ----
	name.push_back("Source/images/mario/mario2s_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 41 ----
	name.push_back("Source/images/mario/mario_s0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 42 ----
	name.push_back("Source/images/mario/mario_s0_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 43 ----
	name.push_back("Source/images/mario/mario_s0_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 44 ----
	name.push_back("Source/images/mario/mario_s0_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 45 ----
	name.push_back("Source/images/mario/mario_s0_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 46 ----
	name.push_back("Source/images/mario/mario_s0_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 47 ----
	name.push_back("Source/images/mario/mario_s0_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 48 ----
	name.push_back("Source/images/mario/mario_s0_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 49 ----
	name.push_back("Source/images/mario/mario_s0_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 50 ----
	name.push_back("Source/images/mario/mario_s0_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
}

void Player::MovePlayer()
{
}

void Player::Playerphysics()
{
	if (!Window::getMap()->GetUnderWater())
	{

	}
}

bool Player::CheckCollisionLB(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xPlayer - Window::getMap()->GetX() + distanceX), (int)(yPlayer + height + distanceY));
}

bool Player::CheckCollisionLT(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xPlayer - Window::getMap()->GetX() + distanceX), (int)(yPlayer + distanceY));
}

bool Player::CheckCollisionRB(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xPlayer - Window::getMap()->GetX() + width + distanceX), (int)(yPlayer + height + distanceY));
}

bool Player::CheckCollisionRT(int distanceX, int distanceY)
{
	return Window::getMap()->CheckObject((int)(xPlayer - Window::getMap()->GetX() + width + distanceX), (int)(yPlayer + distanceY));
}

bool Player::CheckCollisionLC(int distance)
{
	return Window::getMap()->CheckObject((int)(xPlayer - Window::getMap()->GetX() + width + distance), (int)(yPlayer + (width / 2)));
}

bool Player::CheckCollisionRC(int distance)
{
	return Window::getMap()->CheckObject((int)(xPlayer - Window::getMap()->GetX() + distance), (int)(yPlayer + (width / 2)));
}