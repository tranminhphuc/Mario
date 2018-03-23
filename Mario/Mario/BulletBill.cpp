#include "BulletBill.h"
#include "Windows.h"

BulletBill::BulletBill(int xMinion, int yMinion, int minionState, bool moveDirection)
{
	this->xMinion = (float)xMinion;
	this->yMinion = (float)yMinion - 2;

	this->moveDirection = Window::GetMap()->GetPlayer()->GetX() - Window::GetMap()->GetX() + Window::GetMap()->GetPlayer()->GetWidth() / 32 < this->xMinion + width / 32;
	this->moveSpeed = 4;

	this->id = Window::GetMap()->GetLevel() == 22 ? 60 : 59;
	this->height = 30;

	this->minionState = minionState;

	this->currentJumpSpeed = (float)Window::GetMap()->GetObjectX(xMinion + 16);
	this->currentFallingSpeed = (float)Window::GetMap()->GetObjectY(yMinion);

	this->minX = Window::GetMap()->GetLevel() == 17 ? 73 * 32 : 0;
	this->maxX = Window::GetMap()->GetLevel() == 17 ? 303 * 32 : Window::GetMap()->GetWidth() * 32;
}

BulletBill::~BulletBill()
{
}

void BulletBill::Update()
{
	if (minionState != -2)
	{
		xMinion += moveDirection ? -moveSpeed : moveSpeed;

		if (xMinion + width < currentJumpDistance || xMinion > jumpState)
			minionState = -1;
	}
	else
	{
		MinionDeathAnimation();
	}
}

void BulletBill::Draw(sf::RenderWindow & window, Texture * texture)
{
	if (minionState != -2)
		texture->Draw(window, sf::Vector2f(xMinion + Window::GetMap()->GetX(), yMinion + 2));

	if (minionState == 0)
		Window::GetMap()->GetObject(145)->GetAnimation()->getTexture()->Draw(window, sf::Vector2f(currentJumpSpeed * 32 + Window::GetMap()->GetX(), Window::gameHeight - currentFallingSpeed * 32 + 32));
}

void BulletBill::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect() || top)
		SetMinionState(-2);
	else
		Window::GetMap()->PlayerDeath();
}
