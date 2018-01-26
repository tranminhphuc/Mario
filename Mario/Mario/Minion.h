#pragma once

#ifndef _MINION
#define _MINION

#include "Library.h"
#include "Textures.h"

class Minion
{
public:
	enum State
	{
		TrenMatDat,
		NhayLen,
		NhayXuong
	};
	State jumpState;

	int minionState;
	int id;

	int xMinion, yMinion;
	int width, height;

	bool moveDirection;
	int moveSpeed;

	float startJumpSpeed;
	float currentJumpSpeed;
	float jumpDistance;
	float currentJumpDistance;
	float currentFallingSpeed;

	int deadTime;

	bool minionSpawned;
	bool onAnotherMinion;

	bool collisionOnlyWithPlayer;

	Minion();
	~Minion();

	virtual void Update();
	virtual void Draw(sf::RenderWindow& window, Texture* texture);

	virtual void MoveX();
	virtual void MoveY(int distance);

	virtual bool UpdateMinion();
	virtual void MinionPhysics();
	
	virtual void CollisionEffect();
	virtual void MinionDeathAnimation();

	virtual void CollisionWithPlayer(bool top);
	virtual void CollisionWithAnotherMinion();

	virtual void LockMinion();

	virtual void SetMinionState(int minionState);
	virtual bool GetPowerUp();

	void PhysicsState1();
	void PhysicsState2();

	void StartJump(int distance);
	void ResetJump();

	void Spawn();

	int GetX();
	int GetY();
	void SetY(int y);

	int GetID();
	void SetID(int id);

	int GetMinionState();

	bool CheckCollisionLB(int distanceX, int distanceY);
	bool CheckCollisionLT(int distanceX, int distanceY);
	bool CheckCollisionRB(int distanceX, int distanceY);
	bool CheckCollisionRT(int distanceX, int distanceY);
	bool CheckCollisionLC(int distance);
	bool CheckCollisionRC(int distance);
};

#endif
