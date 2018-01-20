#include "Beetle.h"
#include "Windows.h"

Beetle::Beetle(int xMinion, int yMinion, bool moveDirection)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
	this->minionState = 0;
	this->id = Window::getMap()->GetMapType() == Window::getMap()->BanNgay || Window::getMap()->GetMapType() == Window::getMap()->HoangHon || Window::getMap()->GetMapType() == Window::getMap()->BuoiToi || Window::getMap()->GetMapType() == Window::getMap()->BinhMinh ? 53 : Window::getMap()->GetMapType() == Window::getMap()->LongDat ? 55 : 57;
	this->moveDirection = moveDirection;
	this->moveSpeed = 1;
}

Beetle::~Beetle()
{
}

void Beetle::Update(unsigned int time)
{
}

void Beetle::Draw(sf::RenderWindow & window, Texture * texture)
{
}
