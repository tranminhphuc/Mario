#include "Player.h"
#include "Windows.h"

Player::Player(int xPlayer, int yPlayer)
{
	this->xPlayer = xPlayer;
	this->yPlayer = yPlayer;
	this->live = 3;
	this->level = 0;
	this->score = 0;
	this->coin = 0;

	this->id = 1;

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
				Window::GetMap()->MoveMap(-x);
			else
				xPlayer += x;
		}
		else
		{
			MoveX(x - 1);
			if (moveSpeed > 1 && jumpState == TrenMatDat)
				moveSpeed--;
		}
	}
	else if (x < 0)
	{
		if (!CheckCollisionLB(x, -2) && !CheckCollisionLT(x, 2) && (level == 0 ? true : (!CheckCollisionLC(x))))
		{
			if (xPlayer <= 192)
			{
				Window::GetMap()->MoveMap(-x);
			}
			else
			{
				xPlayer += x;
			}
		}
		else
		{
			MoveX(x + 1);
			if (moveSpeed > 1 && jumpSpeed == TrenMatDat)
				moveSpeed--;
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
				jumpState = TrenMatDat;
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
				sf::Vector2i RT = Window::GetMap()->getTilePosition((int)(xPlayer - Window::GetMap()->GetX() + width - 1), (int)(yPlayer + y));

				if (!Window::GetMap()->GetObject(Window::GetMap()->GetTile(RT.x, RT.y)->GetID())->GetVisible())
				{

				}
				else if(Window::GetMap()->GetObject(Window::GetMap()->GetTile(RT.x, RT.y)->GetID())->GetCanDestroy())
				{
					jumpState = NhayXuong;
				}
				else
				{
					jumpState = NhayXuong;
				}
			}
			else if (left && !right)
			{
				sf::Vector2i LT = Window::GetMap()->getTilePosition((int)(xPlayer - Window::GetMap()->GetX() + 1), (int)(yPlayer + y));

				if (!Window::GetMap()->GetObject(Window::GetMap()->GetTile(LT.x, LT.y)->GetID())->GetVisible())
				{

				}
				else if (Window::GetMap()->GetObject(Window::GetMap()->GetTile(LT.x, LT.y)->GetID())->GetCanDestroy())
				{

				}
				else
				{

				}
			}
		}
	}
}

void Player::PlayerPhysics()
{
	if (!Window::GetMap()->GetUnderWater())
	{
		if (jumpState == NhayLen)
		{
			MoveY(-(int)currentJumpSpeed);
			currentJumpDistance += currentJumpSpeed;
			currentJumpSpeed *= (currentJumpSpeed / jumpDistance > 0.75f ? 0.972f : 0.986f);

			if (currentJumpSpeed < 2.5f)
				currentJumpSpeed = 2.5f;

			if (!Window::space && currentJumpDistance > 64)
			{
				jumpDistance = 16;
				currentJumpDistance = 0;
				currentJumpSpeed = 2.5f;
			}

			if (jumpDistance <= currentJumpDistance)
				jumpState = NhayXuong;
		}
		else
		{

		}
	}
	else
	{
		if (jumpState == NhayLen)
		{
			if (yPlayer > Window::gameHeight - 12 * 32)
			{
				MoveY(-2);
				currentJumpDistance += 2;

				if (jumpDistance <= currentJumpDistance)
				{
					jumpState = NhayXuong;
					currentJumpDistance = 0;
				}
			}
			else
			{
				jumpState = NhayXuong;
			}
		}
		else
		{
			if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2))
			{

			}
			else if (jumpState == NhayXuong)
			{
				ResetJump();
			}
		}
	}
}

void Player::Update()
{
}

void Player::UpdateAnimation(float time)
{
	//mario->Update(time - 0.65f + moveSpeed * 0.04f);
}

