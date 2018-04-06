#include "Pipe.h"
#include "Windows.h"

Pipe::Pipe(int type, int leftX, int leftY, int rightX, int rightY, int newPlayerX, int newPlayerY, int newCurrentLevel, int newLevel, int delay, int speed, bool newUnderWater)
{
	this->type = type;

	this->leftX = leftX;
	this->leftY = leftY;
	this->rightX = rightX;
	this->rightY = rightY;

	this->newPlayerX = newPlayerX;
	this->newPlayerY = newPlayerY;

	this->newCurrentLevel = newCurrentLevel;
	this->newLevel = newLevel;
	this->newUnderWater = newUnderWater;

	this->delay = delay;
	this->speed = speed;
}

Pipe::~Pipe()
{
}

void Pipe::CheckUse()
{
	if(type == 0 || type == 2)
	{
		if (Window::GetMap()->GetPlayer()->GetSquat() && Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetX() >= leftX * 32 + 4 && Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() < (rightX + 1) * 32 - 4)
			SetEvent();
	}
	else
	{
		if (!Window::GetMap()->GetPlayer()->GetSquat() && Window::GetMap()->GetObjectX(Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 2 + 2) == rightX - 1 && Window::GetMap()->GetObjectY(Window::GetMap()->GetPlayer()->GetY() + Window::GetMap()->GetPlayer()->GetHeight() + 2) == rightY - 1)
			SetEvent();
	}
}

void Pipe::SetEvent()
{
	Window::GetMap()->GetEvent()->ResetData();
	Window::GetMap()->GetPlayer()->StopMove();
	Window::GetMap()->GetPlayer()->ResetJump();

	Window::GetMap()->GetEvent()->eventType = Window::GetMap()->GetEvent()->normal;

	Window::GetMap()->GetEvent()->newLevel = newCurrentLevel;
	Window::GetMap()->GetEvent()->newLevelType = newLevel;

	Window::GetMap()->GetEvent()->delay = delay;
	Window::GetMap()->GetEvent()->speed = speed;

	Window::GetMap()->GetEvent()->inEvent = false;
	Window::GetMap()->GetEvent()->newUnderWater = newUnderWater;

	Window::GetMap()->GetEvent()->newMapX = (newPlayerX <= 32 * 2 ? 0 : -(newPlayerX - 32 * 2));
	Window::GetMap()->GetEvent()->newPlayerX = (newPlayerX <= 32 * 2 ? newPlayerX : 32 * 2);
	Window::GetMap()->GetEvent()->newPlayerY = newPlayerY;

	if (type = 0)
	{
		Window::GetMap()->GetEvent()->newPlayerY = -Window::GetMap()->GetPlayer()->GetLevel() > 0 ? 32 : 0;
		Window::GetMap()->GetEvent()->oldDir.push_back(Window::GetMap()->GetEvent()->Bot);
		Window::GetMap()->GetEvent()->oldLength.push_back(Window::GetMap()->GetPlayer()->GetHeight());
	}
}