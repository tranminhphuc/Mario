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
		DungYen,
		NhayLen,
		NhayXuong
	};
	State jumpState;

	float xPlayer, yPlayer;
	float width, height;

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
	Player();
	~Player();

	void MoveX(int distance);
	void MoveY(int distance);

	void UpdateAnimation(float time);

	void StartMove();
	void ResetMove();
	void StopMove();

	int GetWidth();
	int GetHeight();

	int GetMoveSpeed();
	void SetMoveSpeed(int moveSpeed);

	bool getSquat();
	void SetSquat(bool squat);
};

#endif
