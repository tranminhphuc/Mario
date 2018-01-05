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

	float xPlayer, yPlayer;
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

	bool move;
	bool squat;

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
	Player(float xPlayer, float yPlayer);
	~Player();

	void MoveX(int distance);
	void MoveY(int distance);

	void Update();

	void UpdateAnimation(float time);

	void StartMove();
	void ResetMove();
	void StopMove();

	void ResetLevel();

	int GetWidth();
	int GetHeight();

	int GetLevel();
	void SetLevel(int level);

	int getLive();
	void SetLive(int live);

	int GetMoveSpeed();
	void SetMoveSpeed(int moveSpeed);

	bool GetSquat();
	void SetSquat(bool squat);

	int GetScore();
	void SetScore(int score);

	int GetCoin();
	void SetCoin(int coin);

	int GetJumpState();

	bool getMove();
};

#endif