void Player::PowerUpAnimation()
{
	if (inLevelDownAnimation)
	{
		if (inLevelAnimationID % 15 < 5)
		{
			id = 12;

			if (inLevelAnimationID != 0 && inLevelAnimationID % 15 == 0)
			{
				yPlayer += 16;
				xPlayer -= 4;
			}
		}
		else if (inLevelAnimationID % 15 < 10)
		{
			id = 67;

			if (inLevelAnimationID % 15 == 5)
			{
				yPlayer += 16;
				xPlayer += 1;
			}
		}
		else
		{
			id = 1;

			if (inLevelAnimationID % 15 == 10)
			{
				yPlayer -= 32;
				xPlayer += 3;
			}
		}

		inLevelAnimationID++;

		if (inLevelAnimationID > 59)
		{
			inLevelAnimation = false;
			yPlayer += 32;

			if (jumpState != TrenMatDat)
				SetMarioID(5);
		}
	}
	else if (level == 1)
	{
		if (inLevelAnimationID % 15 < 5)
		{
			id = 1;

			if (inLevelAnimationID != 0 && inLevelAnimationID % 15 == 0)
			{
				yPlayer += 32;
				xPlayer += 4;
			}
		}
		else if (inLevelAnimationID % 15 < 10)
		{
			id = 67;

			if (inLevelAnimationID % 15 == 5)
			{
				yPlayer -= 16;
				xPlayer -= 3;
			}
		}
		else
		{
			id = 12;

			if (inLevelAnimationID % 15 == 10)
			{
				yPlayer -= 16;
				xPlayer -= 1;
			}
		}

		inLevelAnimationID++;

		if (inLevelAnimationID > 59)
		{
			inLevelAnimation = false;

			if (jumpState != TrenMatDat)
				SetMarioID(5);
		}
	}
	else if (level == 2)
	{
		if (inLevelAnimationID % 10 < 5)
			id = id % 11 + 22;
		else
			id = id % 11 + 33;

		inLevelAnimationID++;

		if (inLevelAnimationID > 59)
		{
			inLevelAnimation = false;

			if (jumpState != TrenMatDat)
				SetMarioID(5);

			id = id % 11 + 22;
		}
	}
	else
	{
		inLevelAnimation = false;
	}
}

void Player::MoveAnimation()
{
	if (Window::GetTime() - 65 + moveSpeed * 4 > moveAnimationTime)
	{
		moveAnimationTime = Window::GetTime();

		if (id >= 4 + 11 * level)
			SetMarioID(2);
		else
			id++;
	}
}

void Player::SwimingAnimation()
{
	if (Window::GetTime() - 105 > moveAnimationTime)
	{
		moveAnimationTime = Window::GetTime();

		if (id % 11 == 8)
			SetMarioID(9);
		else
			SetMarioID(8);
	}
}

void Player::StartMove()
{
	moveAnimationTime = Window::GetTime();
	timePassed = Window::GetTime();
	moveSpeed = 1;
	move = true;

	if (Window::GetMap()->GetUnderWater())
		SetMarioID(8);
}

void Player::ResetMove()
{
	moveSpeed--;
	move = false;
}

void Player::StopMove()
{
	moveSpeed = 0;
	move = false;
	squat = false;
	changeMoveDirection = false;
	SetMarioID(1);
}

void Player::Jump()
{
	if (Window::GetMap()->GetUnderWater())
	{
		StartJump(1);
	}
	else if (jumpState == TrenMatDat)
	{
		StartJump(4);
	}
}

void Player::StartJump(int distance)
{
	currentJumpSpeed = jumpSpeed;
	jumpDistance = 32.0f * distance + 24;
	currentJumpDistance = 0;
	jumpState = NhayLen;

	if (!Window::GetMap()->GetUnderWater())
	{
		SetMarioID(5);
	}
	else
	{
		if (jumpState == TrenMatDat)
		{
			moveAnimationTime = Window::GetTime();
			SetMarioID(8);
			SwimingAnimation();
		}
	}
}

void Player::ResetJump()
{
	jumpState = TrenMatDat;
	jumpDistance = 0;
	currentJumpDistance = 0;
	currentFallingSpeed = 2.7f;
}

void Player::ResetLevel()
{
	level = 0;
	id = 1;
}

