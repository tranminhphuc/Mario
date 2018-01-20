#pragma once

#ifndef _PLAYER
#define _PLAYER

#include "Animation.h"

class Player
{
private:
	vector<Animation*> mario;

	enum State
	{
		TrenMatDat,
		NhayLen,
		NhayXuong
	};
	State jumpState;

	int xPlayer, yPlayer;
	float width, height;

	unsigned int score;
	unsigned int coin;

	const int smallWidth = 24, smallHeight = 32;
	const int bigWidth = 32, bigHeight = 64;

	int moveSpeed;
	int maxSpeed;
	int live;
	int level;

	float jumpSpeed;
	float currentJumpSpeed;
	float jumpDistance;
	float currentJumpDistance;
	float currentFallingSpeed;

	bool move;
	bool squat;

	bool starEffect;

	void LoadData();
	void MovePlayer();
	void Playerphysics();

	bool CheckCollisionLB(int distanceX, int distanceY);
	bool CheckCollisionLT(int distanceX, int distanceY);
	bool CheckCollisionRB(int distanceX, int distanceY);
	bool CheckCollisionRT(int distanceX, int distanceY);
	bool CheckCollisionLC(int distance);
	bool CheckCollisionRC(int distance);
public:
	Player(int xPlayer, int yPlayer);
	~Player();

	void MoveX(int distance);
	void MoveY(int distance);

	void Update();

	void UpdateAnimation(float time);

	void StartMove();
	void ResetMove();
	void StopMove();

	void Jump();
	void StartJump(int distance);
	void ResetJump();

	void ResetLevel();

	int GetWidth();
	int GetHeight();

	int GetX();
	void SetX(int xPlayer);
	
	int GetY();
	void SetY(int yPlayer);

	int GetLevel();
	void SetLevel(int level);

	int getLive();
	void SetLive(int live);

	int GetMoveSpeed();
	void SetMoveSpeed(int moveSpeed);

	bool GetSquat();
	void SetSquat(bool squat);

	bool GetStarEffect();
	void SetStarEffect(bool startEffect);

	int GetScore();
	void SetScore(int score);

	int GetCoin();
	void SetCoin(int coin);

	int GetJumpState();

	bool getMove();
};

#endif
