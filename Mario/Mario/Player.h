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
	int moveSpeed;
	int maxSpeed;
	int live;
	int level;
	float jumpSpeed;
	float currentJumpSpeed;
	float jumpDistance;
	float currentJumpDistance;

	void LoadData();
	void MovePlayer();
	void Playerphysics();

	bool CheckCollisionLB(int distanceX, int distanceY);
	bool CheckCollisionLT(int distanceX, int distanceY);
	bool CheckCollisionRB(int distanceX, int distanceY);
	bool CheckCollisionRT(int distanceX, int distanceY);
	bool CheckCollisionLC(int distanceX);
	bool CheckCollisionRC(int distanceX);
public:
	Player();
	~Player();
	void MoveX(int distance);
	void MoveY(int distance);
	void UpdateAnimation(float time);
};

#endif
