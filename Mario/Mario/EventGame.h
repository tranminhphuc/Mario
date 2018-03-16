#pragma once

#ifndef _EVENT
#define _EVENT

#include "Library.h"

class Event
{
private:
	bool state;
	unsigned int step;
public:
	enum AnimationType
	{
		Top,
		Bot,
		Left,
		Right,
		LoadingMenu,
		GameOver,
		ScoreEnd,
		BossEnd1,
		BossEnd2,
		BossEnd3,
		BossEnd4,
		BossEndText1,
		BossEndText2
	};
	std::vector<AnimationType> oldDir;
	std::vector<int> oldLength;

	std::vector<AnimationType> newDir;
	std::vector<int> newLenght;

	enum EventType
	{
		normal,
		end,
		bonusEnd
	};
	EventType eventType;

	unsigned int time;
	int delay;
	int speed;

	int newLevel;
	int newLevelType;

	int newMapX;
	int newPlayerX;
	int newPlayerY;

	bool inEvent;
	bool newUnderWater;
	bool newMoveMap;

	bool endGame;

	Event();
	~Event();

	void Normal();
	void End();

	void NewLevel();

	void ResetData();
};

#endif
