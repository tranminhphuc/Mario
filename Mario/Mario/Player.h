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

	int id;
	unsigned int moveAnimationTime;

	unsigned int score;
	unsigned int coin;

	const int smallWidth = 24, smallHeight = 32;
	const int bigWidth = 32, bigHeight = 64;

	int moveSpeed;
	int maxSpeed;
	int live;
	int level;

	unsigned int timePassed;

	float jumpSpeed;
	float currentJumpSpeed;
	float jumpDistance;
	float currentJumpDistance;
	float currentFallingSpeed;

	bool move;
	bool squat;

	bool moveDirection;
	bool changeMoveDirection;
	bool newMoveDiretion;

	bool inLevelAnimation;
	bool inLevelDownAnimation;
	int inLevelDownAnimationID;

	bool starEffect;

	void LoadData(string file);
	void MovePlayer();

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

	void PlayerPhysics();

	void Update();
	void Draw(sf::RenderWindow& window);

	void UpdateAnimation(float time);
	void PowerUpAnimation();

	void MoveAnimation();
	void SwimingAnimation();

	void StartMove();
	void ResetMove();
	void StopMove();

	void Jump();
	void StartJump(int distance);
	void ResetJump();

	void ResetLevel();

	int GetWidth();
	int GetHeight();

	float GetX();
	void SetX(float xPlayer);
	
	float GetY();
	void SetY(float yPlayer);

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

	int GetMarioID();
	void SetMarioID(int id);

	int GetCoin();
	void SetCoin(int coin);

	int GetJumpState();

	bool getMove();
};

#endif
