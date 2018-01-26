#include "BulletBill.h"
#include "Windows.h"

BulletBill::BulletBill(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

BulletBill::~BulletBill()
{
}

void BulletBill::Update()
{
}

void BulletBill::Draw(sf::RenderWindow & window, Texture * texture)
{
}

void BulletBill::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect() || top)
	{
		SetMinionState(-2);
	}
	else
	{
		Window::GetMap()->PlayerDeath();
	}
}