int Player::GetWidth()
{
	return level == 0 ? smallWidth : smallHeight;
}

int Player::GetHeight()
{
	return level == 0 ? smallHeight : squat ? 44 : bigHeight;
}

int Player::GetX()
{
	return xPlayer;
}

void Player::SetX(int xPlayer)
{
	this->xPlayer = xPlayer;
}

int Player::GetY()
{
	return yPlayer;
}

void Player::SetY(int yPlayer)
{
	this->yPlayer = yPlayer;
}

int Player::GetLevel()
{
	return level;
}

void Player::SetLevel(int level)
{
	this->level = level;
}

int Player::getLive()
{
	return live;
}

void Player::SetLive(int live)
{
	this->live = live;
}

int Player::GetMoveSpeed()
{
	return moveSpeed;
}

void Player::SetMoveSpeed(int moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

bool Player::GetSquat()
{
	return squat;
}

void Player::SetSquat(bool squat)
{
	if (squat && this->squat != squat)
	{
		if (level > 0)
			yPlayer += 20;

		this->squat = squat;
	}
	else if (this->squat != squat && Window::GetMap()->GetUnderWater())
	{
		if (level > 0)
			yPlayer -= 20;

		this->squat = squat;
	}
}

bool Player::GetStarEffect()
{
	return starEffect;
}

void Player::SetStarEffect(bool startEffect)
{
	this->starEffect = startEffect;
}

int Player::GetScore()
{
	return score;
}

void Player::SetScore(int score)
{
	this->score = score;
}

void Player::SetMarioID(int id)
{
	this->id = id + 11 * level;
}

int Player::GetCoin()
{
	return coin;
}

void Player::SetCoin(int coin)
{
	this->coin = coin;
}

int Player::GetJumpState()
{
	return jumpState;
}

bool Player::getMove()
{
	return move;
}

void Player::LoadData()
{
	vector<string> name;
	vector<unsigned int> time;
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
	name.push_back("Source/images/mario/mario.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 8 ----
	name.push_back("Source/images/mario/mario_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 9 ----
	name.push_back("Source/images/mario/mario_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 10 ----
	name.push_back("Source/images/mario/mario_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 11 ----
	name.push_back("Source/images/mario/mario_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 12 ----
	name.push_back("Source/images/mario/mario1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 13 ----
	name.push_back("Source/images/mario/mario1_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 14 ----
	name.push_back("Source/images/mario/mario1_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 15 ----
	name.push_back("Source/images/mario/mario1_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 16 ----
	name.push_back("Source/images/mario/mario1_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 17 ----
	name.push_back("Source/images/mario/mario1_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 18 ----
	name.push_back("Source/images/mario/mario1_squat.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 19 ----
	name.push_back("Source/images/mario/mario1_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 20 ----
	name.push_back("Source/images/mario/mario1_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 21 ----
	name.push_back("Source/images/mario/mario1_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 22 ----
	name.push_back("Source/images/mario/mario1_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 23 ----
	name.push_back("Source/images/mario/mario2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 24 ----
	name.push_back("Source/images/mario/mario2_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 25 ----
	name.push_back("Source/images/mario/mario2_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 26 ----
	name.push_back("Source/images/mario/mario2_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 27 ----
	name.push_back("Source/images/mario/mario2_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 28 ----
	name.push_back("Source/images/mario/mario2_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 29 ----
	name.push_back("Source/images/mario/mario2_squat.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 30 ----
	name.push_back("Source/images/mario/mario2_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 31 ----
	name.push_back("Source/images/mario/mario2_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 32 ----
	name.push_back("Source/images/mario/mario2_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 33 ----
	name.push_back("Source/images/mario/mario2_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 34 ----
	name.push_back("Source/images/mario/mario2s.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 35 ----
	name.push_back("Source/images/mario/mario2s_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 36 ----
	name.push_back("Source/images/mario/mario2s_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 37 ----
	name.push_back("Source/images/mario/mario2s_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 38 ----
	name.push_back("Source/images/mario/mario2s_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 39 ----
	name.push_back("Source/images/mario/mario2s_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 40 ----
	name.push_back("Source/images/mario/mario2s_squat.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 41 ----
	name.push_back("Source/images/mario/mario2s_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 42 ----
	name.push_back("Source/images/mario/mario2s_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 43 ----
	name.push_back("Source/images/mario/mario2s_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 44 ----
	name.push_back("Source/images/mario/mario2s_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 445 ----
	name.push_back("Source/images/mario/mario_s0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 46 ----
	name.push_back("Source/images/mario/mario_s0_move0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 47 ----
	name.push_back("Source/images/mario/mario_s0_move1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 48 ----
	name.push_back("Source/images/mario/mario_s0_move2.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 49 ----
	name.push_back("Source/images/mario/mario_s0_jump.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 50 ----
	name.push_back("Source/images/mario/mario_s0_st.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 51 ----
	name.push_back("Source/images/mario/mario_s0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 52 ----
	name.push_back("Source/images/mario/mario_s0_underwater0.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 53 ----
	name.push_back("Source/images/mario/mario_s0_underwater1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 54 ----
	name.push_back("Source/images/mario/mario_s0_end.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
	// ---- 55 ----
	name.push_back("Source/images/mario/mario_s0_end1.bmp");
	mario.push_back(new Animation(name, time));
	name.clear();
}

void Player::MovePlayer()
{
	if (move && !changeMoveDirection && (!squat || level == 0))
	{
		if (moveSpeed > maxSpeed)
		{
			moveSpeed--;
		}
		else if (Window::GetTime() - (100 + 35 * moveSpeed) >= timePassed && moveSpeed < maxSpeed)
		{
			moveSpeed++;
			timePassed = Window::GetTime();
		}
	}
	else
	{
		if (Window::GetTime() - (50 + 15 * (maxSpeed - moveSpeed) * (squat &&level > 0 ? 6 : 1)) > timePassed && moveSpeed != 0)
		{
			moveSpeed--;
			timePassed = Window::GetTime();
		}

		if (changeMoveDirection && moveSpeed <= 1)
		{
			moveDirection = newMoveDiretion;
			changeMoveDirection = false;
			move = true;
		}
	}

	if (moveSpeed > 0)
	{
		if (moveDirection)
			MoveX(moveSpeed);
		else
			MoveX(-moveSpeed);
	}
	else if (jumpState = TrenMatDat)
	{
		MoveX(0);
	}
	else
	{
		MoveX(0);
	}
}

bool Player::CheckCollisionLB(int distanceX, int distanceY)
{
	return Window::GetMap()->CheckObject((int)(xPlayer - Window::GetMap()->GetX() + distanceX), (int)(yPlayer + GetHeight() + distanceY));
}

bool Player::CheckCollisionLT(int distanceX, int distanceY)
{
	return Window::GetMap()->CheckObject((int)(xPlayer - Window::GetMap()->GetX() + distanceX), (int)(yPlayer + distanceY));
}

bool Player::CheckCollisionRB(int distanceX, int distanceY)
{
	return Window::GetMap()->CheckObject((int)(xPlayer - Window::GetMap()->GetX() + GetWidth() + distanceX), (int)(yPlayer + GetHeight() + distanceY));
}

bool Player::CheckCollisionRT(int distanceX, int distanceY)
{
	return Window::GetMap()->CheckObject((int)(xPlayer - Window::GetMap()->GetX() + GetWidth() + distanceX), (int)(yPlayer + distanceY));
}

bool Player::CheckCollisionLC(int distance)
{
	return Window::GetMap()->CheckObject((int)(xPlayer - Window::GetMap()->GetX() + GetWidth() + distance), (int)(yPlayer + (GetHeight() / 2)));
}

bool Player::CheckCollisionRC(int distance)
{
	return Window::GetMap()->CheckObject((int)(xPlayer - Window::GetMap()->GetX() + distance), (int)(yPlayer + (GetHeight() / 2)));
}
