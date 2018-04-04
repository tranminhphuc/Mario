#include "Player.h"
#include "Windows.h"

Player::Player(float xPlayer, float yPlayer)
{
	this->xPlayer = xPlayer;
	this->yPlayer = yPlayer;
	this->live = 3;
	this->level = 0;
	this->score = 0;
	this->coin = 0;

	this->id = 1;

	LoadData("Source/files/Player.txt");
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
				Window::GetMap()->MoveMap(-x);
			else
				xPlayer += x;
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
				jumpState = TrenMatDat;

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
				sf::Vector2i RT = Window::GetMap()->GetTilePosition((int)(xPlayer - Window::GetMap()->GetX() + width - 1), (int)(yPlayer + y));

				if (!Window::GetMap()->GetObject(Window::GetMap()->GetTile(RT.x, RT.y)->GetID())->GetVisible())
				{
					if (Window::GetMap()->Destroy(RT.x, RT.y, Window::GetMap()->GetTile(RT.x, RT.y)->GetID(), 0))
						jumpState = NhayXuong;
					else
						yPlayer += y;
				}
				else if(Window::GetMap()->GetObject(Window::GetMap()->GetTile(RT.x, RT.y)->GetID())->GetCanDestroy())
				{
					if (Window::GetMap()->Destroy(RT.x, RT.y, Window::GetMap()->GetTile(RT.x, RT.y)->GetID(), 0))
						jumpState = NhayXuong;
					else
						yPlayer += y;
				}
				else
				{
					jumpState = NhayXuong;
				}
			}
			else if (left && !right)
			{
				sf::Vector2i LT = Window::GetMap()->GetTilePosition((int)(xPlayer - Window::GetMap()->GetX() + 1), (int)(yPlayer + y));

				if (!Window::GetMap()->GetObject(Window::GetMap()->GetTile(LT.x, LT.y)->GetID())->GetVisible())
				{
					if (Window::GetMap()->Destroy(LT.x, LT.y, Window::GetMap()->GetTile(LT.x, LT.y)->GetID(), 0))
						jumpState = NhayXuong;
					else
						yPlayer += y;
				}
				else if (Window::GetMap()->GetObject(Window::GetMap()->GetTile(LT.x, LT.y)->GetID())->GetCanDestroy())
				{
					if (Window::GetMap()->Destroy(LT.x, LT.y, Window::GetMap()->GetTile(LT.x, LT.y)->GetID(), 0))
						jumpState = NhayXuong;
					else
						yPlayer += y;
				}
				else
				{
					jumpState = NhayXuong;
				}
			}
		}

		MoveY(y + 1);
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
			currentJumpSpeed *= (currentJumpDistance / jumpDistance > 0.75f ? 0.972f : 0.986f);

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
	PlayerPhysics();
	MovePlayer();

	if (frameID > 0)
		frameID--;
	else if (comboPoint > 1)
		comboPoint--;

	if (inLevelDownAnimation)
	{
		if (inLevelDownAnimationID > 0)
			inLevelDownAnimationID--;
	}
}

void Player::Draw(sf::RenderWindow & window)
{
	if (!inLevelDownAnimation)
	{
		mario[GetMarioID()]->getTexture()->Draw(window, sf::Vector2f(xPlayer, yPlayer));
	}
	else
	{
		if (inLevelDownAnimationID % 15 < (inLevelDownAnimationID > 120 ? 7 : inLevelDownAnimationID > 90 ? 9 : inLevelDownAnimationID > 60 ? 11 : inLevelDownAnimationID > 30 ? 13 : 14))
		{
			mario[GetMarioID()]->getTexture()->Draw(window, sf::Vector2f(xPlayer, yPlayer));
		}
	}
}

void Player::PowerUpAnimation()
{
	if (inLevelDownAnimation)
	{
		if (inLevelDownAnimationID % 15 < 5)
		{
			id = 12;

			if (inLevelDownAnimationID != 0 && inLevelDownAnimationID % 15 == 0)
			{
				yPlayer += 16;
				xPlayer -= 4;
			}
		}
		else if (inLevelDownAnimationID % 15 < 10)
		{
			id = 67;

			if (inLevelDownAnimationID % 15 == 5)
			{
				yPlayer += 16;
				xPlayer += 1;
			}
		}
		else
		{
			id = 1;

			if (inLevelDownAnimationID % 15 == 10)
			{
				yPlayer -= 32;
				xPlayer += 3;
			}
		}

		inLevelDownAnimationID++;

		if (inLevelDownAnimationID > 59)
		{
			inLevelAnimation = false;
			yPlayer += 32;

			if (jumpState != TrenMatDat)
				SetMarioID(5);
		}
	}
	else if (level == 1)
	{
		if (inLevelDownAnimationID % 15 < 5)
		{
			id = 1;

			if (inLevelDownAnimationID != 0 && inLevelDownAnimationID % 15 == 0)
			{
				yPlayer += 32;
				xPlayer += 4;
			}
		}
		else if (inLevelDownAnimationID % 15 < 10)
		{
			id = 67;

			if (inLevelDownAnimationID % 15 == 5)
			{
				yPlayer -= 16;
				xPlayer -= 3;
			}
		}
		else
		{
			id = 12;

			if (inLevelDownAnimationID % 15 == 10)
			{
				yPlayer -= 16;
				xPlayer -= 1;
			}
		}

		inLevelDownAnimationID++;

		if (inLevelDownAnimationID > 59)
		{
			inLevelAnimation = false;

			if (jumpState != TrenMatDat)
				SetMarioID(5);
		}
	}
	else if (level == 2)
	{
		if (inLevelDownAnimationID % 10 < 5)
			id = id % 11 + 22;
		else
			id = id % 11 + 33;

		inLevelDownAnimationID++;

		if (inLevelDownAnimationID > 59)
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

float Player::GetX()
{
	return xPlayer;
}

void Player::SetX(float xPlayer)
{
	this->xPlayer = xPlayer;
}

float Player::GetY()
{
	return yPlayer;
}

void Player::SetY(float yPlayer)
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

int Player::GetMarioID()
{
	return id;
}

void Player::SetMarioID(int id)
{
	this->id = id + 11 * level;
}

void Player::CollectCoin()
{
	score += 200;
	coin += 1;
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

void Player::LoadData(string file)
{
	vector<vector<string>> name;
	vector<unsigned int> time;
	time.push_back(0);

	fstream f;
	f.open(file);

	while (!f.eof())
	{
		string count;
		string text;

		f >> count;
		f >> text;
		text = "Source/images/mario/" + text;

		vector<string> img;
		img.push_back(text);

		name.push_back(img);
	}

	for (int i = 0; i < name.size(); i++)
	{
		mario.push_back(new Animation(name[i], time));
	}
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
