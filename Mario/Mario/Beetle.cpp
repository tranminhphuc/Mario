#include "Beetle.h"
#include "Windows.h"

Beetle::Beetle(int xMinion, int yMinion, bool moveDirection)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
	this->minionState = 0;
	this->id = Window::GetMap()->GetMapType() == Window::GetMap()->BanNgay || Window::GetMap()->GetMapType() == Window::GetMap()->HoangHon || Window::GetMap()->GetMapType() == Window::GetMap()->BuoiToi || Window::GetMap()->GetMapType() == Window::GetMap()->BinhMinh ? 53 : Window::GetMap()->GetMapType() == Window::GetMap()->LongDat ? 55 : 57;
	this->moveDirection = moveDirection;
	this->moveSpeed = 1;
}

Beetle::~Beetle()
{
}

void Beetle::Update()
{
	if (minionState == -2)
		MinionDeathAnimation();
	else
		MoveX();
}

void Beetle::Draw(sf::RenderWindow & window, Texture * texture)
{
	if (minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion));
}
